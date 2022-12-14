# CMakeList.txt : CMake project for TextovaHra, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("TextovaHra")

# Add source to this project's executable.
add_executable (TextovaHra "main.cpp"  "GameLib/ANSI/ANSI.cpp" "GameLib/ANSI/ANSI.h" "GameLib/ANSI/ANSIMacros.h" "GameLib/GameLib.h" "GameLib/GameLib.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TextovaHra PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.