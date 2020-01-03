#name post_vignette

// https://en.wikipedia.org/wiki/Stippling
// https://en.wikipedia.org/wiki/Ordered_dithering
// http://www.tannerhelland.com/4660/dithering-eleven-algorithms-source-code/

// https://twitter.com/_kzr/status/829621272757755905
// http://www.loopit.dk/banding_in_games.pdf
// http://www.anisopteragames.com/how-to-fix-color-banding-with-dithering/
// https://www.shadertoy.com/view/MlV3R1
// https://computergraphics.stackexchange.com/questions/3964/opengl-specular-shading-gradient-banding-issues
// https://gist.github.com/pixelmager/5d25fa32987273b9608a2d2c6cc74bfa
// https://github.com/playdeadgames/publications/blob/master/INSIDE/rendering_inside_gdc2016.pdf
// http://momentsingraphics.de/BlueNoise.html

// https://youtu.be/IviNO7iICTM
// https://digitalrune.github.io/DigitalRune-Documentation/html/fa431d48-b457-4c70-a590-d44b0840ab1e.htm
// https://ocias.com/blog/unity-stipple-transparency-shader/

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform vec2 u_ScreenSize;

out vec2 v_ScreenPos;

void main()
{
	v_ScreenPos = a_Position.xy * 2.0;
	gl_Position = vec4(v_ScreenPos, 0.01, 1.0);
}

#type fragment
#version 330 core

#define DITHER_MODE 8
#define FRAG_OUT_MODE 2

in vec2 v_ScreenPos;

uniform vec4 u_Color;

layout(location = 0) out vec4 color;

#if DITHER_MODE == 4
	// @Note: might be a texture, array, matrix
	struct ThresholdLine { float data[DITHER_MODE]; };
	uniform ThresholdLine u_Threshold[DITHER_MODE] = ThresholdLine[DITHER_MODE](
		float[4]( 0/16.,  8/16.,  2/16., 10/16.),
		float[4](12/16.,  4/16., 14/16.,  6/16.),
		float[4]( 3/16., 11/16.,  1/16.,  9/16.),
		float[4](15/16.,  7/16., 13/16.,  5/16.)
	);
#elif DITHER_MODE == 8
	// @Note: might be a texture, array
	struct ThresholdLine { float data[DITHER_MODE]; };
	uniform ThresholdLine u_Threshold[DITHER_MODE] = ThresholdLine[DITHER_MODE](
		float[8]( 0/64., 32/64.,  8/64., 40/64.,  2/64., 34/64., 10/64., 42/64.),
		float[8](48/64., 16/64., 56/64., 24/64., 50/64., 18/64., 58/64., 26/64.),
		float[8](12/64., 44/64.,  4/64., 36/64., 14/64., 46/64.,  6/64., 38/64.),
		float[8](60/64., 28/64., 52/64., 20/64., 62/64., 30/64., 54/64., 22/64.),
		float[8]( 3/64., 35/64., 11/64., 43/64.,  1/64., 33/64.,  9/64., 41/64.),
		float[8](51/64., 19/64., 59/64., 27/64., 49/64., 17/64., 57/64., 25/64.),
		float[8](15/64., 47/64.,  7/64., 39/64., 13/64., 45/64.,  5/64., 37/64.),
		float[8](63/64., 31/64., 55/64., 23/64., 61/64., 29/64., 53/64., 21/64.)
	);
#elif DITHER_MODE == -1
	uint hash(uint x) {
		x += x << 10u;
		x ^= x >>  6u;
		x += x <<  3u;
		x ^= x >> 11u;
		x += x << 15u;
		return x;
	}
	uint hash(uvec2 v) { return hash(v.x ^ hash(v.y)); }

	float hash_to_01(uint x) {
		x = (x >> 9) | 0x3f800000U;    // clamp to [1 .. 2) * (2^0)
		return uintBitsToFloat(x) - 1; // return [1 .. 2) - 1
	}
	float hash_to_radius01(uint x) {
		x = (x >> 9) | 0x40000000U;    // clamp to [1 .. 2) * (2^0)
		return uintBitsToFloat(x) - 1; // return [1 .. 2) - 1
	}

	float random_01(vec2 v) { return hash_to_01(hash(floatBitsToUint(v))); }
	float random_radius01(vec2 v) { return hash_to_radius01(hash(floatBitsToUint(v))); }
#endif

void main()
{
	float vignette_value = distance(v_ScreenPos, vec2(0.0));
	vignette_value = clamp(vignette_value - 0.4, 0.0, 1.0);
	vignette_value *= vignette_value;

	#if DITHER_MODE == 4 || DITHER_MODE == 8
		// sample the threshold matrix
		float dither_value = u_Threshold[int(gl_FragCoord.y) % DITHER_MODE]
			.data[int(gl_FragCoord.x) % DITHER_MODE];
	#elif DITHER_MODE == -1
		// sample random value
		float dither_value = random_01(gl_FragCoord.xy);
	#else
		// default to zero
		float dither_value = 0.0;
	#endif

	#if FRAG_OUT_MODE == 1
		// mask with vignette and input alpha; do not blend
		if (u_Color.a * vignette_value <= dither_value) discard;
		color = vec4(u_Color.rgb, 1.0);
	#elif FRAG_OUT_MODE == 2
		// mask with vignette only; blend by input alpha
		if (vignette_value <= dither_value) discard;
		color = u_Color;
	#elif FRAG_OUT_MODE == 3
		// control input alpha with vignette and dither; blend by the result
		// @Note: will never reach full opacity
		color = vec4(u_Color.rgb, u_Color.a * vignette_value * dither_value);
	#elif FRAG_OUT_MODE == 4
		// control input alpha with vignette mixed by dither; blend by the result
		// @Note: dither pattern is omnipresent
		color = vec4(u_Color.rgb, u_Color.a * mix(1.0, vignette_value, dither_value));
	#elif FRAG_OUT_MODE == 5
		// control input alpha with dither mixed by vignette; blend by the result
		// @Note: dither pattern is omnipresent
		color = vec4(u_Color.rgb, u_Color.a * mix(dither_value, 1.0, vignette_value));
	#elif FRAG_OUT_MODE == 6
		// jitter color with dither; blend by input alpha and vignette
		// @Note: might restrict jittering RGB or Alpha only, too
		color = vec4(u_Color.rgb, u_Color.a * vignette_value) + (dither_value - 0.5) / 8.0;
	#else
		// default; blend by input alpha and vignette
		color = vec4(u_Color.rgb, u_Color.a * vignette_value);
	#endif
}
