#pragma once

#include <glm/glm.hpp>
#include <vector>

struct CubeInstance {
    glm::vec3 position{0.0f};
    float scale = 1.0f;
    float rotation = 0.0f;
};

class QuantumCubeField {
public:
    void init(int count);
    void update(float globalScale, float globalSpeed, float dt);

    const std::vector<CubeInstance>& instances() const { return m_instanceData; }

private:
    void setupHardwareBuffers();
    void updateHardwareBuffers();

    int m_count = 0;
    std::vector<CubeInstance> m_instanceData;
};
