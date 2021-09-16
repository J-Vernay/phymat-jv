cmake_minimum_required(VERSION 3.11)

project(phymat-jv)

set(CMAKE_CXX_STANDARD 20) # Using C++20

# Dependencies
find_package(OpenGL REQUIRED)
add_subdirectory(glfw)
file(GLOB IMGUI_SRC src/imgui/*)
add_library(imgui ${IMGUI_SRC})

add_compile_definitions(GLFW_INCLUDE_GLU)
include_directories(glfw/include ${OPENGL_INCLUDE_DIRS})
link_libraries(glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
link_libraries(imgui)

add_executable(phymat-jv
    # All source files here
    src/main.cpp
    src/Matrix.hpp
    src/Vector.hpp
    src/Graphics.hpp
    src/Graphics.cpp
    src/Particle.hpp
)