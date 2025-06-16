/*
** GGL PROJECT, 2025
** src/renderer/ggl_shape_data
** File description:
** GGL shape data helper
*/

#include "ggl.h"

/**
 * @brief Create a shape data.
 *
 * @param position              The position of the shape
 * @param color                 The color of the shape
 *
 * @return The shape data.
 */
ggl_shape_data
__ggl_create_shape_data(ggl_vector2f position,
                        ggl_color color)
{
    ggl_shape_data data = {0};

    data.__texture_id__ = 0;
    data._position = position;
    data._color = color;
    data._rotation = 0.0f;
    data._outline_width = 0.0f;
    data._outline_color = GGL_COLOR_BLACK;
    return data;
}
