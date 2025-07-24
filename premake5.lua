workspace "n-methods"
   configurations {"Release"}
   location "build"

project "library"
   kind "SharedLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs "include"
   files "src/*.cpp"

   libdirs "lib"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "simple-test"
   kind "StaticLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs "include"
   files "test/simple_test.cpp"

   link "library"
