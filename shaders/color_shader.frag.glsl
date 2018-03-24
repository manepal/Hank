#version 330

in vec2 TexCoords;
in vec4 fragColor;

out vec4 outColor;

void main()
{
	outColor = fragColor;
}