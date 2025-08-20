/************************** BEGIN McpUI.h *****************************
 FAUST Architecture File
 Copyright (C) 2025 INRIA
 Copyright (C) 2025 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>

#include "faust/gui/UI.h"

// ============================================================================
// Utility Functions
// ============================================================================

inline std::string extractStringValue(const std::string& json, const std::string& key)
{
    std::string searchKey = "\"" + key + "\"";
    size_t      pos       = json.find(searchKey);
    if (pos == std::string::npos) {
        return "";
    }
    
    // Move past the key
    pos += searchKey.length();
    
    // Skip spaces and look for ":"
    while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t')) {
        pos++;
    }
    if (pos >= json.length() || json[pos] != ':') {
        return "";
    }
    pos++;  // skip the ":"
    
    // Skip spaces after ":"
    while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t')) {
        pos++;
    }
    if (pos >= json.length()) {
        return "";
    }
    
    // If it's a string
    if (json[pos] == '"') {
        pos++;  // skip the first "
        size_t endPos = json.find("\"", pos);
        if (endPos == std::string::npos) {
            return "";
        }
        return json.substr(pos, endPos - pos);
    }
    // If it's a number (integer or float)
    if ((json[pos] >= '0' && json[pos] <= '9') || json[pos] == '-' || json[pos] == '+') {
        size_t startPos = pos;
        while (pos < json.length() && ((json[pos] >= '0' && json[pos] <= '9') || json[pos] == '.' || json[pos] == 'e' ||
                                       json[pos] == 'E' || json[pos] == '-' || json[pos] == '+')) {
            pos++;
        }
        return json.substr(startPos, pos - startPos);
    }
    // Otherwise, not supported
    return "";
}

inline std::string removeControlChars(const std::string& input)
{
    std::string output;
    bool        inString  = false;
    bool        prevSpace = false;
    
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        
        // Handle string characters
        if (c == '"' && (i == 0 || input[i - 1] != '\\')) {
            inString = !inString;
            output += c;
            prevSpace = false;
            continue;
        }
        
        // Inside a string, copy everything (except control characters)
        if (inString) {
            if ((c >= 32 && c != 127) || c == '\t') {
                output += c;
            }
            continue;
        }
        
        // Outside string: remove control characters
        if (c >= 32 && c != 127) {
            if (c == ' ') {
                if (!prevSpace) {
                    output += ' ';
                    prevSpace = true;
                }
                // otherwise, skip the space
            } else {
                output += c;
                prevSpace = false;
            }
        }
        // otherwise, skip the control character
    }
    return output;
}

// ============================================================================
// MCP Tool Interface
// ============================================================================

/**
 * @brief Abstract base class for MCP tools
 *
 * This interface defines the contract that all MCP tools must implement.
 * Tools represent executable functions that can be invoked by MCP clients.
 */
class McpTool
{
public:
    McpTool() = default;
    virtual ~McpTool() = default;
    
    /**
     * @brief Get the unique name/identifier of this tool
     * @return Tool name used for MCP communication
     */
    virtual std::string name() const = 0;
    
    /**
     * @brief Get the JSON schema description of this tool
     * @return JSON string describing the tool's interface
     */
    virtual std::string describe() const = 0;
    
    /**
     * @brief Execute the tool with given arguments
     * @param arguments JSON string containing the tool's input parameters
     * @return JSON string containing the tool's response
     */
    virtual std::string call(const std::string& arguments) = 0;
};

    // ============================================================================
    // Simple MCP Server
    // ============================================================================

/**
 * @brief Simple MCP (Model Context Protocol) server implementation
 *
 * This class implements a server that:
 * - Communicates via JSON-RPC 2.0 protocol over stdin/stdout
 * - Manages a collection of tools that can be called by MCP clients
 * - Handles model context interactions
 * - Logs all exchanges to a file for debugging
 */
class SimpleMCPServer
{
private:
        // Static members
        // static std::ofstream logFile;  ///< Log file stream (uncomment for debugging)
    
        // Instance members
    std::map<std::string, std::unique_ptr<McpTool>> fRegisteredTools;  ///< Registry of available tools
    std::string fServerName;    ///< Server name for MCP identification
    std::string fServerVersion; ///< Server version for MCP identification
    
        // Message handling methods
    void sendResponse(const std::string& id, const std::string& result)
    {
    std::string cleanedResult = removeControlChars(result);
        // logFile << "SENDING:"
        //         << R"({"jsonrpc": "2.0", "id": ")" << id << R"(", "result": )" << cleanedResult << "}" << std::endl;
    std::cout << R"({"jsonrpc": "2.0", "id": ")" << id << R"(", "result": )" << cleanedResult << "}" << std::endl;
    }
    
    void sendError(const std::string& id, int code, const std::string& message)
    {
        // logFile << R"({"jsonrpc": "2.0", "id": ")" << id << R"(", "error": {"code": )" << code << R"(, "message": ")"
        //         << message << R"("})"
        //         << "}" << std::endl;
    std::cout << R"({"jsonrpc": "2.0", "id": ")" << id << R"(", "error": {"code": )" << code << R"(, "message": ")"
    << message << R"("})"
    << "}" << std::endl;
    }
    
        // Request processing methods
    void handleToolsListRequest(const std::string& id)
    {
    std::string result = R"( {"tools": [)";
    for (const auto& toolPair : fRegisteredTools) {
        const auto& tool = toolPair.second;
        result += tool->describe() + ",";
    }
    if (!fRegisteredTools.empty()) {
        result.pop_back();  // Remove the last comma
    }
    result += R"(] })";
    sendResponse(id, result);
    }
    
    void handleToolCall(const std::string& id, const std::string& toolName, const std::string& arguments)
    {
    if (fRegisteredTools.find(toolName) == fRegisteredTools.end()) {
        sendError(id, -32602, "Method not found: " + toolName);
        return;
    }
    std::string msg    = fRegisteredTools[toolName]->call(arguments);
    std::string result = R"({"content": [{"type": "text", "text": )" + msg + "}]}";
    sendResponse(id, result);
    }
    
    void handleInitialize(const std::string& id)
    {
    std::string result = R"({
                "protocolVersion": "2024-11-05",
                "capabilities": {
                "tools": {}
                },
                "serverInfo": {
                "name": ")" + fServerName + R"(",
                "version": ")" + fServerVersion + R"("
            }
        })";
    sendResponse(id, result);
    }
    
public:
    /**
     * @brief Constructor with default server information
     */
    SimpleMCPServer() : fServerName("AudioApp"), fServerVersion("1.0.0") {}
    
    /**
     * @brief Set the server name for MCP identification
     * @param name Server name to display in MCP clients
     */
    void setServerName(const std::string& name)
    {
    fServerName = name;
    }
    
    /**
     * @brief Set the server version for MCP identification
     * @param version Server version to display in MCP clients
     */
    void setServerVersion(const std::string& version)
    {
    fServerVersion = version;
    }
    
    /**
     * @brief Registers a new tool with the MCP server
     * @param tool Unique pointer to the tool to register
     */
    void registerTool(std::unique_ptr<McpTool> tool)
    {
    std::string name      = tool->name();
    fRegisteredTools[name] = std::move(tool);
    }
    
    /**
     * @brief Starts the MCP server and processes incoming requests
     *
     * This method runs an infinite loop reading JSON-RPC requests from stdin
     * and sending responses to stdout. The server handles:
     * - initialize: Server capability negotiation
     * - tools/list: Returns available tools
     * - tools/call: Executes a specific tool with arguments
     */
    void run()
    {
        // logFile.open("/Users/yannorlarey/Documents/Install/mcp-server/greeting.log", std::ios::app);
        // logFile << "Starting Simple MCP Server" << std::endl;
    std::string line;
    
    while (std::getline(std::cin, line)) {
            // logFile << "Received: " << line << std::endl;
        if (line.empty()) {
            continue;
        }
        
            // Basic JSON field extraction
        std::string id     = extractStringValue(line, "id");
        std::string method = extractStringValue(line, "method");
        
        if (method == "initialize") {
            handleInitialize(id);
        } else if (method == "notifications/cancelled") {
                // nothing to do
        } else if (method == "notifications/initialized") {
                // nothing to do
        } else if (method == "tools/list") {
            handleToolsListRequest(id);
        } else if (method == "tools/call") {
            std::string toolName = extractStringValue(line, "name");
            
                // Extract arguments (search for arguments block)
            size_t      argsPos   = line.find("\"arguments\":");
            std::string arguments = "{}";
            if (argsPos != std::string::npos) {
                argsPos += 12;  // length of "arguments":
                while (argsPos < line.length() && line[argsPos] == ' ') {
                    argsPos++;
                }
                if (argsPos < line.length() && line[argsPos] == '{') {
                    int    braceCount = 1;
                    size_t startPos   = argsPos;
                    argsPos++;
                    while (argsPos < line.length() && braceCount > 0) {
                        if (line[argsPos] == '{') {
                            braceCount++;
                        } else if (line[argsPos] == '}') {
                            braceCount--;
                        }
                        argsPos++;
                    }
                    if (braceCount == 0) {
                        arguments = line.substr(startPos, argsPos - startPos);
                    }
                }
            }
            
            handleToolCall(id, toolName, arguments);
        } else {
            sendError(id, -32601, "Method not found: " + method);
        }
    }
    }
};


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
    
    inline float clamp(float value, float a, float b)
    {
        float lo = (a <= b) ? a : b;
        float hi = (a <= b) ? b : a;
        return (value < lo) ? lo : (value > hi) ? hi : value;
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
            value = clamp(value, fMinValue, fMaxValue);

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

/**************************  END  McpUI.h **************************/
