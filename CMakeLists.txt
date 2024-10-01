cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(MAINENGINE)

include_directories(
	src
)


add_library(mainEngine
 src/mainEngine/Core.h
 src/mainEngine/Core.cpp
)

add_executable(demo
 src/demo/main.cpp
 src/demo/TestScene.cpp
 src/demo/TestScene.h
)

target_link_libraries(demo mainEngine)

