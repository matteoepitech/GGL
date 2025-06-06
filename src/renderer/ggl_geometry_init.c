/*
** EPITECH PROJECT, 2025
** src/renderer/ggl_geometry_init.c
** File description:
** GGL renderer init file
*/

#include "ggl.h"

/**
 * @brief Init all primitives geometries.
 *
 * @return GGL_OK if worked, GGL_KO if not.
 */
ggl_status
ggl_geometry_init(void)
{
    if (__ggl_triangle_init() == GGL_KO)
        return GGL_KO;
    return GGL_OK;
}
