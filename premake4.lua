solution "DASH_TOOLS"
  configurations { "Debug", "Release" }

  targetdir "bin/"

  if _ACTION == "clean" then
    os.rmdir("bin/")
    os.rmdir("build/")
  end

  objdir "build/obj"
  location "build/"
  includedirs { "." }

project "yuvPatterer"
  language "C++"
  kind "ConsoleApp"
  files { "src/**.cpp" }

  links { "boost_system",
          "boost_program_options" }

configuration { "Debug*" }
    defines { "_DEBUG", "DEBUG" }
    flags   { "Symbols" }
    targetname ( "yuvPatterer_d" )

  configuration { "Release*" }
    defines { "NDEBUG" }
    flags   { "Optimize" }
    targetname ( "yuvPatterer" )

