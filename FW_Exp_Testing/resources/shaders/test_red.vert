#version 330

in vec3 pos;
in vec3 normal;
in vec3 txcoord;

void main()
{
	gl_Position = vec4(0.1 * (pos.x - 0.5), 0.1 *pos.y, 0.1 * pos.z, 1.0);
}