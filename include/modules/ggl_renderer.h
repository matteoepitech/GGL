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
 * Location : src/renderer/ggl_renderer_init.c
 */
ggl_status ggl_geometry_init(void);

/*
 * Location : src/renderer/geometry/ggl_triangle.c
 */
ggl_status __ggl_triangle_init(void); // @INTERNAL
ggl_status ggl_triangle_render(const ggl_triangle *triangle);
ggl_triangle *ggl_triangle_create(ggl_vector2f position, ggl_vector2f size, ggl_color color);

#endif /* ifndef _GGL_MODULE_RENDERER_H_ */
