#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec3 v_position;
out vec2 v_texCoord;
out vec4 v_color;

uniform mat4 u_mvp;
uniform vec2 u_LightPos;

void main()
{
	gl_Position = vec4(position, 1.0) * u_mvp;
	v_color = color;
	v_texCoord = texCoord;
	v_position = position;
}