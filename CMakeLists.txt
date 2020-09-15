cmake_minimum_required(VERSION 3.17)
project(LorenzAttractor)

set(CMAKE_CXX_STANDARD 14)
add_executable(LorenzAttractor main.cpp ./LA/LorenzAttractor.cpp)
include_directories(/usr/local/include)
include_directories(/Users/gintas.palionis/CLionProjects/LorenzAttractor/LA)


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
find_package(TGUI 0.8.8 REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries (LorenzAttractor ${TGUI_LIBRARY} sfml-graphics sfml-window sfml-system )