/*
** EPITECH PROJECT, 2025
** src/core/ggl_window_helper
** File description:
** GGL window helper
*/

#include "ggl.h"

/**
 * @brief Get the width of the window.
 *
 * @param ctx           The context
 *
 * @return The width of the window.
 */
ggl_int
ggl_get_window_width(ggl_context *ctx)
{
    return ctx->_ggl_window._ref_width;
}

/**
 * @brief Get the height of the window.
 *
 * @param ctx           The context
 *
 * @return The height of the window.
 */
ggl_int
ggl_get_window_height(ggl_context *ctx)
{
    return ctx->_ggl_window._ref_height;
}

/**
 * @brief Get the size of the window.
 *
 * @param ctx           The context
 *
 * @return The size of the window.
 */
ggl_vector2f
ggl_get_window_size(ggl_context *ctx)
{
    return (ggl_vector2f) {
        ggl_get_window_width(ctx),
        ggl_get_window_height(ctx)
    };
}
