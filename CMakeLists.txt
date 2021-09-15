cmake_minimum_required(VERSION 3.11)

project(phymat-jv)

set(CMAKE_CXX_STANDARD 20) # Using C++20

# Dependencies
find_package(OpenGL REQUIRED)
add_subdirectory(glfw)

include_directories(glfw/include ${OPENGL_INCLUDE_DIRS})
link_libraries(glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})

add_executable(phymat-jv
    # All source files here
    src/main.cpp
    src/Matrix.hpp
    src/Particle.hpp
    src/Vector.hpp
)