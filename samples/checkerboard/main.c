/*
** GGL PROJECT, 2025
** main
** File description:
** Hot reloading game to try GGL
*/

#include "../../include/ggl.h"
#include "modules/ggl_core.h"
#include "modules/ggl_input.h"
#include "modules/ggl_renderer.h"
#include "modules/ggl_window.h"

#define RECT_AMOUNT 501
#define RECT_SIZE 50
#define RECT_ROW 31

static void init_rectangles(ggl_rectangle *rects[RECT_AMOUNT])
{
    ggl_vector2f pos = {0, 0};
    int swap = 0;

    for (int i = 0; i < RECT_AMOUNT; i++) {
        rects[i] = ggl_rectangle_create(pos, (ggl_vector2f) {RECT_SIZE, RECT_SIZE},
            swap == 0 ? (ggl_color) {90, 130, 126, 255} : (ggl_color) {132, 174, 146, 255});
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

    if (ctx == NULL)
        return 1;
    if (ggl_create_window(ctx, "CheckBoard", (ggl_vector2i) {1280, 720}) == GGL_KO)
        return 1;
    ggl_setup_debug_close(ctx);
    init_rectangles(rectangles);
    while (ggl_window_should_close(ctx) == GGL_FALSE) {
        ggl_clear_window((ggl_color) {0, 0, 0, 0});
        for (int i = 0; i < RECT_AMOUNT; i++) {
            ggl_rectangle_render(ctx, rectangles[i]);
        }
        printf("FPS : %d\n", (int) ctx->_current_fps);
    }
    ggl_terminate(ctx);
    return 0;
}
