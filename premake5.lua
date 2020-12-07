include "./third-party/Premaker/customization/solution_items.lua"

workspace "Console"

	architecture "x86_64"
	startproject "Console"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

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

group "Build"
	include "third-party/Premaker"

group "Dependencies"
	include "third-party/AnsiStyle/project"
	include "third-party/Detective/project"

group ""
	include "project"