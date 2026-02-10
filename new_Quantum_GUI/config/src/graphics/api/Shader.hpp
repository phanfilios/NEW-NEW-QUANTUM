#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() const { glUseProgram(m_id); }
    
    
    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetLocation(name), 1, GL_FALSE, &mat[0][0]);
    }
    void setVec4(const std::string& name, const glm::vec4& vec) const {
        glUniform4f(glGetLocation(name), vec.x, vec.y, vec.z, vec.w);
    }

private:
    unsigned int m_id;
    int glGetLocation(const std::string& name) const {
        return glGetUniformLocation(m_id, name.c_str());
    }
};