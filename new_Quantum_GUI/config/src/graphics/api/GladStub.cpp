#include "glad/glad.h"

#include <atomic>

namespace {
std::atomic<unsigned int> g_nextId{1};

void assignIds(GLsizei n, GLuint* out) {
    if (!out) {
        return;
    }
    for (GLsizei i = 0; i < n; ++i) {
        out[i] = g_nextId.fetch_add(1);
    }
}
}  // namespace

extern "C" {
void glUseProgram(GLuint) {}
void glUniformMatrix4fv(GLint, GLsizei, GLboolean, const GLfloat*) {}
void glUniform4f(GLint, GLfloat, GLfloat, GLfloat, GLfloat) {}
void glUniform1i(GLint, GLint) {}
void glUniform1f(GLint, GLfloat) {}
GLint glGetUniformLocation(GLuint, const char*) { return 0; }

void glGenFramebuffers(GLsizei n, GLuint* ids) { assignIds(n, ids); }
void glBindFramebuffer(GLenum, GLuint) {}
void glGenTextures(GLsizei n, GLuint* textures) { assignIds(n, textures); }
void glBindTexture(GLenum, GLuint) {}
void glTexImage2D(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*) {}
void glTexParameteri(GLenum, GLenum, GLint) {}
void glFramebufferTexture2D(GLenum, GLenum, GLenum, GLuint, GLint) {}
void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) { assignIds(n, renderbuffers); }
void glBindRenderbuffer(GLenum, GLuint) {}
void glRenderbufferStorage(GLenum, GLenum, GLsizei, GLsizei) {}
void glFramebufferRenderbuffer(GLenum, GLenum, GLenum, GLuint) {}
GLenum glCheckFramebufferStatus(GLenum) { return GL_FRAMEBUFFER_COMPLETE; }
void glDeleteFramebuffers(GLsizei, const GLuint*) {}
void glDeleteTextures(GLsizei, const GLuint*) {}
void glDeleteRenderbuffers(GLsizei, const GLuint*) {}

void glGenVertexArrays(GLsizei n, GLuint* arrays) { assignIds(n, arrays); }
void glGenBuffers(GLsizei n, GLuint* buffers) { assignIds(n, buffers); }
void glBindVertexArray(GLuint) {}
void glBindBuffer(GLenum, GLuint) {}
void glBufferData(GLenum, GLsizeiptr, const void*, GLenum) {}
void glEnableVertexAttribArray(GLuint) {}
void glVertexAttribPointer(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*) {}
void glClear(GLbitfield) {}
void glActiveTexture(GLenum) {}
void glDrawArrays(GLenum, GLint, GLsizei) {}
}
