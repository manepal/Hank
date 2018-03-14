#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoords = texCoords;

	gl_Position = projection *view * model * vec4(position, 0.0f, 1.0f);
}