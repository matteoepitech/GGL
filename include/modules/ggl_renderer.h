/*
** GGL PROJECT, 2025
** include/modules/ggl_renderer.h
** File description:
** GGL Renderer module header file
*/

#ifndef _GGL_MODULE_RENDERER_H_
    #define _GGL_MODULE_RENDERER_H_

    #include "../misc/ggl_types.h"

/**
 * @brief Create a triangle.
 *
 * @param position              The pos of the triangle using ggl_vector2f
 * @param size                  The size of the trignale using ggl_vector2f
 * @param color                 The color of the triangle using ggl_color
 *
 * @return The triangle geometry structure.
 */
ggl_triangle *ggl_triangle_create(ggl_vector2f position,
                                  ggl_vector2f size,
                                  ggl_color color);

/**
 * @brief Free a triangle.
 *
 * @param triangle                The triangle
 *
 * @return GGL_TRUE if everything worked. GGL_FALSE otherwise.
 */
ggl_bool ggl_triangle_free(ggl_triangle *triangle);

/**
 * @brief Render a triangle.
 *
 * @param ctx                    The context
 * @param triangle              The triangle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status ggl_triangle_render(ggl_context *ctx,
                               const ggl_triangle *triangle);

/**
 * @brief Triangle get position.
 *
 * @param triangle              The triangle
 *
 * @return The vector of position.
 */
ggl_vector2f ggl_triangle_get_position(ggl_triangle *triangle);

/**
 * @brief triangle get rotation.
 *
 * @param triangle             The triangle
 *
 * @return The vector of rotation.
 */
ggl_float ggl_triangle_get_rotation(ggl_triangle *triangle);

/**
 * @brief Triangle get color.
 *
 * @param triangle              The triangle
 *
 * @return The color.
 */
ggl_color ggl_triangle_get_color(ggl_triangle *triangle);

/**
 * @brief Triangle get size.
 *
 * @param triangle              The triangle
 *
 * @return The size.
 */
ggl_vector2f ggl_triangle_get_size(ggl_triangle *triangle);

/**
 * @brief Triangle set position.
 *
 * @param triangle             The triangle
 * @param position              The new position
 *
 * @return The vector of position.
 */
ggl_vector2f ggl_triangle_set_position(ggl_triangle *triangle,
                                       ggl_vector2f position);

/**
 * @brief Triangle set rotation
 *
 * @param triangle             The triangle
 * @param position             The new rotation
 *
 * @return The vector of rotation.
 */
ggl_float ggl_triangle_set_rotation(ggl_triangle *triangle,
                                    ggl_float rotation);

/**
 * @brief Triangle set color.
 *
 * @param triangle             The triangle
 * @param color                 The new color
 *
 * @return The color.
 */
ggl_color ggl_triangle_set_color(ggl_triangle *triangle,
                                 ggl_color color);

/**
 * @brief Triangle set size.
 *
 * @param triangle              The triangle
 *
 * @return The size.
 */
ggl_vector2f ggl_triangle_set_size(ggl_triangle *triangle,
                                   ggl_vector2f size);

/**
 * @brief Set a texture for a triangle.
 *
 * @param triangle              The triangle
 * @param texture               The texture to add
 *
 * @return GGL_OK.
 */
ggl_status ggl_triangle_set_texture(ggl_triangle *triangle,
                                    ggl_texture *texture);


// ==============================================================

/**
 * @brief Create a rectangle.
 *
 * @param position              The pos of the rectangle using ggl_vector2f
 * @param size                  The size of the trignale using ggl_vector2f
 * @param color                 The color of the rectangle using ggl_color
 *
 * @return The rectangle geometry structure.
 */
ggl_rectangle *ggl_rectangle_create(ggl_vector2f position,
                                    ggl_vector2f size,
                                    ggl_color color);

/**
 * @brief Free a rectangle.
 *
 * @param rectangle                The rectangle
 *
 * @return GGL_TRUE if everything worked. GGL_FALSE otherwise.
 */
ggl_bool ggl_rectangle_free(ggl_rectangle *rectangle);

/**
 * @brief Render a rectangle.
 *
 * @param ctx                    The context
 * @param rectangle              The rectangle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status ggl_rectangle_render(ggl_context *ctx,
                                const ggl_rectangle *rectangle);

/**
 * @brief Rectangle get position.
 *
 * @param rectangle             The rectangle
 *
 * @return The vector of position.
 */
ggl_vector2f ggl_rectangle_get_position(ggl_rectangle *rectangle);

/**
 * @brief Rectangle get rotation.
 *
 * @param rectangle             The rectangle
 *
 * @return The vector of rotation.
 */
ggl_float ggl_rectangle_get_rotation(ggl_rectangle *rectangle);

/**
 * @brief Rectangle get color.
 *
 * @param rectangle             The rectangle
 *
 * @return The color.
 */
ggl_color ggl_rectangle_get_color(ggl_rectangle *rectangle);

/**
 * @brief Rectangle get size.
 *
 * @param rectangle             The rectangle
 *
 * @return The size.
 */
ggl_vector2f ggl_rectangle_get_size(ggl_rectangle *rectangle);

/**
 * @brief Is a point in the bounds of the rectangle?
 *
 * @param ctx           The context
 * @param rectangle     The rectangle
 * @param point         The point
 *
 * @return GGL_TRUE or FALSE.
 */
ggl_bool ggl_rectangle_contain(ggl_context *ctx,
                               ggl_rectangle *rectangle,
                               ggl_vector2f point);
/**
 * @brief Rectangle set position.
 *
 * @param rectangle             The rectangle
 * @param position              The new position
 *
 * @return The vector of position.
 */
ggl_vector2f ggl_rectangle_set_position(ggl_rectangle *rectangle,
                                        ggl_vector2f position);

/**
 * @brief Rectangle set rotation
 *
 * @param rectangle            The rectangle
 * @param position             The new rotation
 *
 * @return The vector of rotation.
 */
ggl_float ggl_rectangle_set_rotation(ggl_rectangle *rectangle,
                                     ggl_float rotation);

/**
 * @brief Rectangle set color.
 *
 * @param rectangle             The rectangle
 * @param color                 The new color
 *
 * @return The color.
 */
ggl_color ggl_rectangle_set_color(ggl_rectangle *rectangle,
                                  ggl_color color);

/**
 * @brief Rectangle set size.
 *
 * @param rectangle             The rectangle
 *
 * @return The size.
 */
ggl_vector2f ggl_rectangle_set_size(ggl_rectangle *rectangle,
                                    ggl_vector2f size);

/**
 * @brief Set a texture for a rectangle.
 *
 * @param rectangle              The rectangle
 * @param texture               The texture to add
 *
 * @return GGL_OK.
 */
ggl_status ggl_rectangle_set_texture(ggl_rectangle *rectangle,
                                     ggl_texture *texture);

// ==============================================================

/**
 * @brief Create a convex.
 *
 * @param position              The pos of the convex using ggl_vector2f
 *
 * @return The convex geometry structure.
 */
ggl_convex *ggl_convex_create(ggl_vector2f position);

/**
 * @brief Free a convex.
 *
 * @param convex                The convex
 *
 * @return GGL_TRUE if everything worked. GGL_FALSE otherwise.
 */
ggl_bool ggl_convex_free(ggl_convex *convex);

/**
 * @brief Render a convex.
 *
 * @param ctx                    The context
 * @param convex              The convex to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status ggl_convex_render(ggl_context *ctx,
                             const ggl_convex *convex);

/**
 * @brief Add a vertex in the convex shape.
 *        @INFO the vertex data has the following pattern :
 *        x,y,z,r,g,b,a so 7 bytes is 1 stride.
 *
 * @param convex                The original shape
 * @param position              The position of the point to add
 * @param color                 The color of the vertex to add
 *
 * @return The new convex shape.
 */
ggl_convex *ggl_convex_add_vertex(ggl_convex *convex,
                                  ggl_vector2f position,
                                  ggl_color color);

/**
 * @brief Set color for a specific vertex.
 *
 * @param convex                The convex shape
 * @param vertex_index          The index of the vertex
 * @param color                 The color to set
 *
 * @return GGL_OK if successful, GGL_KO otherwise.
 */
ggl_status ggl_convex_set_vertex_color(ggl_convex *convex,
                                       int vertex_index,
                                       ggl_color color);
/**
 * @brief Get color of a specific vertex.
 *
 * @param convex                The convex shape
 * @param vertex_index          The index of the vertex
 *
 * @return The color of the vertex.
 */
ggl_color ggl_convex_get_vertex_color(ggl_convex *convex,
                                      int vertex_index);

/**
 * @brief Get the position of the convex shape.
 *
 * @param convex        The shape
 *
 * @return The position.
 */
ggl_vector2f ggl_convex_get_position(ggl_convex *convex);

/**
 * @brief convex get rotation.
 *
 * @param convex             The convex
 *
 * @return The vector of rotation.
 */
ggl_float ggl_convex_get_rotation(ggl_convex *convex);

/**
 * @brief Set the position of the convex shape.
 *
 * @param convex                The shape
 * @param position              The position
 *
 * @return The new position.
 */
ggl_vector2f ggl_convex_set_position(ggl_convex *convex,
                                     ggl_vector2f position);

/**
 * @brief Convex set rotation
 *
 * @param convex               The convex
 * @param position             The new rotation
 *
 * @return The vector of rotation.
 */
ggl_float ggl_convex_set_rotation(ggl_convex *convex,
                                  ggl_float rotation);

// ==============================================================

/**
 * @brief Create a circle.
 *
 * @param position              The pos of the circle using ggl_vector2f
 * @param radius                The radius of the circle using ggl_int
 * @param step                  The number of step of the circle using ggl_int
 * @param color                 The color of the circle using ggl_color
 *
 * @return The circle geometry structure.
 */
ggl_circle *ggl_circle_create(ggl_vector2f position,
                              ggl_int radius,
                              ggl_int step,
                              ggl_color color);

/**
 * @brief Free a circle.
 *
 * @param circle                The circle
 *
 * @return GGL_TRUE if everything worked. GGL_FALSE otherwise.
 */
ggl_bool ggl_circle_free(ggl_circle *circle);

/**
 * @brief Render a circle.
 *
 * @param ctx                    The context
 * @param circle              The circle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status ggl_circle_render(ggl_context *ctx,
                             const ggl_circle *circle);

/**
 * @brief circle get position.
 *
 * @param circle              The circle
 *
 * @return The vector of position.
 */
ggl_vector2f ggl_circle_get_position(ggl_circle *circle);

/**
 * @brief circle get color.
 *
 * @param circle              The circle
 *
 * @return The color.
 */
ggl_color ggl_circle_get_color(ggl_circle *circle);

/**
 * @brief circle get radius.
 *
 * @param circle              The circle
 *
 * @return The radius.
 */
ggl_int ggl_circle_get_radius(ggl_circle *circle);

/**
 * @brief circle set position.
 *
 * @param circle             The circle
 * @param position              The new position
 *
 * @return The vector of position.
 */
ggl_vector2f ggl_circle_set_position(ggl_circle *circle,
                                     ggl_vector2f position);

/**
 * @brief circle set color.
 *
 * @param circle             The circle
 * @param color                 The new color
 *
 * @return The color.
 */
ggl_color ggl_circle_set_color(ggl_circle *circle,
                               ggl_color color);

/**
 * @brief circle set radius.
 *
 * @param circle              The circle
 *
 * @return The radius.
 */
ggl_int ggl_circle_set_radius(ggl_circle *circle,
                              ggl_int radius);

/**
 * @brief Set a texture for a circle.
 *
 * @param circle              The circle
 * @param texture               The texture to add
 *
 * @return GGL_OK.
 */
ggl_status ggl_circle_set_texture(ggl_circle *circle,
                                  ggl_texture *texture);

// ==============================================================

#endif /* ifndef _GGL_MODULE_RENDERER_H_ */
