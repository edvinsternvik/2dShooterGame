#version 330 core
layout (location = 0) in vec2 a_Pos;
layout (location = 1) in vec2 a_TextureCoords;

uniform mat3 u_transformMatrix;

out vec2 textureCoords;

void main() {
    vec3 pos = u_transformMatrix * vec3(a_Pos, 1.0);
    textureCoords = a_TextureCoords;
    gl_Position = vec4(pos.xy, 0.0, 1.0);
}
