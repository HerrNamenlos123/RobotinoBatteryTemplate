
-- Retrieve the project name
newoption { trigger = "projectname", description = "Name of the generated project" }
local projectName = _OPTIONS["projectname"]
if projectName == nil then print("The project name was not specified! --projectname=YourApplication") end

-- Main Solution
workspace (projectName)
    configurations { "Debug", "Release", "Deploy" }

    platforms { "x64" }
    defaultplatform "x64"
    startproject (projectName)

-- Actual project
project (projectName)
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build"
    targetname (projectName)

    system "Windows"
    entrypoint "mainCRTStartup"
    architecture "x86_64"

    pchheader "pch.h"
    pchsource "src/pch.cpp"

    -- Configuration filters, filters are active up to the next filter statement
    -- Indentation is purely visual
    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG", "NDEPLOY", "ALLEGRO_STATICLINK" }
        kind "ConsoleApp"
        runtime "Debug"
        symbols "On"
        libdirs { "$(BATTERY_ENGINE_DEBUG_LINK_DIRS)" }
        links { "$(BATTERY_ENGINE_DEBUG_LINK_FILES)" }
        links { "$(ROBOTINOLIB_DEBUG_LINKS)" }
        targetdir (_SCRIPT_DIR .. "/bin/Debug")

    filter "configurations:Release"
        defines { "NDEBUG", "NDEPLOY", "ALLEGRO_STATICLINK" }
        kind "ConsoleApp"
        runtime "Release"
        optimize "On"
        libdirs { "$(BATTERY_ENGINE_RELEASE_LINK_DIRS)" }
        links { "$(BATTERY_ENGINE_RELEASE_LINK_FILES)" }
        links { "$(ROBOTINOLIB_RELEASE_LINKS)" }
        targetdir (_SCRIPT_DIR .. "/bin/Release")

    filter "configurations:Deploy"
        defines { "NDEBUG", "DEPLOY", "ALLEGRO_STATICLINK" }
        kind "WindowedApp"
        runtime "Release"
        optimize "On"
        libdirs { "$(BATTERY_ENGINE_DEPLOY_LINK_DIRS)" }
        links { "$(BATTERY_ENGINE_DEPLOY_LINK_FILES)" }
        links { "$(ROBOTINOLIB_DEPLOY_LINKS)" }
        targetdir (_SCRIPT_DIR .. "/bin/Deploy")

    filter {}
    
    includedirs { _SCRIPT_DIR .. "/include", "$(BATTERY_ENGINE_INCLUDE_DIRECTORY)" }
    includedirs { _SCRIPT_DIR .. "/include", "$(ROBOTINOLIB_INCLUDE_DIRECTORY)" }
    files { _SCRIPT_DIR .. "/include/**", _SCRIPT_DIR .. "/src/**" }

    linkoptions { "/IGNORE:4099" }  -- Ignore warning that no .pdb file is found for debugging
