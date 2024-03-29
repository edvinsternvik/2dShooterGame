#version 330 core
layout (location = 0) in vec2 a_Pos;
layout (location = 1) in vec2 a_TextureCoords;

uniform vec2 u_spriteOffsets[256];
uniform vec2 u_tileScale;
uniform vec2 u_spriteScale;
uniform ivec2 u_nSprites;
uniform vec2 u_cameraPos;

out vec2 textureCoords;

void main() {
    textureCoords = a_TextureCoords * u_spriteScale + u_spriteOffsets[gl_InstanceID];
    
    vec2 spritePos = vec2(gl_InstanceID % u_nSprites.x, gl_InstanceID / u_nSprites.x) * u_tileScale;
    vec3 pos = vec3(a_Pos * u_tileScale + spritePos, 1.0);
    pos += vec3(u_cameraPos, 0.0);
    gl_Position = vec4(pos.xy * 2.0 - vec2(1.0), 0.0, 1.0);
}
