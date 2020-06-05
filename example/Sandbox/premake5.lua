project "Sandbox"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"
	
	files {"**.cpp", "src/**"}
	includedirs {
		"include/"
	}
	UsePNG()
	