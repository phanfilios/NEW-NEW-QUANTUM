#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace {
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[Shader] No se pudo abrir archivo: " << path << '\n';
        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int compileShader(unsigned int type, const std::string& source, const std::string& path) {
    const char* rawSource = source.c_str();
    unsigned int shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &rawSource, nullptr);
    glCompileShader(shaderId);

    int success = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        char infoLog[512] = {0};
        glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "[Shader] Error compilando " << path << ": " << infoLog << '\n';
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
    : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath) {
    const std::string vertexCode = readFile(m_vertexPath);
    const std::string fragmentCode = readFile(m_fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        return;
    }

    const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode, m_vertexPath);
    const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode, m_fragmentPath);
    if (vertexShader == 0 || fragmentShader == 0) {
        if (vertexShader != 0) {
            glDeleteShader(vertexShader);
        }
        if (fragmentShader != 0) {
            glDeleteShader(fragmentShader);
        }
        return;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);

    int success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        char infoLog[512] = {0};
        glGetProgramInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "[Shader] Error linkeando programa: " << infoLog << '\n';
        glDeleteProgram(m_id);
        m_id = 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    if (m_id != 0) {
        glDeleteProgram(m_id);
        m_id = 0;
    }
}

void Shader::use() const {
    if (m_id != 0) {
        glUseProgram(m_id);
    }
}

bool Shader::isValid() const {
    return m_id != 0;
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
    if (m_id == 0) {
        return -1;
    }
    return glGetUniformLocation(m_id, name.c_str());
}
