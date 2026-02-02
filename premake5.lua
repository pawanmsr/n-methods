workspace "n-methods"
   configurations "Release"
   location "build"

project "library"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs "include"
   files "src/*.cpp"

   libdirs "lib"

   filter "configurations:Release"
      defines "NDEBUG"
      optimize "On"

project "simple-test"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs "include"
   files "test/simple_test.cpp"

   links "library"
