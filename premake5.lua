workspace "PNG-Parser"
	configurations {"Debug", "Release"}
	platforms {"Win32", "x64"}

	filter "platforms:Win32"
		architecture "x86"

	filter "platforms:x64"
		architecture "x86_64"

output = "%{cfg.buildcfg}-%{cfg.architecture}"

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

	targetdir ("bin/" .. output .. "/%{prj.name}")
	objdir ("bin/int/" .. output .. "/%{prj.name}")

	includedirs {
		"include/",
		"src/"
	}

	files 
	{
		"**.hpp",
		"**.h",
		"**.cpp"
	}

function UsePNG()
	includedirs "PNG-Parser/include"
end