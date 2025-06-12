#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

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

// Static member definition
// std::ofstream SimpleMCPServer::logFile;