#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec3 fragColor;

void main()
{
	fragColor = color;

	gl_Position = vec4 (position, 0.0f, 1.0f);
}