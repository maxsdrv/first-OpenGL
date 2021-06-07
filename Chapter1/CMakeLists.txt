cmake_minimum_required(VERSION 3.19)
project(Chapter1)

set(CMAKE_CXX_STANDARD 17)


add_executable(Chapter1 lesson2.cpp src/glad.c)

#libraries for linux, just comment out it if you need
#target_link_libraries(Chapter1 -lglfw -lGL -lX11 -lpthread -lXrandr -ldl)

#libraries for windows, just comment out it if you need
target_link_libraries(Chapter1 -lglfw3 -lfreeglut -lOpenGL32)

