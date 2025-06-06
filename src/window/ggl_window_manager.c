/*
** EPITECH PROJECT, 2025
** src/core/ggl_window_manager
** File description:
** GGL window manager
*/

#include "ggl.h"

/**
 * @brief Create a GGL window.
 *
 * @param title         The title of the window
 * @param size          The size of the window
 *
 * @return GGL_OK if everything worked. GGL_KO if not.
 */
ggl_status
ggl_create_window(const char *title, ggl_size_t size)
{
    GLFWwindow* window = NULL;
    ggl_context_t *ctx = ggl_get_context();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(size._width, size._height, title, NULL, NULL);
    if (window == NULL) {
        GGL_PERROR("Cannot create the window.");
        return GGL_KO;
    }
    ctx->_ggl_window._win_glfw = window;
    GGL_DEBUG("Window created with name '%s'.", title);
    glfwMakeContextCurrent(window);
    return GGL_OK;
}

/**
 * @brief Is the window need to be closed ?
 *        It does the swap buffers and poll events as well.
 *
 * @param ctx           The context of the program
 *
 * @return GGL_TRUE if yes GGL_FALSE if no.
 */
ggl_bool
ggl_window_should_close(ggl_context_t *ctx)
{
    if (ctx == NULL)
        ctx = ggl_get_context();
    if (ctx == NULL || ctx->_ggl_window._win_glfw == NULL)
        return GGL_TRUE;
    if (glfwWindowShouldClose(ctx->_ggl_window._win_glfw) == GLFW_TRUE)
        return GGL_TRUE;
    glfwSwapBuffers(ctx->_ggl_window._win_glfw);
    glfwPollEvents();
    return GGL_FALSE;
}
