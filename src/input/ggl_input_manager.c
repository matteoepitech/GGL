/*
** EPITECH PROJECT, 2025
** src/core/ggl_input_manager.c
** File description:
** GGL input file
*/

#include "ggl.h"

/**
 * @brief Is a key is down or not.
 *
 * @param ctx           The context
 * @param key           The key (int)
 *
 * @return GGL_TRUE or GGL_FALSE.
 */
ggl_bool
ggl_is_key_down(ggl_context *ctx, ggl_key key)
{
    if (ctx == NULL)
        ctx = ggl_get_context();
    if (ctx == NULL || ctx->_ggl_window._win_glfw == NULL)
        return GGL_FALSE;
    return glfwGetKey(ctx->_ggl_window._win_glfw, key) == GLFW_PRESS;
}
