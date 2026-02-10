#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D u_SceneTexture;
uniform float u_BloomIntensity;
void main() {
    vec3 sceneColor = texture(u_SceneTexture, TexCoords).rgb;
    vec3 brightColor = max(sceneColor - vec3(0.5), vec3(0.0));
    vec3 bloomEffect = brightColor * u_BloomIntensity * 2.0;
    FragColor = vec4(sceneColor + bloomEffect, 1.0);
}
