/*
** EPITECH PROJECT, 2025
** src/core/ggl_init
** File description:
** GGL init file
*/

#include "ggl.h"

/**
 * @brief Init of GGL. This is the first function you should call.
 *
 * @return GGL_OK if everything worked, GGL_KO if not.
 */
ggl_status
ggl_init(void)
{
    if (glfwInit() == GLFW_FALSE) {
        GGL_PERROR("GLFW cannot be initialized.");
        return GGL_KO;
    }
    GGL_DEBUG("GLFW got initialized.");
    return GGL_OK;
}
