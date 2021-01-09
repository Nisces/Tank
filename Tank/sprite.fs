#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D sprite;
uniform int attacked;

void main()
{
    if(attacked == 0)
        FragColor = texture(sprite, TexCoord);
    else
        FragColor = mix(texture(sprite, TexCoord), vec4(1.0, 1.0, 1.0, texture(sprite, TexCoord).w), 0.5);
}