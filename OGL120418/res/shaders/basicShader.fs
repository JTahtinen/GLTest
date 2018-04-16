#version 330 core

in vec3 v_position;
in vec4 v_color;
in vec2 v_texCoord;

uniform vec4 u_Color;
uniform vec2 u_LightPos;
uniform sampler2D u_Texture;

out vec4 color;


void main()
{
    float intensity = 1.0 / length(u_LightPos - v_position.xy);
    color = (v_color * texture(u_Texture, v_texCoord)) * u_Color * intensity;
    //color = vec4(1.0, 0, 0, 1.0) * intensity;
    //color = v_color; //u_Color * (100.0 / distance(gl_FragCoord.xy, u_LightPos));
}