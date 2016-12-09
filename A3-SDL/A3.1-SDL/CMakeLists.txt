cmake_minimum_required (VERSION 3.2)
project(sdl-demo)

# options for the C++ compiler 
set(CMAKE_CXX_STANDARD 14)

# find the SDL2 framework and set include and library path accordingly 
if (WIN32) 
   link_directories(../SDL2/lib/x86)  # customize your path here, this must be specified before add_executable
else()
   find_package(SDL2 REQUIRED)
endif()


# which sources to parse (only .cpp, no .h)
set(sources main.cpp)

add_executable        ( demo ${sources} )
target_link_libraries ( demo LINK_PUBLIC sdl2 )

if (WIN32)
   target_include_directories( demo PUBLIC ../SDL2-2.0.5/ )      # customize your path here
   target_link_libraries ( demo LINK_PUBLIC sdl2 kernel32 user32 Wldap32 shell32
                                                 winmm imm32 ole32 oleaut32 gdi32 Version )
endif()
