cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(BRAMBLES)


# Define libraries for different platforms
if (EMSCRIPTEN)
    message(STATUS "Configuring for Emscripten")

    add_executable(demo
            src/demo/main.cpp
    )

    # Include directories
    include_directories(${PROJECT_SOURCE_DIR}/src)
    include_directories(${PROJECT_SOURCE_DIR}/contrib/include)

    # Set the output file suffix to .html for Emscripten
    set_target_properties(demo PROPERTIES SUFFIX ".html")

    # Correctly set linker options for Emscripten (after add_executable!)
    target_link_options(demo PRIVATE
            "SHELL:-s USE_SDL=2"
            "SHELL:-s ALLOW_MEMORY_GROWTH=1"
            "SHELL:-s NO_DISABLE_EXCEPTION_CATCHING=1"
            "SHELL:-s ASSERTIONS=1"
            "SHELL:-s FULL_ES2=1"
            "SHELL:-s MIN_WEBGL_VERSION=2"
            "SHELL:-s MAX_WEBGL_VERSION=2"
            "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/assets@/assets"
    )

    


else()
    # Standard desktop configuration (MSVC or Unix)

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
        set(LIBFREETYPE freetype)
    else()
        include_directories(
                /usr/include
                src
                contrib/include
        )
        set(LIBGLEW GLEW)
        set(LIBGL GL)
        set(LIBAL openal)
        set(LIBFREETYPE freetype)
    endif()
endif()

# Define the render library
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
        src/rend/Font.h
        src/rend/Font.cpp
        src/rend/Shader.h
        src/rend/Shader.cpp
        src/rend/Texture.h
        src/rend/Texture.cpp
)

# Link the correct libraries based on the platform
if (EMSCRIPTEN)
    target_link_libraries(rend
            SDL2
            ${LIBGLEW}
            ${LIBGL}
            ${LIBFREETYPE}
    )
else()
    target_link_libraries(rend
            SDL2
            SDL2main
            ${LIBGLEW}
            ${LIBGL}
            ${LIBAL}
            ${LIBFREETYPE}
            ${FREETYPE_LIBRARIES}
    )
endif()

# Define the Brambles library
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
        src/Brambles/Renderer.cpp
        src/Brambles/Renderer.h
        src/Brambles/Controllers/CameraController.h
        src/Brambles/Controllers/CameraController.cpp
        src/Brambles/Controllers/PlayerController.h
        src/Brambles/Controllers/PlayerController.cpp
        src/Brambles/Transform.h
        src/Brambles/Transform.cpp
        src/Brambles/LightManager.h
        src/Brambles/AudioSource.h
        src/Brambles/AudioSource.cpp
        src/Brambles/BoxCollider.h
        src/Brambles/BoxCollider.cpp
        src/Brambles/MeshCollider.h
        src/Brambles/MeshCollider.cpp
        src/Brambles/RigidBody.h
        src/Brambles/RigidBody.cpp
        src/Brambles/Physics.h
        src/Brambles/Physics.cpp
        src/Brambles/Timer.h
        src/Brambles/Timer.cpp
        src/Brambles/Gui.h
        src/Brambles/Gui.cpp
        src/Brambles/DebugRenderer.h
        src/Brambles/DebugRenderer.cpp
        src/Brambles/Sound.h
        src/Brambles/Sound.cpp
        src/Brambles/Camera.h
        src/Brambles/Camera.cpp
        src/Brambles/Font.h
        src/Brambles/Input.h
        src/Brambles/Input.cpp
        src/Brambles/Resource.h
        src/Brambles/Resource.cpp
        src/Brambles/Resources.h
        src/Brambles/Resources/Audio.h
        src/Brambles/Resources/Audio.cpp
        src/Brambles/Resources/Texture.h
        src/Brambles/Resources/Texture.cpp
        src/Brambles/Resources/Model.h
        src/Brambles/Resources/Model.cpp
        src/Brambles/Resources/Shader.cpp
        src/Brambles/Resources/Shader.h
)

# Define the demo executable
add_executable(demo
        src/demo/main.cpp
)

# Link Brambles to rend
target_link_libraries(Brambles rend ${LIBAL})

# Link demo to Brambles
target_link_libraries(demo Brambles)