#version 330 core

layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the tex variable has attribute position 2 

out vec3 vertColor; // output a color to the fragment shader
out vec2 texCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y * -1, aPos.z, 1.0);
    vertColor = aColor; // Set the fragColor to the colour passed in via the location 1
    texCoord = aTexCoord;
}  