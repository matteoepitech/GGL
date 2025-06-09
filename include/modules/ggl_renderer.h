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
ggl_triangle *ggl_triangle_create(ggl_vector2f position, ggl_vector2f size, ggl_color color);
ggl_status ggl_triangle_render(ggl_context *ctx, const ggl_triangle *triangle);
ggl_vector2f ggl_triangle_get_position(ggl_triangle *triangle);
ggl_color ggl_triangle_get_color(ggl_triangle *triangle);
ggl_vector2f ggl_triangle_get_size(ggl_triangle *triangle);
ggl_vector2f ggl_triangle_set_position(ggl_triangle *triangle, ggl_vector2f position);
ggl_color ggl_triangle_set_color(ggl_triangle *triangle, ggl_color color);
ggl_vector2f ggl_triangle_set_size(ggl_triangle *triangle, ggl_vector2f size);
;

/*
 * Location : src/renderer/geometry/ggl_rectangle.c
 */
ggl_rectangle *ggl_rectangle_create(ggl_vector2f position, ggl_vector2f size, ggl_color color);
ggl_status ggl_rectangle_render(ggl_context *ctx, const ggl_rectangle *rectangle);
ggl_vector2f ggl_rectangle_get_position(ggl_rectangle *rectangle);
ggl_color ggl_rectangle_get_color(ggl_rectangle *rectangle);
ggl_vector2f ggl_rectangle_get_size(ggl_rectangle *rectangle);
ggl_bounds ggl_rectangle_get_bounds(ggl_context *ctx, ggl_rectangle *rectangle);
ggl_vector2f ggl_rectangle_set_position(ggl_rectangle *rectangle, ggl_vector2f position);
ggl_color ggl_rectangle_set_color(ggl_rectangle *rectangle, ggl_color color);
ggl_vector2f ggl_rectangle_set_size(ggl_rectangle *rectangle, ggl_vector2f size);

/*
 * Location : src/renderer/geometry/ggl_convex.c
 */
ggl_convex *ggl_convex_create(ggl_vector2f position);
ggl_convex *ggl_convex_add_vertex(ggl_convex *convex, ggl_vector2f position, ggl_color color);
ggl_status ggl_convex_render(ggl_context *ctx, const ggl_convex *convex);
ggl_vector2f ggl_convex_get_position(ggl_convex *convex);
ggl_color ggl_convex_get_vertex_color(ggl_convex *convex, int vertex_index);
ggl_bounds ggl_convex_get_bounds(ggl_context *ctx, ggl_convex *convex);
ggl_vector2f ggl_convex_set_position(ggl_convex *convex, ggl_vector2f position);
ggl_status ggl_convex_set_vertex_color(ggl_convex *convex, int vertex_index, ggl_color color);

#endif /* ifndef _GGL_MODULE_RENDERER_H_ */
