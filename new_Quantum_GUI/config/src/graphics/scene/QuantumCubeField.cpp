#include "QuantumCubeField.hpp"

#include <glad/glad.h>

#include <random>
#include <vector>

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
    updateHardwareBuffers();
}

void QuantumCubeField::update(float globalScale, float globalSpeed, float dt) {
    for (auto& cube : m_instanceData) {
        cube.rotation += globalSpeed * dt;
        cube.scale = globalScale;
    }

    updateHardwareBuffers();
}

void QuantumCubeField::draw() const {
    if (m_vao == 0 || m_count <= 0) {
        return;
    }

    glBindVertexArray(m_vao);
    glDrawArrays(GL_POINTS, 0, m_count);
    glBindVertexArray(0);
}

void QuantumCubeField::shutdown() {
    if (m_vbo != 0) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }

    if (m_vao != 0) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}

void QuantumCubeField::setupHardwareBuffers() {
    if (m_vao != 0 || m_vbo != 0) {
        shutdown();
    }

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_instanceData.size() * sizeof(glm::vec3)), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void QuantumCubeField::updateHardwareBuffers() {
    if (m_vbo == 0 || m_instanceData.empty()) {
        return;
    }

    std::vector<glm::vec3> positions;
    positions.reserve(m_instanceData.size());

    for (const auto& cube : m_instanceData) {
        positions.push_back(cube.position * cube.scale);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(positions.size() * sizeof(glm::vec3)), positions.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
