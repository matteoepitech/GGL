/*
** GGL PROJECT, 2025
** src/input/ggl_cursor
** File description:
** GGL cursor file
*/

#include "ggl.h"

/**
 * @brief Get cursor position using context. SCREEN position.
 *
 * @param ctx           The context
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_get_cursor_screen_position(ggl_context *ctx)
{
    double x_pos = 0.0;
    double y_pos = 0.0;

    glfwGetCursorPos(ctx->_ggl_window._win_glfw, &x_pos, &y_pos);
    return (ggl_vector2f) {x_pos, y_pos};
}

/**
 * @brief Get cursor position using context. SCALED position
 *        (adapted to framebuffer).
 *
 * @param ctx           The context
 *
 * @return The vector of position (scaled to reference resolution).
 */
ggl_vector2f
ggl_get_cursor_scaled_position(ggl_context *ctx)
{
    double x_pos = 0.0;
    double y_pos = 0.0;
    float scaled_x = 0.0f;
    float scaled_y = 0.0f;

    glfwGetCursorPos(ctx->_ggl_window._win_glfw, &x_pos, &y_pos);
    scaled_x = x_pos *
        ((float) ctx->_ggl_window._fb_ref_width / ctx->_ggl_window._fb_width);
    scaled_y = y_pos *
        ((float) ctx->_ggl_window._fb_ref_height / ctx->_ggl_window._fb_height);
    return (ggl_vector2f) {scaled_x, scaled_y};
}
