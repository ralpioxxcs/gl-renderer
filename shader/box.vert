#version 420 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

uniform mat4 transform;

out vec2 TexCoord;

void main() {
    gl_Position = transform * vec4(inPos, 1.0);
    TexCoord = inTexCoord;
}