--[[----------------------------------------------------------------------------
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2025 Audiokinetic Inc.
------------------------------------------------------------------------------]]

if not _AK_PREMAKE then
    error('You must use the custom Premake5 scripts by adding the following parameter: --scripts="Scripts\\Premake"', 1)
end

local Plugin = {}
Plugin.name = "Faust_Interpreter_Wwise_Plugin"
Plugin.factoryheader = "../SoundEnginePlugin/Faust_Interpreter_Wwise_PluginSourceFactory.h"
Plugin.appleteamid = ""
Plugin.signtoolargs = {}
Plugin.sdk = {}
Plugin.sdk.static = {}
Plugin.sdk.shared = {}
Plugin.authoring = {}

-- SDK STATIC PLUGIN SECTION
Plugin.sdk.static.includedirs = -- https://github.com/premake/premake-core/wiki/
{
    "../FaustRuntime",
}

Plugin.sdk.static.files = -- https://github.com/premake/premake-core/wiki/files
{
    "**.cpp",
    "**.h",
    "**.hpp",
    "**.c",
    "../FaustRuntime/**.cpp",
    "../FaustRuntime/**.h",
}
Plugin.sdk.static.excludes = -- https://github.com/premake/premake-core/wiki/removefiles
{
    "Faust_Interpreter_Wwise_PluginSourceShared.cpp"
}
Plugin.sdk.static.links = -- https://github.com/premake/premake-core/wiki/links
{
    "libfaust",
}

Plugin.sdk.static.libsuffix = "Source"
Plugin.sdk.static.libdirs = -- https://github.com/premake/premake-core/wiki/libdirs
{
}
Plugin.sdk.static.defines = -- https://github.com/premake/premake-core/wiki/defines
{
}

-- SDK SHARED PLUGIN SECTION
Plugin.sdk.shared.includedirs =
{
    "../FaustRuntime",
}
Plugin.sdk.shared.files =
{
    "Faust_Interpreter_Wwise_PluginSourceShared.cpp",
    "Faust_Interpreter_Wwise_PluginSourceFactory.h",
    "../FaustRuntime/**.cpp",
    "../FaustRuntime/**.h",
}
Plugin.sdk.shared.excludes =
{
}
Plugin.sdk.shared.links =
{
}
Plugin.sdk.shared.libdirs =
{
}
Plugin.sdk.shared.defines =
{
}

-- AUTHORING PLUGIN SECTION
Plugin.authoring.includedirs =
{
    "../FaustRuntime",
}
Plugin.authoring.files =
{
    "**.cpp",
    "**.h",
    "**.hpp",
    "**.c",
    "Faust_Interpreter_Wwise_Plugin.def",
    "Faust_Interpreter_Wwise_Plugin.xml",
    "**.rc",
}
Plugin.authoring.excludes =
{
}
Plugin.authoring.links =
{
}
Plugin.authoring.libdirs =
{
}
Plugin.authoring.defines =
{
}

-------------------------------------------------------------------------------- FAUST2WWISE ADDITIONS

local function faustQuery(arg)
    local cmd = "faust " .. arg
    local pipe = io.popen(cmd)
    if not pipe then
        return nil
    end

    local result = pipe:read("*l")
    pipe:close()

    if result == "" then
        return nil
    end
    
    return result
end

local faustLibDir     = faustQuery("-libdir")
local faustIncludeDir = faustQuery("-includedir")

if not faustLibDir or not faustIncludeDir then
    error("Faust not found. Ensure Faust is installed and available on PATH.", 1)
else
    -- .. add include dir into the includedirs sections
    table.insert(Plugin.sdk.static.includedirs, faustIncludeDir)
    table.insert(Plugin.sdk.shared.includedirs, faustIncludeDir)
    table.insert(Plugin.authoring.includedirs, faustIncludeDir)

    -- .. add include dir into the includedirs sections
    table.insert(Plugin.sdk.static.libdirs, faustLibDir)

    -- .. add libfaustwithllvm into the Plugin.sdk.static.links sections
    if os.isfile(faustLibDir .. "/libfaustwithllvm.lib") then -- if Faust is configured with LLVM by checking if lib file exists in libdir
        print("Faust LLVM backend detected: enabling libfaustwithllvm")
        table.insert(Plugin.sdk.static.links, "libfaustwithllvm")
    else
        print("Faust LLVM backend NOT detected: building without LLVM")
    end
end

return Plugin