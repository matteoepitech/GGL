/*
** GGL PROJECT, 2025
** src/math/ggl_coords_helper.c
** File description:
** GGL coords helper
*/

#include "ggl.h"

/**
 * @brief Converts reference coordinates to current screen resolution.
 *
 * @param ctx           Program context
 * @param ref_coords    Reference coordinates
 *
 * @return Scaled screen-space coordinates.
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
 * @brief Converts position to NDC [-1;1],
 *        considering aspect ratio.
 *
 * @param ctx           Program context
 * @param ref_coords    Reference position
 *
 * @return Normalized position in NDC.
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
 * @brief Converts a size vector to normalized screen space [0;1],
 *        considering aspect ratio.
 *
 * @param ctx           Program context
 * @param ref_coords    Reference size
 *
 * @return Normalized size vector.
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
 * @brief Converts a reference value to NDC [-1;1]
 *        based on current screen size.
 *
 * @param ctx           Program context
 * @param ref_value     Reference coordinate
 * @param axis          0 = X, 1 = Y
 *
 * @return Normalized NDC value.
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
