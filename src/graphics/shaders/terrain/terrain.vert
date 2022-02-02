#version 330 core

flat out vec3 color;

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec4 in_color;
layout(location = 2) in vec4 in_normal;

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
	
	vec3 lighting = calculateLighting();
    color = in_color.rgb * lighting;

    gl_Position = proj * view * fragPos;
}
