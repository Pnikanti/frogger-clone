#version 330 core

layout (location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoordinate;

out vec2 v_TextureCoordinate;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
uniform float u_AtlasRows;
uniform vec2 u_AtlasSubTextureOffset;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
	v_TextureCoordinate = ((a_TextureCoordinate + u_AtlasSubTextureOffset) / u_AtlasRows);
}