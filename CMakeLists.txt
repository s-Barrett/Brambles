cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(BRAMBLES)

include_directories(
	src
)


add_library(Brambles
	src/Brambles/Brambles.h
	src/Brambles/Core.cpp
	src/Brambles/Entity.cpp
	src/Brambles/Core.h
	src/Brambles/Entity.h
	src/Brambles/Component.h
	src/Brambles/Component.cpp
)

add_executable(demo
	src/demo/main.cpp
	src/demo/Employee.cpp
	src/demo/Employee.h
	
)

target_link_libraries(demo Brambles)

