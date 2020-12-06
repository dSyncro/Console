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

include "third-party/Premaker"
include "third-party/AnsiStyle/project"
include "project"