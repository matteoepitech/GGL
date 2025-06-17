#version 330 core

out vec4 frag_color;
in vec2 tex_coord;

uniform vec4 u_color;
uniform sampler2D u_sampler_texture;

uniform float u_out_width;
uniform vec4 u_out_color;

void main()
{
  frag_color = texture(u_sampler_texture, tex_coord) * u_color;
}
