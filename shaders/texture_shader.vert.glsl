#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec4 color;

out vec2 TexCoords;
out vec4 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoords = texCoords;
	fragColor = color;

	gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
}