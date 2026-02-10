#include "QuantumCubeField.hpp"

#include <random>

void QuantumCubeField::init(int count) {
    m_count = count;
    m_instanceData.resize(count);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    for (int i = 0; i < count; i++) {
        m_instanceData[i].position = glm::vec3(dist(generator), dist(generator), dist(generator));
        m_instanceData[i].rotation = 0.0f;
        m_instanceData[i].scale = 1.0f;
    }

    setupHardwareBuffers();
}

void QuantumCubeField::update(float globalScale, float globalSpeed, float dt) {
    for (auto& cube : m_instanceData) {
        cube.rotation += globalSpeed * dt;
        cube.scale = globalScale;
    }

    updateHardwareBuffers();
}

void QuantumCubeField::setupHardwareBuffers() {
    // Placeholder de upload GPU.
}

void QuantumCubeField::updateHardwareBuffers() {
    // Placeholder de update GPU.
}
