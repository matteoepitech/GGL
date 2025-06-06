/*
** EPITECH PROJECT, 2025
** src/core/ggl_init
** File description:
** GGL debug close window key input. Default : ESC
*/

#include "ggl.h"

/**
 * @brief GGL Debug close callback.
 *
 * @param window         The window
 * @param key            The key
 * @param scancode       The scancode
 * @param action         The action
 * @param mods           The mods
 */
static void
ggl_debug_close_callback(GLFWwindow* window, int key, int scancode,
    int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        if (window == NULL) {
            GGL_PERROR("Cannot close the window.");
        }
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        GGL_DEBUG("Closing window...");
    }
}

/**
 * @brief Setup the debug close. If you don't call this function
 *        you will not gonna have this feature.
 *
 * @param ctx           The context
 *
 * @return GGL_OK if worked, GGL_KO if not.
 */
ggl_status
ggl_setup_debug_close(ggl_context *ctx)
{
    if (ctx == NULL)
        ctx = ggl_get_context();
    if (ctx == NULL || ctx->_ggl_window._win_glfw == NULL)
        return GGL_KO;
    glfwSetKeyCallback(ctx->_ggl_window._win_glfw, ggl_debug_close_callback);
    GGL_DEBUG("Debug close is activated.");
    return GGL_OK;
}
