/*
** GGL PROJECT, 2025
** main
** File description:
** Hot reloading game to try GGL
*/

#include "../../include/ggl.h"
#include "misc/ggl_types.h"
#include "modules/ggl_core.h"
#include "modules/ggl_input.h"
#include "modules/ggl_math.h"
#include "modules/ggl_renderer.h"
#include "modules/ggl_window.h"
#include <math.h>

#define RECT_AMOUNT 501
#define RECT_SIZE 50
#define RECT_ROW 31
#define TRAIL_LENGTH 15

static void init_rectangles(ggl_rectangle *rects[RECT_AMOUNT], ggl_vector2f positions[RECT_AMOUNT], ggl_texture *t)
{
    ggl_vector2f pos = {0, 0};
    int swap = 0;

    for (int i = 0; i < RECT_AMOUNT; i++) {
        rects[i] = ggl_rectangle_create(pos, (ggl_vector2f) {RECT_SIZE, RECT_SIZE},
            swap == 0 ? (ggl_color) {90, 130, 126, 255} : (ggl_color) {132, 174, 146, 255});
        //ggl_rectangle_set_texture(rects[i], t);
        positions[i] = pos;
        swap ^= 1;
        pos._x += RECT_SIZE;
        if ((i + 1) % RECT_ROW == 0) {
            pos._y += RECT_SIZE;
            pos._x = 0;
        }
    }
}

int main(void)
{
    ggl_context *ctx = ggl_init();
    ggl_rectangle *rectangles[RECT_AMOUNT];
    ggl_vector2f original_positions[RECT_AMOUNT];
    ggl_vector2f cursor_pos = {0, 0};
    int trail[TRAIL_LENGTH];
    for (int i = 0; i < TRAIL_LENGTH; i++)
        trail[i] = -1;
    ggl_color colors[3] = {GGL_COLOR_RED, GGL_COLOR_GREEN, GGL_COLOR_BLUE};
    int trail_index = 0;

    ggl_texture *t = ggl_texture_create("./tree.jpeg");
    ggl_texture *t2 = ggl_texture_create("./tree.jpeg");

    if (ctx == NULL)
        return 1;
    if (ggl_create_window(ctx, "CheckBoard", (ggl_vector2i) {1280, 720}) == GGL_KO)
        return 1;

    ggl_setup_debug_close(ctx);
    init_rectangles(rectangles, original_positions, t2);

    ggl_convex *convex_shape = ggl_convex_create((ggl_vector2f) {1280.0f / 2.0f, 720.0f / 2.0f});

    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {0, 80}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {-60, 20}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {-80, -20}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {-60, -60}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {-20, -80}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {0, -60}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {20, -80}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {60, -60}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {80, -20}, GGL_COLOR_RED);
    ggl_convex_add_vertex(convex_shape, (ggl_vector2f) {60, 20}, GGL_COLOR_RED);

    ggl_circle *my_circle = ggl_circle_create((ggl_vector2f) {1280.0f / 2.0f - 500, 720.0f / 2.0f}, 250, 50, GGL_COLOR_GREEN);
    ggl_circle *my_circle_2 = ggl_circle_create((ggl_vector2f) {1280.0f / 2.0f - 0, 720.0f / 2.0f}, 250, 40, GGL_COLOR_WHITE);
    ggl_circle *my_circle_3 = ggl_circle_create((ggl_vector2f) {1280.0f / 2.0f + 500, 720.0f / 2.0f}, 250, 40, GGL_COLOR_RED);

    ggl_rectangle *button = ggl_rectangle_create((ggl_vector2f) {(GGL_WIN_WIDTH(ctx) / 2.0f) - 200, (GGL_WIN_HEIGHT(ctx) / 2.0f) - 100}, (ggl_vector2f) {400, 200}, GGL_COLOR_WHITE);
    ggl_rectangle_set_texture(button, t);

    ggl_triangle *triangle = ggl_triangle_create(
        (ggl_vector2f) {GGL_WIN_WIDTH(ctx) / 3.0f, GGL_WIN_HEIGHT(ctx) / 3.0f}, (ggl_vector2f) {100, 100}, GGL_COLOR_GREEN);
    ggl_triangle_set_texture(triangle, t);

    while (ggl_window_should_close(ctx) == GGL_FALSE) {
        cursor_pos = ggl_get_cursor_screen_position(ctx);
        ggl_clear_window((ggl_color) {0, 0, 0, 0});

        for (int i = 0; i < RECT_AMOUNT; i++) {
            ggl_rectangle_set_color(rectangles[i],
                (i % 2 == 0) ? (ggl_color){90, 130, 126, 255} : (ggl_color){132, 174, 146, 255});
        }
        for (int i = 0; i < RECT_AMOUNT; i++) {
            ggl_rectangle_set_position(rectangles[i], original_positions[i]);
        }

        for (int i = 0; i < RECT_AMOUNT; i++) {
            if (ggl_rectangle_contain(ctx, rectangles[i], cursor_pos) == GGL_TRUE) {
                int last_index = trail[(trail_index - 1 + TRAIL_LENGTH) % TRAIL_LENGTH];
                if (i != last_index) {
                    trail[trail_index] = i;
                    trail_index = (trail_index + 1) % TRAIL_LENGTH;
                }
                break;
            }
        }

        for (int i = 0; i < TRAIL_LENGTH; i++) {
            if (trail[i] >= 0 && trail[i] < RECT_AMOUNT)
                ggl_rectangle_set_color(rectangles[trail[i]], colors[i % 3]);
        }
     
        int last_index = trail[(trail_index - 1 + TRAIL_LENGTH) % TRAIL_LENGTH];
        if (last_index >= 0 && last_index < RECT_AMOUNT) {
            ggl_vector2f new_pos = original_positions[last_index];
            new_pos._y -= 10;
            ggl_rectangle_set_position(rectangles[last_index], new_pos);
        }

        for (int i = 0; i < RECT_AMOUNT; i++) {
            ggl_rectangle_render(ctx, rectangles[i]);
        }

        // ggl_convex_render(ctx, convex_shape);


        static float circle_r = 0.0f;

        float t = circle_r;

        float r1 = (((sinf(t) + 1.0f) / 2.0f) * 250.0f);
        float r2 = (((sinf(t - 0.5f) + 1.0f) / 2.0f) * 250.0f);
        float r3 = (((sinf(t - 1.0f) + 1.0f) / 2.0f) * 250.0f);

        // ggl_circle_set_radius(my_circle, r1);
        // ggl_circle_set_radius(my_circle_2, r2);
        // ggl_circle_set_radius(my_circle_3, r3);
        //
        // ggl_circle_render(ctx, my_circle);
        // ggl_circle_render(ctx, my_circle_2);
        // ggl_circle_render(ctx, my_circle_3);
        //
        // circle_r += 0.05f;

        ggl_rectangle_render(ctx, button);

        if (ggl_rectangle_contain(ctx, button, ggl_get_cursor_screen_position(ctx)) == GGL_TRUE) {
            ggl_rectangle_set_color(button, GGL_COLOR_RED);
        } else {
            ggl_rectangle_set_color(button, GGL_COLOR_WHITE);
        }
       
        ggl_triangle_render(ctx, triangle);

        printf("FPS : %d\n", (int) ctx->_current_fps);
        printf("Cursor: %.1f, %.1f | FB: %d x %d | Ref: %d x %d | FB Ref: %d %d\n",
            cursor_pos._x, cursor_pos._y,
            ctx->_ggl_window._fb_width, ctx->_ggl_window._fb_height,
            ctx->_ggl_window._ref_width, ctx->_ggl_window._ref_height,
            ctx->_ggl_window._fb_ref_width, ctx->_ggl_window._fb_ref_height);
    }

    ggl_terminate(ctx);
    return 0;
}
