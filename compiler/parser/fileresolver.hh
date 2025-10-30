#pragma once

#include <algorithm>
#include <filesystem>
#include <system_error>
#include <optional>
#include <string>
#include <vector>

namespace faust::parser {

/**
 * @brief Canonicalise @p dir to a path that can be stored or compared reliably.
 */
inline std::filesystem::path canonicalPath(const std::filesystem::path& dir)
{
    namespace fs = std::filesystem;
    if (dir.empty()) {
        return dir;
    }

    std::error_code ec;
    const bool exists = fs::exists(dir, ec);
    if (!ec && exists) {
        ec.clear();
        auto weak = fs::weakly_canonical(dir, ec);
        if (!ec) {
            return weak;
        }
    }

    ec.clear();
    auto absolute = fs::absolute(dir, ec);
    if (!ec) {
        return absolute.lexically_normal();
    }

    return dir.lexically_normal();
}

/** @return canonical string form for @p dir (empty string when @p dir is empty). */
inline std::string canonicalDirectoryString(const std::filesystem::path& dir)
{
    auto canonical = canonicalPath(dir);
    return canonical.empty() ? std::string{} : canonical.string();
}

/**
 * @brief Append @p dir to @p dirs when non-empty and not already present.
 */
inline void appendUniqueDirectory(std::vector<std::string>& dirs, const std::filesystem::path& dir)
{
    std::string canonical = canonicalDirectoryString(dir);
    if (canonical.empty()) {
        return;
    }
    if (std::find(dirs.begin(), dirs.end(), canonical) == dirs.end()) {
        dirs.push_back(std::move(canonical));
    }
}

/**
 * @brief Canonical filesystem resolver used by parsing and code-generation paths.
 *
 * The parser historically stored raw strings in global vectors and relied on
 * ad-hoc string concatenation (or even process-wide @c chdir calls) to find
 * import files and architecture templates. This class centralises that logic:
 *
 *  - search directories are canonicalised once as they are registered;
 *  - duplicates are ignored so resolvers work with minimal, deterministic
 *    directory lists;
 *  - lookups return canonical absolute paths (or @c std::nullopt) without
 *    mutating global state, eliminating the need for temporary @c chdir calls;
 *  - scheme-based paths (e.g. @c http://) are ignored here, leaving network
 *    fetchers to handle them.
 *
 * High-level API code (SourceReader, box signal bridges, Documentator, etc.)
 * can now request canonical file locations without caring about string
 * normalisation or platform-specific separator quirks.
 */
class FileResolver {
   public:
    using path_type = std::filesystem::path;

    FileResolver() = default;

    /**
     * @brief Register an import search directory.
     *
     * The directory is canonicalised and deduplicated. Non-existent paths are
     * still stored lexically normalised so callers can perform existence tests
     * later.
     */
    void addImportDirectory(const path_type& dir) { appendUnique(fImportDirectories, normalizeDirectory(dir)); }

    /**
     * @brief Register an architecture search directory (same semantics as imports).
     */
    void addArchitectureDirectory(const path_type& dir)
    {
        appendUnique(fArchitectureDirectories, normalizeDirectory(dir));
    }

    /** @return canonicalised import directories, in registration order. */
    [[nodiscard]] const std::vector<path_type>& importDirectories() const { return fImportDirectories; }

    /** @return canonicalised architecture directories, in registration order. */
    [[nodiscard]] const std::vector<path_type>& architectureDirectories() const { return fArchitectureDirectories; }

    /**
     * @brief Resolve a DSP import path.
     *
     * @param filename relative or absolute path supplied by user code.
     * @return canonical absolute path when the file exists, otherwise nullopt.
     */
    [[nodiscard]] std::optional<path_type> resolveImport(const path_type& filename) const
    {
        return resolve(filename, fImportDirectories);
    }

    /**
     * @brief Resolve an architecture file path.
     * Identical semantics to resolveImport but operating on the architecture list.
     */
    [[nodiscard]] std::optional<path_type> resolveArchitecture(const path_type& filename) const
    {
        return resolve(filename, fArchitectureDirectories);
    }

   private:
    /**
     * @return true when @p filename contains a URL scheme (e.g. "http://"),
     * signalling that the resolver should ignore it and let higher layers
     * handle remote fetching.
     */
    [[nodiscard]] static bool hasScheme(const path_type& filename)
    {
        const auto value = filename.generic_string();
        return value.find("://") != std::string::npos;
    }

    /**
     * @brief Produce a canonical representation of @p dir suitable for storage.
     *
     * Existing directories are canonicalised via @c weakly_canonical. Missing
     * ones fallback to @c absolute/@c lexically_normal to minimise surprises.
     */
    [[nodiscard]] static path_type normalizeDirectory(const path_type& dir) { return canonicalPath(dir); }

    /** Append @p dir into @p storage when non-empty and not already present. */
    static void appendUnique(std::vector<path_type>& storage, const path_type& dir)
    {
        if (dir.empty()) {
            return;
        }
        if (std::find(storage.begin(), storage.end(), dir) == storage.end()) {
            storage.push_back(dir);
        }
    }

    /**
     * @brief Canonicalise @p candidate when it resolves to an existing file.
     *
     * @return canonical absolute path, or nullopt if the file does not exist or
     * canonicalisation fails.
     */
    [[nodiscard]] static std::optional<path_type> canonicalIfExists(const path_type& candidate)
    {
        namespace fs = std::filesystem;
        std::error_code ec;

        auto absoluteCandidate = fs::absolute(candidate, ec);
        if (ec) {
            return std::nullopt;
        }

        ec.clear();
        const bool exists = fs::exists(absoluteCandidate, ec);
        if (ec || !exists) {
            return std::nullopt;
        }

        ec.clear();
        const bool isFile = fs::is_regular_file(absoluteCandidate, ec);
        if (ec || !isFile) {
            return std::nullopt;
        }

        ec.clear();
        auto canonical = fs::weakly_canonical(absoluteCandidate, ec);
        if (ec) {
            return std::nullopt;
        }

        return canonical;
    }

    /**
     * @brief Resolve absolute or rooted filenames directly.
     */
    [[nodiscard]] static std::optional<path_type> resolveAbsolute(const path_type& filename)
    {
        if (filename.empty()) {
            return std::nullopt;
        }
        if (filename.is_absolute() || filename.has_root_name()) {
            return canonicalIfExists(filename);
        }

        return std::nullopt;
    }

    /**
     * @brief Common resolution routine used by both import and architecture lookups.
     */
    [[nodiscard]] std::optional<path_type> resolve(const path_type& filename,
                                                   const std::vector<path_type>& roots) const
    {
        if (filename.empty() || hasScheme(filename)) {
            return std::nullopt;
        }

        if (auto absoluteResult = resolveAbsolute(filename)) {
            return absoluteResult;
        }

        if (auto directResult = canonicalIfExists(filename)) {
            return directResult;
        }

        return resolveInRoots(filename, roots);
    }

    /**
     * @brief Search @p roots for @p filename, returning the first canonical match.
     */
    [[nodiscard]] std::optional<path_type> resolveInRoots(const path_type& filename,
                                                          const std::vector<path_type>& roots) const
    {
        for (const auto& root : roots) {
            if (root.empty()) {
                continue;
            }
            if (auto resolved = canonicalIfExists(root / filename)) {
                return resolved;
            }
        }
        return std::nullopt;
    }

    std::vector<path_type> fImportDirectories;
    std::vector<path_type> fArchitectureDirectories;
};

}  // namespace faust::parser
