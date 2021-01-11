#version 330 core

layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; // the tex variable has attribute position 1

out vec3 vertColor; // output a color to the fragment shader
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}  