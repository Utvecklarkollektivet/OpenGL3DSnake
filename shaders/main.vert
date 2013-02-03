#version 150

in vec3 in_Normal;
in vec3 in_Position;

out vec3 exNormal;

uniform mat4 projMatrix;
uniform mat4 mdlMatrix;

void main(void)
{
	mat3 normalMatrix = mat3(mdlMatrix);
	vec3 transformedNormal = normalMatrix * in_Normal;
	exNormal = transformedNormal;
	gl_Position = projMatrix * mdlMatrix * vec4(in_Position, 1.0);
	//gl_Position = projMatrix * vec4(in_Position, 1.0);
}
