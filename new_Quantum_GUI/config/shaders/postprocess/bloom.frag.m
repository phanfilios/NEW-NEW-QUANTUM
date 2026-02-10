#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_SceneTexture;
uniform float u_BloomIntensity; // Del VisualMapper

void main() {
    vec3 sceneColor = texture(u_SceneTexture, TexCoords).rgb;

    // Un umbral simple para extraer las partes brillantes
    vec3 brightColor = max(sceneColor - vec3(0.5), vec3(0.0));
    
    // Aquí iría una lógica más compleja de blur si tuvieras un shader de blur
    // Por ahora, solo escalamos el color brillante y lo añadimos a la escena

    vec3 bloomEffect = brightColor * u_BloomIntensity * 2.0; // Multiplicador de intensidad
    
    FragColor = vec4(sceneColor + bloomEffect, 1.0);
}