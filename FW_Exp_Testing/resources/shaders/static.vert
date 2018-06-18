#version 130

in vec3 vertexPosition;
in vec2 uv_coord;

out vec2 uv;
out vec2 uv_of;
out vec2 br_m;

uniform mat4 transformation_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main()
{
	gl_Position = projection_matrix * view_matrix *  transformation_matrix * vec4(vertexPosition, 1.0);

	uv = uv_coord;
}