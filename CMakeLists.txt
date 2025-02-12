cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(BRAMBLES)

if(MSVC)
include_directories(
 src
 contrib/cl-windows-x86_64/include
 contrib/include
)
link_directories(
 ${PROJECT_SOURCE_DIR}/contrib/cl-windows-x86_64/lib
)
set(LIBGLEW glew32)
set(LIBGL opengl32)
set(LIBAL openal32)
else()
include_directories(
 /usr/include
 src
 contrib/include
)
#link_directories(
# ${PROJECT_SOURCE_DIR}/contrib/cl-windows-x86_64/lib
#)
set(LIBGLEW GLEW)
set(LIBGL GL)
set(LIBAL openal)
endif()


add_library(rend
 src/rend/rend.h
 src/rend/Mesh.cpp
 src/rend/RenderTexture.cpp
 src/rend/RenderTexture.h
 src/rend/Utilities.cpp
 src/rend/Utilities.h
 src/rend/Mesh.h
 src/rend/Model.h
 src/rend/Model.cpp
 src/rend/Shader.h
 src/rend/Shader.cpp
 src/rend/Texture.h
 src/rend/Texture.cpp
)
target_link_libraries(rend SDL2 SDL2main ${LIBGLEW} ${LIBGL})

add_library(brambles
	src/brambles/Brambles.h
	src/brambles/Core.cpp
	src/brambles/Entity.cpp
	src/brambles/Window.h
	src/brambles/Window.cpp
	src/brambles/Core.h
	src/brambles/Entity.h
	src/brambles/Component.h
	src/brambles/Component.cpp
	src/brambles/Renderer.cpp
	src/brambles/Renderer.h
	src/brambles/Controllers/CameraController.h
	src/brambles/Controllers/CameraController.cpp
	src/brambles/Controllers/PlayerController.h
	src/brambles/Controllers/PlayerController.cpp
	src/brambles/Transform.h
	src/brambles/Transform.cpp
	src/brambles/AudioSource.h
	src/brambles/AudioSource.cpp
	src/brambles/BoxCollider.h
	src/brambles/BoxCollider.cpp
	src/brambles/RigidBody.h
	src/brambles/RigidBody.cpp
	src/brambles/Timer.h 
	src/brambles/Timer.cpp
	src/brambles/Gui.h 
	src/brambles/Gui.cpp
	src/brambles/DebugRenderer.h
	src/brambles/DebugRenderer.cpp
	src/brambles/Sound.h
	src/brambles/Sound.cpp
	src/brambles/Camera.h
	src/brambles/Camera.cpp
	src/brambles/Input.h
	src/brambles/Input.cpp
	src/brambles/Resource.h
	src/brambles/Resource.cpp
	src/brambles/Resources.h
	src/brambles/Resources/Audio.h
	src/brambles/Resources/Audio.cpp
	src/brambles/Resources/Texture.h
	src/brambles/Resources/Texture.cpp
	src/brambles/Resources/Model.h
	src/brambles/Resources/Model.cpp
	src/brambles/Resources/Shader.cpp
	src/brambles/Resources/Shader.h
)
target_link_libraries(brambles rend ${LIBAL})

add_executable(demo
  src/demo/main.cpp
)
target_link_libraries(demo brambles)

