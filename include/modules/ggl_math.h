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
 * @brief Normalizes a reference coordinate value to NDC range [-1;1]
 *        taking the current screen dimensions into account.
 *
 * @param ctx           The program context
 * @param ref_value     Coordinate value based on 1280x720 resolution
 * @param axis          Axis to normalize (0 for X, 1 for Y)
 *
 * @return The normalized coordinate value in NDC range.
 */
float ggl_coord_normalize_to_ndc_pos(ggl_context *ctx,
                                     float ref_value,
                                     int axis);

/**
 * @brief Normalizes reference coordinates to screen coordinates in the
 *        range [O;1] taking the current aspect ratio into account.
 *
 * @param ctx           The program context
 * @param ref_coords    Coordinates based on 1280x720 resolution
 *
 * @return The final normalized coordinates.
 */
ggl_vector2f ggl_coords_normalize_to_ndc_size(ggl_context *ctx,
                                              ggl_vector2f ref_coords);

/**
 * @brief Normalizes reference coordinates to screen coordinates in the
 *        range [-1;1] taking the current aspect ratio into account.
 *
 * @param ctx           The program context
 * @param ref_coords    Coordinates based on 1280x720 resolution
 *
 * @return The final normalized coordinates.
 */
ggl_vector2f ggl_coords_normalize_to_ndc_pos(ggl_context *ctx,
                                             ggl_vector2f ref_coords);

/**
 * @brief Converts reference coordinates to the current screen coordinates
 *        Maintains the same relative ratio as in the reference window.
 *
 * @param ctx           The program context
 * @param ref_coords    Coordinates based on 1280x720 resolution
 *
 * @return Coordinates adapted to the current screen size.
 */
ggl_vector2f ggl_coords_adapt_to_current_size(ggl_context *ctx,
                                              ggl_vector2f ref_coords);

/**
 * @brief Return if a point is in the bounds or not.
 *
 * @param bounds           The bounds to check
 * @param point            The point to check
 *
 * @return GGL_TRUE or GGL_FALSE.
 */
ggl_bool ggl_bounds_contains(ggl_bounds bounds,
                             ggl_vector2f point);

#endif /* ifndef _GGL_MODULE_MATH_H_ */
