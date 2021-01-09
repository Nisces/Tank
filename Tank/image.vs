#version 330 core
layout (location = 0) in vec4 pos;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoord = pos.zw;
    gl_Position = projection * model * vec4(pos.xy, 1.0, 1.0);
}