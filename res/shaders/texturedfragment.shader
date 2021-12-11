#version 330 core

out vec4 fragColor;

in vec2 v_TextureCoordinate;

uniform vec3 u_Color;
uniform sampler2D u_Texture;

void main()
{
	fragColor = texture(u_Texture, v_TextureCoordinate) * vec4(u_Color, 1.0f);
}