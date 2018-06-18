#version 130

in vec2 uv;
in vec2 uv_of;
in vec2 br_m;

out vec4 color;

uniform sampler2D diffuse_map;
uniform vec2 uv_offset;
uniform vec2 uv_crop;
uniform vec2 br_margin;
uniform bool br_margin_set;

void main()
{
	vec2 mod_uv;
	if(br_margin_set)
	{
		mod_uv = mod(uv, vec2(0.5, br_margin / textureSize(diffuse_map, 0)));
	}
	else
	{
		mod_uv = uv;
	}

	if(uv_crop != vec2(0.0, 0.0))
	{
		mod_uv = mod_uv * (uv_crop / textureSize(diffuse_map, 0));
	}

	color = texture(diffuse_map, mod_uv - (uv_offset / textureSize(diffuse_map, 0)));
}