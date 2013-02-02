#version 150

out vec4 out_Color;

in vec3 exNormal;

void main(void)
{
	const vec3 light = vec3(0.2, 0.2, 0.2);
	float shade;

	shade = dot(normalize(exNormal), light);
	out_Color = vec4(vec3(0.0, 0.0, 1.0) + vec3(shade), 1.0);//vec4( vec3(exNormal), 1.0);
}
