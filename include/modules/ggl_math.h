/*
** GGL PROJECT, 2025
** include/modules/ggl_math.h
** File description:
** GGL Math module header file
*/

#ifndef _GGL_MODULE_MATH_H_
    #define _GGL_MODULE_MATH_H_

    #include "../misc/ggl_types.h"

/**
 * @brief Converts reference coordinates to current screen resolution.
 *
 * @param ctx           Program context
 * @param ref_coords    Reference coordinates
 *
 * @return Scaled screen-space coordinates.
 */
ggl_vector2f ggl_coords_adapt_to_current_size(ggl_context *ctx,
                                              ggl_vector2f ref_coords);

/**
 * @brief Converts position to NDC [-1;1],
 *        considering aspect ratio.
 *
 * @param ctx           Program context
 * @param ref_coords    Reference position
 *
 * @return Normalized position in NDC.
 */
ggl_vector2f ggl_coords_normalize_to_ndc_pos(ggl_context *ctx,
                                             ggl_vector2f ref_coords);

/**
 * @brief Converts a size vector to normalized screen space [0;1],
 *        considering aspect ratio.
 *
 * @param ctx           Program context
 * @param ref_coords    Reference size
 *
 * @return Normalized size vector.
 */
ggl_vector2f ggl_coords_normalize_to_ndc_size(ggl_context *ctx,
                                              ggl_vector2f ref_coords);


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
float ggl_coord_normalize_to_ndc_pos(ggl_context *ctx,
                                     float ref_value,
                                     int axis);

/**
 * @brief Get the vector length.
 *
 * @param vector                The vector
 *
 * @return The vector length.
 */
ggl_float ggl_get_vector_length(ggl_vector2f vector);

/**
 * @brief Get the distance between 2 points.
 *
 * @param point1                The point 1
 * @param point2                The point 2
 *
 * @return The distance.
 */
ggl_float ggl_distance_between_points(ggl_vector2f point1,
                                      ggl_vector2f point2);

#endif /* ifndef _GGL_MODULE_MATH_H_ */
