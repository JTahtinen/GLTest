#version 330 core

in vec4 v_position;
in vec4 v_color;
in vec2 v_texCoord;

uniform vec4 u_Color;
uniform vec2 u_LightPos;
uniform vec3 u_LightPos3D;
uniform float u_LightIntensity;
uniform mat4 u_ModelMatrix;
uniform sampler2D u_Texture;

out vec4 color;


void main()
{
    float lightDistance = length(vec4(u_LightPos3D, 1.0) - u_ModelMatrix * v_position);
    float intensity = u_LightIntensity / (lightDistance * lightDistance);//(lightDistance * lightDistance);
    color = (v_color * texture(u_Texture, v_texCoord)) * u_Color * intensity;
    //color = v_color * u_Color * intensity;
}