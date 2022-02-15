#version 330 core
layout (location = 0) in vec2 a_Pos;

uniform mat3 u_transformMatrix;

void main() {
    vec3 pos = u_transformMatrix * vec3(a_Pos, 1.0);
    gl_Position = vec4(pos.xy, 0.0, 1.0);
}
