/*
** GGL PROJECT, 2025
** src/math/ggl_collision
** File description:
** GGL collision helper
*/

#include "ggl.h"

/**
 * @brief Return if a point is in the bounds or not.
 *
 * @param bounds           The bounds to check
 * @param point            The point to check
 *
 * @return GGL_TRUE or GGL_FALSE.
 */
ggl_bool
ggl_bounds_contains(ggl_bounds bounds,
                    ggl_vector2f point)
{
    if (point._x >= bounds._start_x &&
        point._y >= bounds._start_y &&
        point._y <= bounds._end_y &&
        point._x <= bounds._end_x)
        return GGL_TRUE;
    return GGL_FALSE;
}
