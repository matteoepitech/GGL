/*
** GGL PROJECT, 2025
** src/math/ggl_distance_helper.c
** File description:
** GGL distance helper
*/

#include "ggl.h"

/**
 * @brief Get the vector length.
 *
 * @param vector                The vector
 *
 * @return The vector length.
 */
ggl_float
ggl_get_vector_length(ggl_vector2f vector)
{
    ggl_float length = 0;

    length += vector._x * vector._x;
    length += vector._y * vector._y;
    return sqrt(length);
}

/**
 * @brief Get the distance between 2 points.
 *
 * @param point1                The point 1
 * @param point2                The point 2
 *
 * @return The distance.
 */
ggl_float
ggl_distance_between_points(ggl_vector2f point1, ggl_vector2f point2)
{
    ggl_vector2f local_vector = point1;

    local_vector._x -= point2._x;
    local_vector._y -= point2._y;
    return ggl_get_vector_length(local_vector);
}
