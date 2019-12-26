#name renderer2d_vignette

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

layout(location = 0) out vec4 color;

void main()
{
	float vignette = 1.0 - distance(v_ScreenPos * 0.8, vec2(0.0));
	vignette = clamp(vignette, 0.0, 1.0);
	vignette = sqrt(vignette);
	color = texture(u_Texture, v_TexCoord) * u_Color * vignette;
}
