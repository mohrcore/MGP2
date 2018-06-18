#version 130

in vec2 uv;
in vec3 normal_f;
in vec3 light_pos_f;
in vec2 uv_of;

out vec4 color;

uniform sampler2D diffuse_map;

void main()
{
	vec4 t_color;
	t_color = texture(diffuse_map, uv /*- (uv_of / textureSize(diffuse_map, 0))*/);

	color = t_color * max(dot(normalize(light_pos_f), normalize(normal_f)), 0.0);
	//color = vec4(1.0, 0.0, 0.0, 1.0);
}