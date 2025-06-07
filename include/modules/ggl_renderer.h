/*
** GGL PROJECT, 2025
** include/modules/ggl_renderer.h
** File description:
** GGL Renderer module header file
*/

#ifndef _GGL_MODULE_RENDERER_H_
    #define _GGL_MODULE_RENDERER_H_

    #include "../misc/ggl_types.h"

/*
 * Location : src/renderer/geometry/ggl_triangle.c
 */
ggl_triangle *ggl_triangle_create(ggl_vector2f position, ggl_vector2f size,
    ggl_color color);
ggl_status ggl_triangle_render(ggl_context *ctx, const ggl_triangle *triangle);

/*
 * Location : src/renderer/geometry/ggl_rectangle.c
 */
ggl_rectangle *ggl_rectangle_create(ggl_vector2f position, ggl_vector2f size,
    ggl_color color);
ggl_status ggl_rectangle_render(ggl_context *ctx, const ggl_rectangle *rectangle);

#endif /* ifndef _GGL_MODULE_RENDERER_H_ */
