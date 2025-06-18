#version 330 core

out vec4 frag_color;
in vec2 tex_coord;

uniform vec4 u_color;
uniform vec2 u_size;
uniform sampler2D u_sampler_texture;
uniform float u_out_width;
uniform vec4 u_out_color;

// SDF Triangle : Used for outline
float sdf_triangle(vec2 p)
{
    vec2 a = vec2(0.5, 1.0);
    vec2 b = vec2(0.0, 0.0);
    vec2 c = vec2(1.0, 0.0);
 
    vec2 e0 = b - a;
    vec2 e1 = c - b; 
    vec2 e2 = a - c;
    vec2 v0 = p - a;
    vec2 v1 = p - b;
    vec2 v2 = p - c;
    vec2 pq0 = v0 - e0 * clamp(dot(v0, e0) / dot(e0, e0), 0.0, 1.0);
    vec2 pq1 = v1 - e1 * clamp(dot(v1, e1) / dot(e1, e1), 0.0, 1.0);
    vec2 pq2 = v2 - e2 * clamp(dot(v2, e2) / dot(e2, e2), 0.0, 1.0);
    float s = sign((e0.x * e2.y - e0.y * e2.x));
    vec2 d = min(min(vec2(dot(pq0, pq0), s * (v0.x * e0.y - v0.y * e0.x)),
                     vec2(dot(pq1, pq1), s * (v1.x * e1.y - v1.y * e1.x))),
                     vec2(dot(pq2, pq2), s * (v2.x * e2.y - v2.y * e2.x)));
    return -sqrt(d.x) * sign(d.y);
}

void main()
{
    vec4 tex_sample = texture(u_sampler_texture, tex_coord);
    
    if (u_out_width > 0.0) {
        float scaled_width = u_out_width * 0.001;
        float dist = sdf_triangle(tex_coord);
        float outer_edge = scaled_width;
        float inner_edge = 0.0;
        float outline_mask = smoothstep(outer_edge + 0.001, outer_edge, abs(dist)) * (1.0 - smoothstep(inner_edge + 0.001, inner_edge, abs(dist)));
        float fill_mask = smoothstep(-0.001, 0.001, dist);
        vec4 fill_color = tex_sample * u_color;
        vec4 final_color = mix(fill_color, u_out_color, outline_mask);

        frag_color = final_color;
        frag_color.a *= max(outline_mask, fill_mask);
    } else {
        frag_color = tex_sample * u_color;
    }
}
