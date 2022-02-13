// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#version 330 core

out vec2 out_tex_coords;
out vec4 out_color;

layout (location = 0) in vec3 in_pos;
layout (location = 2) in vec3 in_normal;
layout (location = 3) in vec2 in_tex_coords;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

vec3 lightDirection = vec3(0.3, -1.0, 0.5);
vec3 lightColour = vec3(1.0, 0.8, 0.8);
vec2 lightBias = vec2(0.3, 0.8);

//simple diffuse lighting
vec3 calculateLighting()
{
	vec3 normal = in_normal.xyz * 2.0 - 1.0; //required just because of the format the normals were stored in (0 - 1)
	float brightness = max(dot(-lightDirection, normal), 0.0);
	return (lightColour * lightBias.x) + (brightness * lightColour * lightBias.y);
}

void main(void)
{
    vec4 fragPos = vec4(model * vec4(in_pos, 1.0));
	
    out_color = vec4(calculateLighting(), 1.0);

	out_tex_coords = in_tex_coords;

    gl_Position = proj * view * fragPos;
}
