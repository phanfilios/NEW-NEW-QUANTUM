cmake_minimum_required(VERSION 3.16)
project(SICP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sicp_app
  new_Quantum_GUI/config/src/main.cpp
  new_Quantum_GUI/config/src/core/Engine.cpp
  new_Quantum_GUI/config/src/core/Kernel.cpp
  new_Quantum_GUI/config/src/science/neuro/NeuroInterface.cpp
  new_Quantum_GUI/config/src/science/neuro/SignalProcessor.cpp
  new_Quantum_GUI/config/src/science/quantum/QuantumState.cpp
  new_Quantum_GUI/config/src/graphics/api/Framebuffer.cpp
  new_Quantum_GUI/config/src/graphics/api/Shader.cpp
  new_Quantum_GUI/config/src/graphics/api/GladStub.cpp
  new_Quantum_GUI/config/src/graphics/scene/QuantumCubeField.cpp
  new_Quantum_GUI/config/src/graphics/renderer/Renderer.cpp
)

target_include_directories(sicp_app PRIVATE
  new_Quantum_GUI/config/src
)

message(STATUS "Building sicp_app with local GL/GLM stubs for Paso 1 executable smoke tests.")
