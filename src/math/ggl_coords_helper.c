/*
** GGL PROJECT, 2025
** src/math/ggl_coords_helper.c
** File description:
** GGL coords helper avec ratio adaptatif
*/

#include "ggl.h"

/**
 * @brief Converts reference coordinates to the current screen coordinates
 *        Maintains the same relative ratio as in the reference window.
 *
 * @param ctx           The program context
 * @param ref_coords    Coordinates based on 1280x720 resolution
 *
 * @return Coordinates adapted to the current screen size.
 */
ggl_vector2f
ggl_coords_adapt_to_current_size(ggl_context *ctx, ggl_vector2f ref_coords)
{
    ggl_vector2f adapted = {0};
    float current_width = (float) ctx->_ggl_window._fb_width;
    float current_height = (float) ctx->_ggl_window._fb_height;
    float width_ratio = current_width / ctx->_ggl_window._ref_width;
    float height_ratio = current_height / ctx->_ggl_window._ref_height;

    adapted._x = ref_coords._x * width_ratio;
    adapted._y = ref_coords._y * height_ratio;    
    return adapted;
}

/**
 * @brief Normalizes reference coordinates to screen coordinates in the
 *        range [-1;1] taking the current aspect ratio into account.
 *
 * @param ctx           The program context
 * @param ref_coords    Coordinates based on 1280x720 resolution
 *
 * @return The final normalized coordinates.
 */
ggl_vector2f
ggl_coords_normalize_to_ndc(ggl_context *ctx, ggl_vector2f ref_coords)
{
    ggl_vector2f normalized = {0};
    ggl_vector2f adapted = ggl_coords_adapt_to_current_size(ctx, ref_coords);
    float current_width = (float)ctx->_ggl_window._fb_width;
    float current_height = (float)ctx->_ggl_window._fb_height;

    normalized._x = (adapted._x / (current_width * 0.5f)) - 1.0f;
    normalized._y = 1.0f - (adapted._y / (current_height * 0.5f));    
    return normalized;
}
