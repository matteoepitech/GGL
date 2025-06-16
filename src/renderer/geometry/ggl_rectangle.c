/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_rectangle
** File description:
** GGL render rectangle geometry
*/

#include "ggl.h"

// ==============================================================

/**
 * @brief Content of the geometry rectangle.
 *        Singleton of it using static variable.
 */
typedef struct {
    ggl_ressource_id _vao;
    ggl_ressource_id _vbo;
    ggl_ressource_id _ebo;
    ggl_ressource_id _shader_program;
    ggl_ressource_id _pos_location;
    ggl_ressource_id _rot_location;
    ggl_ressource_id _size_location;
    ggl_ressource_id _color_location;
    ggl_ressource_id _center_location;
    ggl_ressource_id _sampler_texture_location;
    ggl_bool _is_initialized;
} ggl_rectangle_renderer;
static ggl_rectangle_renderer g_rectangle_renderer = {0};

// ==============================================================

/**
 * @brief Rectangle init.
 *        DO NOT CALL THIS FUNCTION only if you know what to do.
 *
 * @return GGL_OK if the init was fine.
 */
static ggl_status
__ggl_rectangle_init(void)
{
    ggl_ressource_id vertex_shader = 0;
    ggl_ressource_id fragment_shader = 0;
    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,      // left up
        0.0f, -1.0f, 0.0f, 0.0f, 0.0f,     // left down
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f,      // right up
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f      // right down
    };
    unsigned int indices[] = { 0, 1, 2, 1, 3, 2 };

    if (g_rectangle_renderer._is_initialized == GGL_TRUE) {
        return GGL_OK;
    }
    glGenVertexArrays(1, &g_rectangle_renderer._vao);
    glBindVertexArray(g_rectangle_renderer._vao);
    glGenBuffers(1, &g_rectangle_renderer._vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectangle_renderer._vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    glGenBuffers(1, &g_rectangle_renderer._ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_rectangle_renderer._ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    vertex_shader = ggl_shader_create(GL_VERTEX_SHADER, GGL_TRIANGLE_VERTEX_SHADER);
    fragment_shader = ggl_shader_create(GL_FRAGMENT_SHADER, GGL_TRIANGLE_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return GGL_KO;
    } 
    g_rectangle_renderer._shader_program = glCreateProgram();
    glAttachShader(g_rectangle_renderer._shader_program, vertex_shader);
    glAttachShader(g_rectangle_renderer._shader_program, fragment_shader);
    glLinkProgram(g_rectangle_renderer._shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    g_rectangle_renderer._pos_location = ggl_get_shader_var_location(g_rectangle_renderer._shader_program, "u_position");
    g_rectangle_renderer._rot_location = ggl_get_shader_var_location(g_rectangle_renderer._shader_program, "u_rad");
    g_rectangle_renderer._size_location = ggl_get_shader_var_location(g_rectangle_renderer._shader_program, "u_size");
    g_rectangle_renderer._color_location = ggl_get_shader_var_location(g_rectangle_renderer._shader_program, "u_color");
    g_rectangle_renderer._center_location = ggl_get_shader_var_location(g_rectangle_renderer._shader_program, "u_center");
    g_rectangle_renderer._sampler_texture_location = ggl_get_shader_var_location(g_rectangle_renderer._shader_program, "u_sampler_texture");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    g_rectangle_renderer._is_initialized = GGL_TRUE;
    return GGL_OK;
}

/**
 * @brief Create a rectangle.
 *
 * @param position              The pos of the rectangle using ggl_vector2f
 * @param size                  The size of the rectangle using ggl_vector2f
 * @param color                 The color of the rectangle using ggl_color
 *
 * @return The rectangle geometry structure.
 */
ggl_rectangle *
ggl_rectangle_create(ggl_vector2f position,
                     ggl_vector2f size,
                     ggl_color color)
{
    ggl_rectangle *rectangle = malloc(sizeof(ggl_rectangle));

    if (rectangle == NULL) {
        return NULL;
    }
    if (g_rectangle_renderer._is_initialized == GGL_FALSE) {
        __ggl_rectangle_init();
    }
    rectangle->_info.__texture_id__ = 0;
    rectangle->_info._position = position;
    rectangle->_info._color = color;
    rectangle->_info._rotation = 0.0f;
    rectangle->_size = size;
    return rectangle;
}

/**
 * @brief Free a rectangle.
 *
 * @param rectangle                The rectangle
 *
 * @return GGL_TRUE if everything worked. GGL_FALSE otherwise.
 */
ggl_bool
ggl_rectangle_free(ggl_rectangle *rectangle)
{
    if (rectangle == NULL)
        return GGL_FALSE;
    free(rectangle);
    return GGL_TRUE;
}

/**
 * @brief Render a rectangle.
 *
 * @param ctx                    The context
 * @param rectangle              The rectangle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_rectangle_render(ggl_context *ctx,
                     const ggl_rectangle *rectangle)
{
    ggl_vector2f final_pos = {0};
    ggl_vector2f final_size = {0};

    if (rectangle == NULL || ctx == NULL) {
        return GGL_KO;
    }
    final_pos = ggl_coords_normalize_to_ndc_pos(ctx, rectangle->_info._position);
    final_size = ggl_coords_normalize_to_ndc_size(ctx, rectangle->_size);
    glBindVertexArray(g_rectangle_renderer._vao);
    glUseProgram(g_rectangle_renderer._shader_program);
    glUniform1i(g_rectangle_renderer._sampler_texture_location, 0);
    __ggl_texture_load_from_id(rectangle->_info.__texture_id__);
    glUniform2f(g_rectangle_renderer._pos_location, final_pos._x, final_pos._y);
    glUniform2f(g_rectangle_renderer._size_location, final_size._x, final_size._y);
    glUniform4f(g_rectangle_renderer._color_location, 
        rectangle->_info._color._r / 255.0f,
        rectangle->_info._color._g / 255.0f,
        rectangle->_info._color._b / 255.0f,
        rectangle->_info._color._a / 255.0f);
    glUniform1f(g_rectangle_renderer._rot_location,
        GGL_DEG_TO_RAD(rectangle->_info._rotation));
    glUniform2f(g_rectangle_renderer._center_location, 0.5, -0.5);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    __ggl_texture_unload();
    return GGL_OK;
}

/**
 * @brief Rectangle get position.
 *
 * @param rectangle             The rectangle
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_rectangle_get_position(ggl_rectangle *rectangle)
{
    if (rectangle == NULL)
        return (ggl_vector2f) {0, 0};
    return rectangle->_info._position;
}

/**
 * @brief Rectangle get rotation.
 *
 * @param rectangle             The rectangle
 *
 * @return The vector of rotation.
 */
ggl_float
ggl_rectangle_get_rotation(ggl_rectangle *rectangle)
{
    if (rectangle == NULL)
        return 0.0f;
    return rectangle->_info._rotation;
}

/**
 * @brief Rectangle get color.
 *
 * @param rectangle             The rectangle
 *
 * @return The color.
 */
ggl_color
ggl_rectangle_get_color(ggl_rectangle *rectangle)
{
    if (rectangle == NULL)
        return (ggl_color) {0, 0, 0, 0};
    return rectangle->_info._color;
}

/**
 * @brief Rectangle get size.
 *
 * @param rectangle             The rectangle
 *
 * @return The size.
 */
ggl_vector2f
ggl_rectangle_get_size(ggl_rectangle *rectangle)
{
    if (rectangle == NULL)
        return (ggl_vector2f) {0, 0};
    return rectangle->_size;
}

/**
 * @brief Is a point in the bounds of the rectangle?
 *
 * @param ctx           The context
 * @param rectangle     The rectangle
 * @param point         The point
 *
 * @return GGL_TRUE or FALSE.
 */
ggl_bool
ggl_rectangle_contain(ggl_context *ctx,
                      ggl_rectangle *rectangle,
                      ggl_vector2f point)
{
    ggl_vector2f start = rectangle->_info._position;
    ggl_vector2f size = rectangle->_size;

    start._x = start._x *
        ((float) ctx->_ggl_window._fb_width / ctx->_ggl_window._fb_ref_width);
    start._y = start._y *
        ((float) ctx->_ggl_window._fb_height / ctx->_ggl_window._fb_ref_height);
    size._x = size._x *
        ((float) ctx->_ggl_window._fb_width / ctx->_ggl_window._fb_ref_width);
    size._y = size._y *
        ((float) ctx->_ggl_window._fb_height / ctx->_ggl_window._fb_ref_height);
    if (rectangle == NULL)
        return GGL_FALSE;
    if (point._x >= start._x &&
        point._y >= start._y &&
        point._y <= start._y + size._y &&
        point._x <= start._x + size._x)
        return GGL_TRUE;
    return GGL_FALSE;
}

/**
 * @brief Rectangle set position.
 *
 * @param rectangle             The rectangle
 * @param position              The new position
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_rectangle_set_position(ggl_rectangle *rectangle,
                           ggl_vector2f position)
{
    rectangle->_info._position = position;
    return position;
}

/**
 * @brief Rectangle set rotation
 *
 * @param rectangle            The rectangle
 * @param position             The new rotation
 *
 * @return The vector of rotation.
 */
ggl_float
ggl_rectangle_set_rotation(ggl_rectangle *rectangle,
                           ggl_float rotation)
{
    rectangle->_info._rotation = rotation;
    return rotation;
}

/**
 * @brief Rectangle set color.
 *
 * @param rectangle             The rectangle
 * @param color                 The new color
 *
 * @return The color.
 */
ggl_color
ggl_rectangle_set_color(ggl_rectangle *rectangle,
                        ggl_color color)
{
    rectangle->_info._color = color;
    return color;
}

/**
 * @brief Rectangle set size.
 *
 * @param rectangle             The rectangle
 *
 * @return The size.
 */
ggl_vector2f
ggl_rectangle_set_size(ggl_rectangle *rectangle,
                       ggl_vector2f size)
{
    rectangle->_size = size;
    return size;
}

/**
 * @brief Set a texture for a rectangle.
 *
 * @param rectangle              The rectangle
 * @param texture               The texture to add
 *
 * @return GGL_OK.
 */
ggl_status
ggl_rectangle_set_texture(ggl_rectangle *rectangle,
                         ggl_texture *texture)
{
    if (rectangle->_info.__texture_id__ != 0) {
        glDeleteTextures(1, &rectangle->_info.__texture_id__);
    }
    glGenTextures(1, &rectangle->_info.__texture_id__);
    glBindTexture(GL_TEXTURE_2D, rectangle->_info.__texture_id__); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->_width,
        texture->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    return GGL_OK;
}
