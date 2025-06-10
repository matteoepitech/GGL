cmake_minimum_required(VERSION 3.16)
project(ggl LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE GGL_SRC src/*.c)
add_library(ggl SHARED ${GGL_SRC})

target_include_directories(ggl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
)

add_library(glad STATIC
    external/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(ggl PUBLIC
    glad
    glfw
    OpenGL::GL
)

if(APPLE)
    target_link_libraries(ggl PUBLIC
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo"
    )
endif()
