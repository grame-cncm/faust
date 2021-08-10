#include <unordered_map>
#include <utility>

#include "Memory.hh"
namespace nlpl
{
void MemoryZone::print(std::ostream& os)
{
    if (fSize == 0) {
        os << fType << ' ' << fName;
    } else {
        os << fType << "[" << fSize << "]" << ' ' << fName;
    }

    if (fPhase != kFinal) {
        os << '_' << fPhase;
    }
};

Mem memory(const std::string& typ, const std::string& name, unsigned int phase)
{
    static std::unordered_map<std::tuple<std::string, std::string, unsigned int>, Mem> gHash;
    std::tuple<std::string, std::string, unsigned int>                                 key(typ, name, phase);

    Mem  M;
    auto p = gHash.find(key);
    if (p != gHash.end()) {
        M = p->second;
    } else {
        M = new MemoryZone(typ, name, phase);
        gHash.insert({key, M});
    }
    return M;
}

// a memory is a memory with a non-zero size
Mem memory(const std::string& typ, const std::string& name, size_t size, unsigned int phase)
{
    Mem M    = memory(typ, name, phase);
    M->fSize = size;
    return M;
}
}  // namespace nlpl