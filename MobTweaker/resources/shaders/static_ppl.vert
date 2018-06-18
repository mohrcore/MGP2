#version 130

in vec3 vertexPosition;
in vec2 uv_coord;
in vec3 normal_v;

out vec2 uv;
out vec3 normal_f;
out vec3 light_pos_f;
out vec2 uv_of;

uniform mat4 transformation_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform vec2 uv_offset;
uniform vec3 light_pos;

void main()
{
	gl_Position = projection_matrix * view_matrix *  transformation_matrix * vec4(vertexPosition, 1.0);

	uv = uv_coord;
	normal_f = (transformation_matrix * vec4(normal_v, 0.0)).xyz;
	light_pos_f = light_pos - (transformation_matrix * vec4(vertexPosition, 1.0)).xyz;
	uv_of = uv_offset;
}