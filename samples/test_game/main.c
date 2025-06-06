/*
** EPITECH PROJECT, 2025
** main
** File description:
** Test file for GGL - color cycling example
*/

#include <stdio.h>
#include <stdlib.h>
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
    ggl_color_t bg_c = {255, 0, 0, 255};
    int phase = 0;
    int speed = 2;

    ggl_init();
    ggl_create_window("Valentino's Window", (ggl_size_t){1280, 720});
    ggl_setup_debug_close(NULL);

    while (ggl_window_should_close(NULL) == GGL_FALSE) {
        process_inputs();
        switch (phase) {
            case 0: // Red to Green
                bg_c._r -= speed;
                bg_c._g += speed;
                if (bg_c._g >= 255) {
                    bg_c._g = 255;
                    bg_c._r = 0;
                    phase = 1;
                }
                break;
            case 1: // Green to Blue
                bg_c._g -= speed;
                bg_c._b += speed;
                if (bg_c._b >= 255) {
                    bg_c._b = 255;
                    bg_c._g = 0;
                    phase = 2;
                }
                break;
            case 2: // Blue to Red
                bg_c._b -= speed;
                bg_c._r += speed;
                if (bg_c._r >= 255) {
                    bg_c._r = 255;
                    bg_c._b = 0;
                    phase = 0;
                }
                break;
        }

        ggl_clear_window(bg_c);
    }

    return 0;
}
