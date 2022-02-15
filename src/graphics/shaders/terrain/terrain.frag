// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#version 330 core

out vec4 final_fragColor;

uniform sampler2D tex;
uniform sampler2D normal_map;
uniform vec3 viewPos;

in vec2 out_tex_coords;
in vec3 normal;
in vec3 pos;

vec3 lightColor = vec3(1.0, 0.8, 0.8);
vec3 lightDir = normalize(vec3(-0.2, -1.0, -0.3));

vec3 calculateLighting()
{
    /*
    vec3 norm = texture(normal_map, out_tex_coords).rgb;
    norm = normalize(norm * 2.0 - 1.0);
    */
    vec3 norm = normalize(normal);
	// ambient
	vec3 ambient = 0.3 * lightColor;
    // diffuse
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - pos);
    vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color  
    
    return (ambient + diffuse + specular);
}

void main(void)
{
    float gamma = 1.2;
    vec4 fragColor = texture(tex, out_tex_coords) * vec4(calculateLighting(), 1.0);
    final_fragColor.rgb = pow(fragColor.rgb, vec3(1.0/gamma));
}
