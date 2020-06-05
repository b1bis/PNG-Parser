workspace "PNG-Parser"
	configurations {"Debug", "Release"}
	platforms {"Win32", "x64"}
	filter "platforms:Win32"
		architecture "x86"

	filter "platforms:x64"
		architecture "x86_64"

	filter {}

	output = "%{cfg.platform}/%{cfg.buildcfg}"

	targetdir ("bin/" .. output .. "/%{prj.name}")
	objdir ("bin/int/" .. output .. "/%{prj.name}")

function IncludeZlib()
	includedirs "thirdparty/zlib/"
end

function LinkZlib()
	links "zlib"
end

filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "On"

project "PNG-Parser"
	kind "StaticLib"

	language "C++"
	cppdialect "C++17"

	includedirs {
		"include/",
		"src/"
	}

	files {
		"include/**.hpp",
		"include/**.h",
		"src/**.cpp"
	}
	IncludeZlib()

function UsePNG()
	includedirs "%{wks.location}/include/"
	links "PNG-Parser"
	LinkZlib()
end

include "thirdparty/zlib/"
