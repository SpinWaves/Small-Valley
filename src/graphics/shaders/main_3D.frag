#version 330 core

out vec4 fragColor;

uniform sampler2D tex;

in vec3 fragPos;
in vec2 texCoords;
in vec4 Color;

void main(void)
{
    fragColor = texture(tex, texCoords) * Color;
}
