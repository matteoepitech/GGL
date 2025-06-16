#version 330 core

layout (location = 0) in vec3 l_pos;
layout (location = 1) in vec4 l_color;

uniform vec2 u_position;
uniform vec2 u_size;

void main()
{
    vec3 scaled_pos = l_pos * vec3(u_size, 1.0);

    gl_Position = vec4(scaled_pos.xy + u_position, 0.0, 1.0);
}
