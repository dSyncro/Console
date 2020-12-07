include "./third-party/Premaker/customization/solution_items.lua"

workspace "Console"

	architecture "x86_64"
	startproject "Console"

	include "./third-party/Premaker/customization/configurations.lua"

	solution_items 
	{
		".gitignore",
		".editorconfig",
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.architecture}/%{cfg.system}/%{cfg.buildcfg}"

include "third-party/Premaker"

group "Dependencies"
	include "third-party/AnsiStyle/project"
	include "third-party/Detective/project"

group ""
	include "project"