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

file(GLOB_RECURSE PHYMAT_SRC CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

add_executable(phymat-jv ${PHYMAT_SRC})