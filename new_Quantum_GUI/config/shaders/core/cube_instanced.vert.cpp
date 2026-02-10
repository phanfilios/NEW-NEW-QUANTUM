#version 330 core
layout (location = 0) in vec3 aPos;       // Datos del cubo base
layout (location = 3) in vec3 iPos;       // Posición de la instancia (Instanced)
layout (location = 4) in float iScale;    // Escala de la instancia (Instanced)
layout (location = 5) in float iRot;      // Rotación de la instancia (Instanced)

uniform mat4 u_ViewProjection;

void main() {
    // Matriz de rotación simple en el eje Y aplicada en el Shader
    mat4 rotation = mat4(
        cos(iRot), 0, sin(iRot), 0,
        0, 1, 0, 0,
        -sin(iRot), 0, cos(iRot), 0,
        0, 0, 0, 1
    );

    vec3 worldPos = (rotation * vec4(aPos * iScale, 1.0)).xyz + iPos;
    gl_Position = u_ViewProjection * vec4(worldPos, 1.0);
}