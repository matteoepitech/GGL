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
 * @param ref_coords    Coordinates based on the reference resolution
 *
 * @return Coordinates adapted to the current screen size.
 */
ggl_vector2f
ggl_coords_adapt_to_current_size(ggl_context *ctx,
                                 ggl_vector2f ref_coords)
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
 * @param ref_coords    Coordinates based on the reference resolution
 *
 * @return The final normalized coordinates.
 */
ggl_vector2f
ggl_coords_normalize_to_ndc_pos(ggl_context *ctx,
                                ggl_vector2f ref_coords)
{
    ggl_vector2f normalized = {0};
    ggl_vector2f adapted = ggl_coords_adapt_to_current_size(ctx, ref_coords);
    float current_width = (float)ctx->_ggl_window._fb_width;
    float current_height = (float)ctx->_ggl_window._fb_height;

    normalized._x = (adapted._x / current_width * 2.0f) - 1.0f;
    normalized._y = 1.0f - (adapted._y / current_height * 2.0f);    
    return normalized;
}

/**
 * @brief Normalizes reference coordinates to screen coordinates in the
 *        range [O;1] taking the current aspect ratio into account.
 *
 * @param ctx           The program context
 * @param ref_coords    Coordinates based on the reference resolution
 *
 * @return The final normalized coordinates.
 */
ggl_vector2f
ggl_coords_normalize_to_ndc_size(ggl_context *ctx,
                                 ggl_vector2f ref_coords)
{
    ggl_vector2f normalized = {0};
    ggl_vector2f adapted = ggl_coords_adapt_to_current_size(ctx, ref_coords);
    float current_width = (float)ctx->_ggl_window._fb_width;
    float current_height = (float)ctx->_ggl_window._fb_height;

    normalized._x = adapted._x / (current_width / 2.0f);
    normalized._y = adapted._y / (current_height / 2.0f);
    return normalized;
}

/**
 * @brief Normalizes a reference coordinate value to NDC range [-1;1]
 *        taking the current screen dimensions into account.
 *
 * @param ctx           The program context
 * @param ref_value     Coordinate value based on the reference resolution
 * @param axis          Axis to normalize (0 for X, 1 for Y)
 *
 * @return The normalized coordinate value in NDC range.
 */
float
ggl_coord_normalize_to_ndc_pos(ggl_context *ctx,
                               float ref_value,
                               int axis)
{
    float normalized = 0.0f;
    float current_dimension = 0.0f;
    float ref_dimension = 0.0f;
    float adapted_value = 0.0f;
    
    if (ctx == NULL) {
        return 0.0f;
    } 
    if (axis == 0) {
        current_dimension = (float)ctx->_ggl_window._fb_width;
        ref_dimension = ctx->_ggl_window._ref_width;
    } else {
        current_dimension = (float)ctx->_ggl_window._fb_height;
        ref_dimension = ctx->_ggl_window._ref_height;
    }
    adapted_value = ref_value * (current_dimension / ref_dimension);
    if (axis == 0) {
        normalized = (adapted_value / current_dimension * 2.0f) - 1.0f;
    } else {
        normalized = 1.0f - (adapted_value / current_dimension * 2.0f);
    }
    return normalized;
}
