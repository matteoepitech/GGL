#version 330 core

layout (location = 0) in vec3 l_pos;
layout (location = 1) in vec2 l_texcoord;

uniform vec2 u_position;
uniform vec2 u_size;
uniform float u_rad;
uniform vec2 u_center;
uniform float u_out_width;

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
    vec2 dir_from_center = normalize(rotated);
    float scaled_width = u_out_width * 0.001;

    rotated += dir_from_center * scaled_width;
    rotated += u_center;
    vec2 scaled = rotated * u_size;
    vec2 final_pos = scaled + u_position;

    gl_Position = vec4(final_pos, 0.0, 1.0);
    tex_coord = l_texcoord;
}
