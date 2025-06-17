#version 330 core

layout (location = 0) in vec3 l_pos;
layout (location = 1) in vec2 l_texcoord;

uniform vec2 u_position;
uniform vec2 u_size;
uniform float u_rad;
uniform vec2 u_center;

out vec2 tex_coord;

void main()
{
    vec2 pos = l_pos.xy - u_center;
    float cos_r = cos(u_rad);
    float sin_r = sin(u_rad);
    vec2 rotated = vec2(
        pos.x * cos_r - pos.y * sin_r,
        pos.x * sin_r + pos.y * cos_r
    );
    rotated.x = rotated.x + u_center.x;
    rotated.y = rotated.y + u_center.y;
    vec2 scaled = rotated * u_size;
    vec2 final_pos = scaled + u_position;
    gl_Position = vec4(final_pos, 0.0, 1.0);
    tex_coord = l_texcoord;
}
