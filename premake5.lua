require "scripts/clear"
require "scripts/project"
require "scripts/platform"
require "vendor/dependencies"

workspace "degenerate-bases-v2"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    startproject "degenerate-bases-v2"

    flags {
		"MultiProcessorCompile"
	}

output_path         = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
binaries_path       = "%{wks.location}/build/bin/" .. "%{output_path}"
intermediate_path   = "%{wks.location}/build/intermediate/" .. "%{output_path}"
vendor_path         = "%{wks.location}/vendor/"

include "degenerate-bases-v2/build.lua"