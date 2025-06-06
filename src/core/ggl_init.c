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
    __ggl_context__ = malloc(sizeof(ggl_context_t));
    if (__ggl_context__ == NULL) {
        GGL_PERROR("GGL Context cannot be created.");
        return GGL_KO;
    }
    GGL_DEBUG("GGL got initialized.");
    return GGL_OK;
}

/**
 * @brief Terminate the GGL library. This is the last function you
 *        should call
 *
 * @return GGL_OK if everything worked, GGL_KO, if not.
 */
ggl_status
ggl_terminate(void)
{
    glfwTerminate();
    return GGL_OK;
}
