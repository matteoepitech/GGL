/*
** GGL PROJECT, 2025
** src/core/ggl_cursor
** File description:
** GGL cursor file
*/

#include "ggl.h"

/**
 * @brief Get cursor position using context.
 *
 * @param ctx           The context
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_get_cursor_position(ggl_context *ctx)
{
    double x_pos = 0;
    double y_pos = 0;

    glfwGetCursorPos(ctx->_ggl_window._win_glfw, &x_pos, &y_pos);
    return (ggl_vector2f) {x_pos, y_pos};
}
