cmake_minimum_required(VERSION 3.16)
project(SICP_Quantum_GUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(sicp_gui
    src/main.cpp
    src/core/Engine.cpp
    src/core/Kernel.cpp
    src/graphics/api/Framebuffer.cpp
    src/graphics/api/Shader.cpp
    src/graphics/renderer/Renderer.cpp
    src/graphics/scene/QuantumCubeField.cpp
    src/science/neuro/NeuroInterface.cpp
    src/science/neuro/SignalProcessor.cpp
    src/science/quantum/QuantumState.cpp
)

target_include_directories(sicp_gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(sicp_gui PRIVATE glfw glm::glm)

# GLAD must be provided by the environment/toolchain.
# Example: add_subdirectory(external/glad) + target_link_libraries(sicp_gui PRIVATE glad)
