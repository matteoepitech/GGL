/*
** EPITECH PROJECT, 2025
** main
** File description:
** Test file for GGL
*/

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/ggl.h"

int main()
{
    ggl_init();
    ggl_create_window("Valentino's Window", (ggl_size_t) {1280, 720});
    ggl_setup_debug_close(NULL);

    while (ggl_window_should_close(NULL) == GGL_FALSE) {
        //printf("Window is running!\n");
    }
    return 0;
}
