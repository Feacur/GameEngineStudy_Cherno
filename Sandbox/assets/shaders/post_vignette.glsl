#name post_vignette

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

out vec2 v_ScreenPos;

void main()
{
	v_ScreenPos = a_Position.xy * 2.0;
	gl_Position = vec4(v_ScreenPos, 0.01, 1.0);
}

#type fragment
#version 330 core

in vec2 v_ScreenPos;

uniform vec4 u_Color;

uniform mat4 u_Dither = mat4(
	 0,  8,  2, 10,
	12,  4, 14,  6,
	 3, 11,  1,  9,
	15,  7, 13,  5
);

layout(location = 0) out vec4 color;

void main()
{
	float dither = u_Dither[int(gl_FragCoord.x) % 4][int(gl_FragCoord.y) % 4] / 16;

	float vignette = distance(v_ScreenPos, vec2(0.0));
	vignette = (vignette - 0.2) / 0.8;
	vignette = clamp(vignette, 0.0, 1.0);
	vignette = sqrt(vignette);
	if (vignette <= dither) discard;
	color = vec4(u_Color.rgb, u_Color.a);
}
