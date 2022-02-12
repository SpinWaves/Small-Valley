// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#version 330 core

out vec4 fragColor;

uniform sampler2D tex;

in vec2 out_tex_coords;
in vec4 out_color;

void main(void)
{
    fragColor = texture(tex, out_tex_coords) * out_color;
}
