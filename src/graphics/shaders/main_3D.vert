// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#version 330 core

out vec2 out_tex_coords;
out vec3 tangent_light_pos;
out vec3 pos;
out vec3 normal;

layout (location = 0) in vec3 in_pos;
layout (location = 2) in vec3 in_normal;
layout (location = 3) in vec2 in_tex_coords;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

void main(void)
{
    vec4 fragPos = vec4(model * vec4(in_pos, 1.0));
	
	out_tex_coords = in_tex_coords;
	pos = in_pos;
    normal = in_normal;

    gl_Position = proj * view * fragPos;
}
