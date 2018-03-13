#version 330

in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D texImage;

void main()
{
	outColor = texture(texImage, TexCoords);
}