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
/*
out vec3 tangent_view_pos;
out vec3 tangent_frag_pos;
*/
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
/*
	mat3 normal_matrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
*/
    gl_Position = proj * view * fragPos;
}
