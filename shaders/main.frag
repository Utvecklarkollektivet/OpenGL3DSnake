#version 150

out vec4 out_Color;

in vec3 exNormal;
in vec2 texCoord;

uniform sampler2D texUnit;


void main(void)
{
	const vec3 light = vec3(0.58, 0.58, 0.58);
	float shade;

	shade = dot(normalize(exNormal), light);
	//out_Color = vec4(vec3(0.0, 0.0, 1.0) + vec3(shade), 1.0);//vec4( vec3(exNormal), 1.0);
	//out_Color = vec4(1.0);
	out_Color = texture(texUnit, texCoord);
}
