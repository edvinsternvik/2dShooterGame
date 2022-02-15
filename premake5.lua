workspace "2dShooterGame"
	architecture "x64"
	startproject "2dShooterGame"

	configurations { "Release" }

include "vendor/glew"
include "vendor/glfw"

project "2dShooterGame"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++20"
	systemversion "latest"

	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"vendor/glew/glew/include",
		"vendor/glfw/glfw/include",
		"vendor/glm/glm/include"
	}

	links {
		"glew",
		"glfw"
	}

	defines "GLEW_STATIC"

	filter "system:linux"
        links {
            "dl",
            "GL",
            "pthread"
        }

	filter "configurations:Release"
		optimize "On"
		runtime "Release"
