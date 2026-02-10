#include "QuantumCubeField.hpp"
#include <random>

void QuantumCubeField::init(int count) {
    m_count = count;
    m_instanceData.resize(count);

    // Inicializamos posiciones aleatorias
    std::default_random_engine generator;
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    for (int i = 0; i < count; i++) {
        m_instanceData[i].position = glm::vec3(dist(generator), dist(generator), dist(generator));
        m_instanceData[i].rotation = 0.0f;
    }

    // Generar Buffers en la GPU (VAO, VBO para malla, y el Instance VBO)
    setupHardwareBuffers();
}

void QuantumCubeField::update(float globalScale, float globalSpeed, float dt) {
    for (auto& cube : m_instanceData) {
        cube.rotation += globalSpeed * dt;
        // La escala individual se ve afectada por la escala global del Mapper
        cube.scale = globalScale; 
    }
    
    // Subir los datos actualizados a la GPU (Buffer SubData es muy eficiente)
    updateHardwareBuffers();
}