#version 330 core

in vec4 v_color;
out vec4 frag_color;
uniform vec4 u_color;

void main()
{
    frag_color = v_color;
}
