project "Console"

	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

	ConsoleIncludeDirs = {}
	ConsoleIncludeDirs["Console"] = "%{prj.location}/"
	ConsoleIncludeDirs["AnsiStyle"] = "%{prj.location}/../third-party/AnsiStyle/project"
	ConsoleIncludeDirs["Detective"] = "%{prj.location}/../third-party/Detective/project"

	files {
		"**.h",
		"**.cpp",
	}

	includedirs {
		ConsoleIncludeDirs,
	}

	links {
		"AnsiStyle"
	}