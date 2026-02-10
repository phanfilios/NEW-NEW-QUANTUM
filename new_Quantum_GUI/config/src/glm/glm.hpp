#pragma once

#include <algorithm>

namespace glm {

struct vec3 {
    float x;
    float y;
    float z;

    constexpr vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr explicit vec3(float v) : x(v), y(v), z(v) {}
    constexpr vec3(float xIn, float yIn, float zIn) : x(xIn), y(yIn), z(zIn) {}
};

struct vec4 {
    float x;
    float y;
    float z;
    float w;

    constexpr vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr explicit vec4(float v) : x(v), y(v), z(v), w(v) {}
    constexpr vec4(float xIn, float yIn, float zIn, float wIn) : x(xIn), y(yIn), z(zIn), w(wIn) {}
};

struct mat4 {
    float data[4][4];

    constexpr explicit mat4(float diagonal = 1.0f)
        : data{{diagonal, 0.0f, 0.0f, 0.0f},
               {0.0f, diagonal, 0.0f, 0.0f},
               {0.0f, 0.0f, diagonal, 0.0f},
               {0.0f, 0.0f, 0.0f, diagonal}} {}

    constexpr float* operator[](int i) { return data[i]; }
    constexpr const float* operator[](int i) const { return data[i]; }
};

inline float smoothstep(float edge0, float edge1, float x) {
    const float denom = (edge1 - edge0);
    if (denom == 0.0f) {
        return x < edge0 ? 0.0f : 1.0f;
    }
    float t = (x - edge0) / denom;
    t = std::clamp(t, 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

}  // namespace glm
