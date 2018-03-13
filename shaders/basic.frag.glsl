#version 330

in vec3 fragColor;
out vec4 outColor;

uniform float time;

void main()
{
	float variant = abs(sin(time) + cos(time));
	outColor = vec4(fragColor, 1.0f)  * variant;
}