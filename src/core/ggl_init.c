/*
** GGL PROJECT, 2025
** src/core/ggl_init
** File description:
** GGL init file
*/

#include "ggl.h"

/**
 * @brief Init of GGL. This is the first function you should call.
 *
 * @return The context of the GGL program.
 */
ggl_context *
ggl_init(void)
{
    ggl_context *ctx = NULL;

    if (glfwInit() == GLFW_FALSE) {
        GGL_PERROR("GLFW cannot be initialized.");
        return NULL;
    }
    GGL_DEBUG("GLFW got initialized.");
    ctx = malloc(sizeof(ggl_context));
    if (ctx == NULL) {
        GGL_PERROR("GGL Context cannot be created.");
        return NULL;
    }
    GGL_DEBUG("GGL got initialized.");
    return ctx;
}

/**
 * @brief Terminate the GGL library. This is the last function you
 *        should call
 *
 * @return GGL_OK if everything worked, GGL_KO, if not.
 */
ggl_status
ggl_terminate(ggl_context *ctx)
{
    if (ctx == NULL)
        return GGL_KO;
    glfwDestroyWindow(ctx->_ggl_window._win_glfw);
    glfwTerminate();
    if (ctx != NULL)
        free(ctx);
    return GGL_OK;
}
