#version 330 core
layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_textureCoords;

uniform mat3 u_transformMatrix;
uniform vec2 u_pos;
uniform vec2 u_cameraPos;

out vec2 textureCoords;

void main() {
    textureCoords = a_textureCoords;
    
    vec3 pos = u_transformMatrix * vec3(a_pos, 1.0);
    pos += vec3(u_cameraPos, 0.0);
    gl_Position = vec4(pos.xy * 2.0 - vec2(1.0), pos.z, 1.0);
}

