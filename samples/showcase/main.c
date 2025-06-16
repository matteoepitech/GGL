/*
** GGL PROJECT, 2025
** main
** File description:
** Animated Showcase - Aligned Version
*/
#include "ggl.h"
#include "misc/ggl_types.h"
#include "modules/ggl_core.h"
#include "modules/ggl_renderer.h"
#include "modules/ggl_texture.h"

#define WIDTH 1280
#define HEIGHT 720
#define C_ONE  (ggl_color){255, 242, 224}
#define C_TWO  (ggl_color){192, 201, 238}
#define C_THR  (ggl_color){162, 170, 219}
#define C_FOUR (ggl_color){137, 138, 196}

#define MARGIN_LEFT 110
#define MARGING_TOP 70
#define SPACING_X 150

float elapsed = 0.0f;

static float oscillate(float t, float min, float max, float speed)
{
    return min + (sinf(t * speed) * 0.5f + 0.5f) * (max - min);
}

static ggl_color shift_color(float t)
{
    return (ggl_color){
        (int) (sinf(t * 0.7f) * 20 + C_THR._r),
        (int) (sinf(t * 1.3f + 2.0f) * 20 + C_THR._g),
        (int) (sinf(t * 2.0f + 4.0f) * 20 + C_THR._b),
    };
}

int main(int argc, char *argv[])
{
    ggl_context *ctx = ggl_init();
    float pos1_x = MARGIN_LEFT;
    float pos2_x = MARGIN_LEFT + SPACING_X;
    float pos3_x = MARGIN_LEFT + SPACING_X * 2;
    float pos4_x = MARGIN_LEFT + SPACING_X * 3;
    float pos5_x = MARGIN_LEFT + SPACING_X * 4;
    float pos6_x = MARGIN_LEFT + SPACING_X * 5;
    float pos7_x = MARGIN_LEFT + SPACING_X * 6;
    float pos8_x = MARGIN_LEFT + SPACING_X * 7;
    ggl_texture *texture = ggl_texture_create("./tree.jpeg");
    ggl_texture *texture_misc = ggl_texture_create("./misc.jpeg");
    
    if (!ctx)
        return GGL_KO;
    
    ggl_window_create(ctx, "GGL Showcase", (ggl_vector2i){WIDTH, HEIGHT});
    ggl_setup_debug_close(ctx);

    ggl_rectangle *cursor = ggl_rectangle_create(
        (ggl_vector2f) {0, 0},
        (ggl_vector2f) {20, 20},
        GGL_COLOR_RED);

    ggl_triangle *tri = ggl_triangle_create(
        (ggl_vector2f){pos1_x, MARGING_TOP},
        (ggl_vector2f){80, 80}, 
        C_TWO);

    ggl_rectangle *rect = ggl_rectangle_create(
        (ggl_vector2f){pos2_x - 60, MARGING_TOP - 40}, 
        (ggl_vector2f){120, 80}, 
        C_FOUR);
    
    ggl_circle *circle = ggl_circle_create(
        (ggl_vector2f){pos3_x, MARGING_TOP}, 
        40, 
        32, 
        C_THR);

    ggl_convex *convex = ggl_convex_create((ggl_vector2f){pos4_x, MARGING_TOP});
    ggl_convex_add_vertex(convex, (ggl_vector2f){0, -40}, C_FOUR);
    ggl_convex_add_vertex(convex, (ggl_vector2f){40, -10}, C_FOUR);
    ggl_convex_add_vertex(convex, (ggl_vector2f){30, 40}, C_FOUR);
    ggl_convex_add_vertex(convex, (ggl_vector2f){-30, 40}, C_FOUR);
    ggl_convex_add_vertex(convex, (ggl_vector2f){-40, -10}, C_FOUR);
    
    ggl_triangle *tri_tex = ggl_triangle_create(
        (ggl_vector2f){pos5_x - 50, MARGING_TOP + 40},
        (ggl_vector2f){80, 80}, 
        GGL_COLOR_WHITE);
    ggl_triangle_set_texture(tri_tex, texture);

    ggl_rectangle *rect_tex = ggl_rectangle_create(
        (ggl_vector2f){pos6_x - 60, MARGING_TOP - 40}, 
        (ggl_vector2f){120, 80}, 
        GGL_COLOR_WHITE);
    ggl_rectangle_set_texture(rect_tex, texture);
    
    ggl_rectangle *rect_tex_bis = ggl_rectangle_create(
        (ggl_vector2f){pos7_x - 60, MARGING_TOP - 40}, 
        (ggl_vector2f){120, 80}, 
        GGL_COLOR_WHITE);
    ggl_rectangle_set_texture(rect_tex_bis, texture);
    
    ggl_rectangle *rect_rot = ggl_rectangle_create(
        (ggl_vector2f){pos8_x - 60, MARGING_TOP - 40}, 
        (ggl_vector2f){120, 80}, 
        C_TWO);

    while (ggl_window_should_close(ctx) == GGL_FALSE) {
        ggl_window_clear(C_ONE);
        elapsed += 0.01f;

        ggl_triangle_set_position(tri, (ggl_vector2f){
            pos1_x + oscillate(elapsed, -70, 0, 1.5f), 
            MARGING_TOP + 40
        });
        ggl_triangle_render(ctx, tri);

        ggl_rectangle_set_color(rect, shift_color(elapsed));
        ggl_rectangle_render(ctx, rect);

        ggl_circle_set_radius(circle, (int) oscillate(elapsed, 15, 60, 2.5));
        ggl_circle_render(ctx, circle);

        for (int i = 0; i < 5; ++i) {
            ggl_convex_set_vertex_color(convex, i, shift_color(elapsed + i * 0.5f));
        }
        ggl_convex_render(ctx, convex);

        ggl_triangle_render(ctx, tri_tex);
        ggl_rectangle_render(ctx, rect_tex);

        ggl_rectangle_set_size(rect_tex_bis, (ggl_vector2f) {120, oscillate(elapsed, 10, 80, 1.5f)});
        ggl_rectangle_set_position(rect_tex_bis, (ggl_vector2f) {pos7_x - 60, oscillate(elapsed, MARGING_TOP, MARGING_TOP - 40, 1.5f)});
        if ((int) (elapsed * 1.5f) % 2 == 0) {
            ggl_rectangle_set_texture(rect_tex_bis, texture);
        } else {
            ggl_rectangle_set_texture(rect_tex_bis, texture_misc);
        }
        ggl_rectangle_render(ctx, rect_tex_bis);
        ggl_rectangle_render(ctx, rect_rot);
        ggl_rectangle_set_rotation(rect_rot, oscillate(elapsed, 0, 360, 1));

        ggl_vector2f c_pos = ggl_get_cursor_scaled_position(ctx);
        c_pos._x -= 10;
        c_pos._y -= 10;
        ggl_rectangle_set_position(cursor, c_pos);
        ggl_rectangle_render(ctx, cursor);
    }
    
    ggl_rectangle_free(cursor);
    ggl_rectangle_free(rect_tex_bis);
    ggl_rectangle_free(rect_tex);
    ggl_rectangle_free(rect);
    ggl_rectangle_free(rect_rot);
    ggl_triangle_free(tri_tex);
    ggl_triangle_free(tri);
    ggl_circle_free(circle);
    ggl_convex_free(convex);
    ggl_texture_free(texture);
    ggl_texture_free(texture_misc);
    return ggl_terminate(ctx);
}
