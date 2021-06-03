cmake_minimum_required(VERSION 3.19)
project(Chapter1)

set(CMAKE_CXX_STANDARD 17)


add_executable(Chapter1 training1.cpp src/glad.c)


target_link_libraries(Chapter1 -lglfw3 -lOpenGL32)
