cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(BRAMBLES)



include_directories(
 src
 contrib/cl-windows-x86_64/include
 contrib/include
)

link_directories(
 ${PROJECT_SOURCE_DIR}/contrib/cl-windows-x86_64/lib
)

add_library(rend
 src/rend/rend.h
 src/rend/Mesh.cpp
 src/rend/RenderTexture.cpp
 src/rend/RenderTexture.h
 src/rend/Shader.cpp
 src/rend/Texture.cpp
 src/rend/Utilities.cpp
 src/rend/Utilities.h
 src/rend/Mesh.h
 src/rend/Model.h
 src/rend/Shader.h
 src/rend/Texture.h
 src/rend/Texture.cpp
)
target_link_libraries(rend SDL2 SDL2main GLEW32 OpenGL32)


add_library(Brambles
	src/Brambles/Brambles.h
	src/Brambles/Core.cpp
	src/Brambles/Entity.cpp
	src/Brambles/Window.h
	src/Brambles/Window.cpp
	src/Brambles/Core.h
	src/Brambles/Entity.h
	src/Brambles/Component.h
	src/Brambles/Component.cpp
)

target_link_libraries(Brambles rend)

add_executable(demo
	src/demo/main.cpp
	src/demo/Employee.cpp
	src/demo/Employee.h
	
)

target_link_libraries(demo Brambles)

