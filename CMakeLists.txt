cmake_minimum_required(VERSION 3.28)

add_subdirectory(lib/glfw-3.4)
add_subdirectory(lib/glm-1.0.1)
project(snek)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} src/main.cpp
        src/graphics/glad.c
        include/stb_image.h
        src/graphics/stb_image.cpp
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/entities/Player.cpp
        src/entities/Player.h
        src/entities/Enemy.cpp
        src/entities/Enemy.h)

set(ASSETS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets)
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_DIRECTORY="${ASSETS_DIRECTORY}")
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        COMMENT "Copying assets to build directory")

add_dependencies(${PROJECT_NAME} copy_assets)

link_directories(lib/glfw-3.4/src)
include_directories(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glm ${GLM_LIBRARIES})


