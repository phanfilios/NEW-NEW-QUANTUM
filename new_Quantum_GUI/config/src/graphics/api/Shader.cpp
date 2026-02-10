#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
    : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath) {
    // Placeholder: creación real de programa GLSL pendiente.
    m_id = 0;
}

Shader::~Shader() = default;

void Shader::use() const {
    glUseProgram(m_id);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& vec) const {
    glUniform4f(glGetLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetLocation(name), value);
}

int Shader::glGetLocation(const std::string& name) const {
    return glGetUniformLocation(m_id, name.c_str());
}
