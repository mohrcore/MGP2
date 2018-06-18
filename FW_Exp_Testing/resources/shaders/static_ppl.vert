#version 130

in vec3 vertexPosition;
in vec3 normal_v;
in vec2 uv_coord;

out vec2 uv;
out vec3 normal_f;
out vec3 light_pos_f [12];
out vec2 uv_of;

uniform mat4 transformation_matrix;
uniform mat4 ws_transformation_matrix;
//uniform mat4 projection_matrix;
//uniform mat4 view_matrix;
uniform vec2 uv_offset;
uniform int lights_cnt;
uniform vec3 lights_pos [12];


void main()
{
	//gl_Position = projection_matrix * view_matrix * transformation_matrix * vec4(vertexPosition, 1.0);
	gl_Position = transformation_matrix * vec4(vertexPosition, 1.0);
	//gl_Position = vec4(vertexPosition, 1.0);

	uv = uv_coord;
	normal_f = (ws_transformation_matrix * vec4(normal_v, 0.0)).xyz;
	uv_of = uv_offset;

	for(int i = 0; i < lights_cnt; i++)
		light_pos_f[i] = lights_pos[i] - (ws_transformation_matrix * vec4(vertexPosition, 1.0)).xyz;
}