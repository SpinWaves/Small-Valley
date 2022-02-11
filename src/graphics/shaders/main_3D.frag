// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#version 330 core

out vec4 fragColor;

uniform sampler2D tex;

in vec3 fragPos;
in vec2 texCoords;
in vec4 Color;

void main(void)
{
    fragColor = texture(tex, texCoords) / Color;
}
