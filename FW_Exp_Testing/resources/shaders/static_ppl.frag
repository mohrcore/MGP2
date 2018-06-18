#version 130

in vec2 uv;
in vec3 normal_f;
in vec3 light_pos_f [12];
in vec2 uv_of;

out vec4 color;

uniform int lights_cnt;
uniform sampler2D diffuse_map;
uniform vec3 lights_col [12];
uniform vec3 ambient;

void main()
{
	vec4 t_color;
	t_color = texture(diffuse_map, uv /*- (uv_of / textureSize(diffuse_map, 0))*/);

	vec3 l_col = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < lights_cnt; i++)
	{
		float light_str = max(dot(normalize(light_pos_f[i]), normalize(normal_f)), 0.0);
		l_col += t_color.rgb * lights_col[i] * vec3(max(ambient.r, light_str), max(ambient.g, light_str), max(ambient.b, light_str));
	}


	color = vec4(l_col, 1.0);
	//color = vec4(t_color.rgb, 1.0);
}