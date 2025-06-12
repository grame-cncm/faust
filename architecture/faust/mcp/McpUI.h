#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "faust/gui/UI.h"
#include "faust/mcp/mcp-protocol.h"

// ============================================================================
// MCP Widget - Faust parameter wrapper for MCP tools
// ============================================================================

/**
 * @brief MCP Tool for Faust widget parameters
 *
 * This class wraps a Faust widget (slider, button, etc.) as an MCP tool,
 * allowing direct control of DSP parameters through the MCP protocol.
 */
class McpWidget : public McpTool {
   private:
    std::string              fName;          ///< Widget name
    std::vector<std::string> fGroups;        ///< Group hierarchy (specific to general)
    float                    fDefaultValue;  ///< Default parameter value
    float                    fMinValue;      ///< Minimum parameter value
    float                    fMaxValue;      ///< Maximum parameter value
    float*                   fAddress;       ///< Pointer to the actual parameter in DSP

    /**
     * @brief Sanitize a name for MCP tool usage
     * @param input Input string to sanitize
     * @return Sanitized string safe for MCP tool names
     */
    std::string sanitizeName(const std::string& input) const
    {
        std::string result;
        result.reserve(input.length());

        for (char c : input) {
            if (std::isalnum(c) || c == '_') {
                // Keep alphanumeric characters and existing underscores
                result += c;
            } else if (c == ' ' || c == '-' || c == '.' || c == '/') {
                // Replace common problematic characters with underscore
                if (!result.empty() && result.back() != '_') {
                    result += '_';
                }
            }
            // Skip other special characters
        }

        // Remove trailing underscore
        if (!result.empty() && result.back() == '_') {
            result.pop_back();
        }

        return result.empty() ? "param" : result;
    }

    /**
     * @brief Generate human-readable parameter path
     * @return String like "Name (Group1 > Group2)"
     */
    std::string getHumanReadablePath() const
    {
        std::string path = fName;

        if (!fGroups.empty()) {
            path += " (";
            for (size_t i = 0; i < fGroups.size(); ++i) {
                if (i > 0) {
                    path += " > ";
                }
                path += fGroups[i];
            }
            path += ")";
        }

        return path;
    }

   public:
    /**
     * @brief Construct a new MCP Widget
     * @param name Widget name
     * @param groups Group hierarchy from most specific to most general
     * @param defaultValue Default parameter value
     * @param minValue Minimum parameter value
     * @param maxValue Maximum parameter value
     * @param address Pointer to the parameter variable in the DSP
     */
    McpWidget(std::string name, std::vector<std::string> groups, float defaultValue, float minValue,
              float maxValue, float* address)
        : fName(std::move(name)),
          fGroups(std::move(groups)),
          fDefaultValue(defaultValue),
          fMinValue(minValue),
          fMaxValue(maxValue),
          fAddress(address)
    {
        // Initialize the parameter with its default value
        if (fAddress != nullptr) {
            *fAddress = fDefaultValue;
        }
    }

    /**
     * @brief Get the MCP tool name
     * @return Tool name in format "Name_Group1_Group2"
     */
    std::string name() const override
    {
        std::string toolName = fName;

        // Add groups from most specific to most general
        for (const auto& group : fGroups) {
            toolName += "_" + group;
        }

        // Sanitize the complete name
        toolName = sanitizeName(toolName);

        // Ensure the name doesn't exceed reasonable length (Cursor has 60 char limit)
        if (toolName.length() > 50) {
            toolName = toolName.substr(0, 50);
        }

        return toolName;
    }

    /**
     * @brief Get the MCP tool description in JSON format
     * @return JSON schema describing the tool
     */
    std::string describe() const override
    {
        std::string humanPath = getHumanReadablePath();
        std::string toolName  = name();

        return R"({
    "name": ")" +
               toolName + R"(",
    "description": "Control )" +
               humanPath + R"(: range [)" + std::to_string(fMinValue) + R"(, )" +
               std::to_string(fMaxValue) + R"(]",
    "inputSchema": {
        "type": "object",
        "properties": {
            "value": {
                "type": "string",
                "description": "Parameter value as string"
            }
        },
        "required": ["value"]
    }
})";
    }

    /**
     * @brief Handle parameter value change
     * @param arguments JSON string containing the new value
     * @return Response message confirming the change
     */
    std::string call(const std::string& arguments) override
    {
        if (fAddress == nullptr) {
            return "\"Error: Invalid parameter address\"";
        }

        // Extract value from JSON arguments
        std::string valueStr = extractStringValue(arguments, "value");
        if (valueStr.empty()) {
            return "\"Error: Missing parameter value\"";
        }

        try {
            float value = std::stof(valueStr);

            // Clamp value between min and max
            value = std::clamp(value, fMinValue, fMaxValue);

            // Update the parameter
            *fAddress = value;

            // Return confirmation message
            std::string humanPath = getHumanReadablePath();
            return "\"" + humanPath + " set to " + std::to_string(value) + "\"";

        } catch (const std::exception& e) {
            return "\"Error: Invalid parameter value\"";
        }
    }
};

// ============================================================================
// MCP UI - Faust UI implementation with MCP server integration
// ============================================================================

/**
 * @brief Faust UI implementation that creates MCP tools for each widget
 *
 * This class implements the Faust UI interface and automatically generates
 * MCP tools for each widget encountered during buildUserInterface().
 * Each slider, button, etc. becomes an MCP tool that can be controlled
 * remotely through the MCP protocol.
 */
class McpUI : public UI {
   private:
    SimpleMCPServer          fServer;       ///< Integrated MCP server
    std::vector<std::string> fCurrentPath;  ///< Current group hierarchy path

    /**
     * @brief Get the current path reversed (for McpWidget constructor)
     * @return Vector of group names from most specific to most general
     */
    std::vector<std::string> getReversedPath() const
    {
        std::vector<std::string> reversed = fCurrentPath;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

   public:
    /**
     * @brief Default constructor
     */
    McpUI() = default;

    /**
     * @brief Start the MCP server
     * Call this after buildUserInterface() to begin serving MCP requests
     */
    void run() { fServer.run(); }

    // -- widget's layouts
    void openTabBox(const char* label) override
    {
        // If this is the first (root) group, set it as server name
        if (fCurrentPath.empty()) {
            fServer.setServerName(label);
        }
        fCurrentPath.emplace_back(label);
    }

    void openHorizontalBox(const char* label) override
    {
        // If this is the first (root) group, set it as server name
        if (fCurrentPath.empty()) {
            fServer.setServerName(label);
        }
        fCurrentPath.emplace_back(label);
    }

    void openVerticalBox(const char* label) override
    {
        // If this is the first (root) group, set it as server name
        if (fCurrentPath.empty()) {
            fServer.setServerName(label);
        }
        fCurrentPath.emplace_back(label);
    }

    void closeBox() override
    {
        if (!fCurrentPath.empty()) {
            fCurrentPath.pop_back();
        }
    }

    // -- active widgets
    void addButton(const char* label, FAUSTFLOAT* zone) override
    {
        auto widget = std::make_unique<McpWidget>(label,  // Direct const char* to string conversion
                                                  getReversedPath(),
                                                  0.0f,  // default value
                                                  0.0f,  // min value
                                                  1.0f,  // max value
                                                  zone);
        fServer.registerTool(std::move(widget));
    }

    void addCheckButton(const char* label, FAUSTFLOAT* zone) override
    {
        auto widget = std::make_unique<McpWidget>(label,  // Direct const char* to string conversion
                                                  getReversedPath(),
                                                  0.0f,  // default value
                                                  0.0f,  // min value
                                                  1.0f,  // max value
                                                  zone);
        fServer.registerTool(std::move(widget));
    }

    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                           FAUSTFLOAT max, FAUSTFLOAT /*step*/) override
    {
        auto widget =
            std::make_unique<McpWidget>(label,  // Direct const char* to string conversion
                                        getReversedPath(), static_cast<float>(init),
                                        static_cast<float>(min), static_cast<float>(max), zone);
        fServer.registerTool(std::move(widget));
    }

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                             FAUSTFLOAT max, FAUSTFLOAT /*step*/) override
    {
        auto widget =
            std::make_unique<McpWidget>(label,  // Direct const char* to string conversion
                                        getReversedPath(), static_cast<float>(init),
                                        static_cast<float>(min), static_cast<float>(max), zone);
        fServer.registerTool(std::move(widget));
    }

    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                     FAUSTFLOAT max, FAUSTFLOAT /*step*/) override
    {
        auto widget =
            std::make_unique<McpWidget>(label,  // Direct const char* to string conversion
                                        getReversedPath(), static_cast<float>(init),
                                        static_cast<float>(min), static_cast<float>(max), zone);
        fServer.registerTool(std::move(widget));
    }

    // -- passive widgets (ignored)
    void addHorizontalBargraph(const char* /*label*/, FAUSTFLOAT* /*zone*/, FAUSTFLOAT /*min*/,
                               FAUSTFLOAT /*max*/) override
    {
        // Ignored as specified
    }

    void addVerticalBargraph(const char* /*label*/, FAUSTFLOAT* /*zone*/, FAUSTFLOAT /*min*/,
                             FAUSTFLOAT /*max*/) override
    {
        // Ignored as specified
    }

    // -- soundfiles (ignored)
    void addSoundfile(const char* /*label*/, const char* /*filename*/,
                      Soundfile** /*sf_zone*/) override
    {
        // Ignored as specified
    }

    // -- metadata declarations (ignored)
    void declare(FAUSTFLOAT* /*zone*/, const char* /*key*/, const char* /*val*/) override
    {
        // Ignored as specified
    }
};