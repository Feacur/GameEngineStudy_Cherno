#name post_vignette

// https://twitter.com/_kzr/status/829621272757755905
// http://www.loopit.dk/banding_in_games.pdf
// http://www.anisopteragames.com/how-to-fix-color-banding-with-dithering/
// https://www.shadertoy.com/view/MlV3R1
// https://computergraphics.stackexchange.com/questions/3964/opengl-specular-shading-gradient-banding-issues
// https://gist.github.com/pixelmager/5d25fa32987273b9608a2d2c6cc74bfa
// https://github.com/playdeadgames/publications/blob/master/INSIDE/rendering_inside_gdc2016.pdf
// http://momentsingraphics.de/BlueNoise.html

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform vec2 u_ScreenSize;
uniform sampler2D u_Texture;

out vec2 v_TexCoord;
out vec2 v_ScreenPos;

void main()
{
	v_TexCoord = a_TexCoord * textureSize(u_Texture, 0);
	v_TexCoord.x *= u_ScreenSize.x / u_ScreenSize.y;
	v_ScreenPos = a_Position.xy * 2.0;
	gl_Position = vec4(v_ScreenPos, 0.01, 1.0);
}

#type fragment
#version 330 core

#define FRAG_OUT_MODE 1

in vec2 v_TexCoord;
in vec2 v_ScreenPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

layout(location = 0) out vec4 color;

void main()
{
	float vignette_value = distance(v_ScreenPos, vec2(0.0));
	vignette_value = clamp(vignette_value - 0.4, 0.0, 1.0);
	vignette_value *= vignette_value;

	float dither_value = texture(u_Texture, v_TexCoord).r;

	#if FRAG_OUT_MODE == 1
		// jitter color with dither; blend by input alpha and vignette
		// @Note: might restrict jittering RGB or Alpha only, too
		color = vec4(u_Color.rgb, u_Color.a * vignette_value) + (dither_value - 0.5) / 8.0;
	#else
		// default; blend by input alpha and vignette
		color = vec4(u_Color.rgb, u_Color.a * vignette_value);
	#endif
}
