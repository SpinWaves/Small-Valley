#version 330 core

out vec4 fragColor;

uniform sampler2D tex;
uniform bool isTexture;

in vec3 fragPos;
in vec2 texCoords;
in vec4 Color;

void main(void)
{
    if(isTexture)
        fragColor = texture(tex, texCoords);
    else
        fragColor = Color;
}
