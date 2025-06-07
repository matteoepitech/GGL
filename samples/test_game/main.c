/*
** EPITECH PROJECT, 2025
** main
** File description:
** Test file for GGL - color cycling example
*/

#include "../../include/ggl.h"

static void process_inputs()
{
    if (ggl_is_key_down(NULL, GLFW_KEY_V)) {
        printf("V is down!\n");
        fflush(stdout);
    }
}

int main()
{
    ggl_color bg_c = {50, 50, 50, 255};
    ggl_color t_color = {10, 10, 255, 255};
    ggl_color t2_color = {10, 255, 10, 155};
    
    ggl_init();
    ggl_create_window("Valentino's Window", (ggl_vector2i){1280, 720});
    ggl_setup_debug_close(NULL);

    ggl_triangle *t1 = ggl_triangle_create(
        (ggl_vector2f) {0.0f, 0.0f},
        (ggl_vector2f) {0.5f, 0.5f},
        t_color
    );
    ggl_triangle *t2 = ggl_triangle_create(
        (ggl_vector2f) {0.0f, 0.3f},
        (ggl_vector2f) {1.5f, 1.5f},
        t2_color
    );
    while (ggl_window_should_close(NULL) == GGL_FALSE) {
        process_inputs();
        ggl_clear_window(bg_c);
        ggl_triangle_render(t2);
        ggl_triangle_render(t1);
        if (ggl_is_key_down(NULL, GLFW_KEY_SPACE)) {
            bg_c._b += 1;
            if (bg_c._b > 255)
                bg_c._b = 0;
        }
    }
    ggl_terminate();
    return 0;
}
