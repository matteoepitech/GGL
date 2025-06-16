/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_triangle
** File description:
** GGL render triangle geometry
*/

#include "ggl.h"
#include "misc/ggl_types.h"

// ==============================================================

/**
 * @brief Content of the geometry triangle.
 *        Singleton of it using static variable.
 */
typedef struct {
    ggl_ressource_id _vao;
    ggl_ressource_id _vbo;
    ggl_ressource_id _shader_program;
    ggl_ressource_id _pos_location;
    ggl_ressource_id _rot_location;
    ggl_ressource_id _size_location;
    ggl_ressource_id _color_location;
    ggl_ressource_id _center_location;
    ggl_ressource_id _outline_width_location;
    ggl_ressource_id _outline_color_location;
    ggl_ressource_id _sampler_texture_location;
    ggl_bool _is_initialized;
} ggl_triangle_renderer;
static ggl_triangle_renderer g_triangle_renderer = {0};

// ==============================================================

/**
 * @brief Triangle init.
 *        DO NOT CALL THIS FUNCTION only if you know what to do.
 *
 * @return GGL_OK if the init was fine.
 */
static ggl_status
__ggl_triangle_init(void)
{
    ggl_ressource_id vertex_shader = 0;
    ggl_ressource_id fragment_shader = 0;
    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  1.0f, 0.0f, 0.5f, 1.0f
    };

    if (g_triangle_renderer._is_initialized == GGL_TRUE) {
        return GGL_OK;
    }
    glGenVertexArrays(1, &g_triangle_renderer._vao);
    glBindVertexArray(g_triangle_renderer._vao);
    glGenBuffers(1, &g_triangle_renderer._vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g_triangle_renderer._vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    vertex_shader = ggl_shader_create(GL_VERTEX_SHADER, GGL_TRIANGLE_VERTEX_SHADER);
    fragment_shader = ggl_shader_create(GL_FRAGMENT_SHADER, GGL_TRIANGLE_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return GGL_KO;
    } 
    g_triangle_renderer._shader_program = glCreateProgram();
    glAttachShader(g_triangle_renderer._shader_program, vertex_shader);
    glAttachShader(g_triangle_renderer._shader_program, fragment_shader);
    glLinkProgram(g_triangle_renderer._shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    g_triangle_renderer._pos_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_position");
    g_triangle_renderer._rot_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_rad");
    g_triangle_renderer._size_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_size");
    g_triangle_renderer._color_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_color");
    g_triangle_renderer._center_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_center");
    g_triangle_renderer._outline_width_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_out_width");
    g_triangle_renderer._outline_color_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_out_color");
    g_triangle_renderer._sampler_texture_location = ggl_get_shader_var_location(g_triangle_renderer._shader_program, "u_sampler_texture");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    g_triangle_renderer._is_initialized = GGL_TRUE;
    return GGL_OK;
}

/**
 * @brief Create a triangle.
 *
 * @param position              The pos of the triangle using ggl_vector2f
 * @param size                  The size of the triangle using ggl_vector2f
 * @param color                 The color of the triangle using ggl_color
 *
 * @return The triangle geometry structure.
 */
ggl_triangle *
ggl_triangle_create(ggl_vector2f position,
                    ggl_vector2f size,
                    ggl_color color)
{
    ggl_triangle *triangle = malloc(sizeof(ggl_triangle));

    if (triangle == NULL) {
        return NULL;
    }
    if (g_triangle_renderer._is_initialized == GGL_FALSE) {
        __ggl_triangle_init();
    }
    triangle->_info = __ggl_create_shape_data(position, color);
    triangle->_size = size;
    return triangle;
}

/**
 * @brief Free a triangle.
 *
 * @param triangle                The triangle
 *
 * @return GGL_TRUE if everything worked. GGL_FALSE otherwise.
 */
ggl_bool
ggl_triangle_free(ggl_triangle *triangle)
{
    if (triangle == NULL)
        return GGL_FALSE;
    free(triangle);
    return GGL_TRUE;
}

/**
 * @brief Render a triangle.
 *
 * @param ctx                    The context
 * @param triangle              The triangle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_triangle_render(ggl_context *ctx,
                    const ggl_triangle *triangle)
{
    ggl_vector2f final_pos = {0};
    ggl_vector2f final_size = {0};

    if (triangle == NULL || ctx == NULL) {
        return GGL_KO;
    }
    final_pos = ggl_coords_normalize_to_ndc_pos(ctx, triangle->_info._position);
    final_size = ggl_coords_normalize_to_ndc_size(ctx, triangle->_size);
    glBindVertexArray(g_triangle_renderer._vao);
    glUseProgram(g_triangle_renderer._shader_program);
    glUniform1i(g_triangle_renderer._sampler_texture_location, 0);
    __ggl_texture_load_from_id(triangle->_info.__texture_id__);
    glUniform2f(g_triangle_renderer._pos_location, final_pos._x, final_pos._y);
    glUniform2f(g_triangle_renderer._size_location, final_size._x, final_size._y);
    glUniform4f(g_triangle_renderer._color_location, 
        triangle->_info._color._r / 255.0f,
        triangle->_info._color._g / 255.0f,
        triangle->_info._color._b / 255.0f,
        triangle->_info._color._a / 255.0f);
    glUniform1f(g_triangle_renderer._rot_location,
        GGL_DEG_TO_RAD(triangle->_info._rotation));
    glUniform1f(g_triangle_renderer._outline_width_location, triangle->_info._outline_width);
    glUniform4f(g_triangle_renderer._color_location, 
        triangle->_info._color._r / 255.0f,
        triangle->_info._color._g / 255.0f,
        triangle->_info._color._b / 255.0f,
        triangle->_info._color._a / 255.0f);
    glUniform2f(g_triangle_renderer._center_location, 0.5, 0.5);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    __ggl_texture_unload();
    return GGL_OK;
}

/**
 * @brief Triangle get position.
 *
 * @param triangle              The triangle
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_triangle_get_position(ggl_triangle *triangle)
{
    return triangle->_info._position;
}

/**
 * @brief Triangle get rotation.
 *
 * @param triangle             The triangle
 *
 * @return The vector of rotation.
 */
ggl_float
ggl_triangle_get_rotation(ggl_triangle *triangle)
{
    if (triangle == NULL)
        return 0.0f;
    return triangle->_info._rotation;
}

/**
 * @brief Triangle get color.
 *
 * @param triangle              The triangle
 *
 * @return The color.
 */
ggl_color
ggl_triangle_get_color(ggl_triangle *triangle)
{
    return triangle->_info._color;
}

/**
 * @brief Triangle get size.
 *
 * @param triangle              The triangle
 *
 * @return The size.
 */
ggl_vector2f
ggl_triangle_get_size(ggl_triangle *triangle)
{
    return triangle->_size;
}

/**
 * @brief Triangle get outline_width.
 *
 * @param triangle              The triangle
 *
 * @return The outline_width.
 */
ggl_float
ggl_triangle_get_outline_width(ggl_triangle *triangle)
{
    return triangle->_info._outline_width;
}


/**
 * @brief Triangle set position.
 *
 * @param triangle             The triangle
 * @param position              The new position
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_triangle_set_position(ggl_triangle *triangle,
                          ggl_vector2f position)
{
    triangle->_info._position = position;
    return position;
}

/**
 * @brief Triangle set rotation
 *
 * @param triangle             The triangle
 * @param position             The new rotation
 *
 * @return The vector of rotation.
 */
ggl_float
ggl_triangle_set_rotation(ggl_triangle *triangle,
                          ggl_float rotation)
{
    triangle->_info._rotation = rotation;
    return rotation;
}

/**
 * @brief Triangle set color.
 *
 * @param triangle             The triangle
 * @param color                 The new color
 *
 * @return The color.
 */
ggl_color
ggl_triangle_set_color(ggl_triangle *triangle,
                       ggl_color color)
{
    triangle->_info._color = color;
    return color;
}

/**
 * @brief Triangle set size.
 *
 * @param triangle              The triangle
 *
 * @return The size.
 */
ggl_vector2f
ggl_triangle_set_size(ggl_triangle *triangle,
                      ggl_vector2f size)
{
    triangle->_size = size;
    return size;
}

/**
 * @brief Triangle set outline_width.
 *
 * @param triangle              The triangle
 *
 * @return The outline_width.
 */
ggl_float
ggl_triangle_set_outline_width(ggl_triangle *triangle,
                               ggl_float outline_width)
{
    triangle->_info._outline_width = outline_width;
    return outline_width;
}

/**
 * @brief Set a texture for a triangle.
 *
 * @param triangle              The triangle
 * @param texture               The texture to add
 *
 * @return GGL_OK.
 */
ggl_status
ggl_triangle_set_texture(ggl_triangle *triangle,
                         ggl_texture *texture)
{
    if (triangle->_info.__texture_id__ != 0) {
        glDeleteTextures(1, &triangle->_info.__texture_id__);
    }
    glGenTextures(1, &triangle->_info.__texture_id__);
    glBindTexture(GL_TEXTURE_2D, triangle->_info.__texture_id__); 
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

/**
 * @brief Get the transformed vertices from a triangle.
 *        Since the triangle has hardcoded coordinates we can create them.
 *
 * @param triangle              The triangle
 * @param a                     The point 1
 * @param b                     The point 2
 * @param c                     The point 3
 */
static void
__ggl_triangle_get_transformed_vertices(const ggl_triangle *triangle,
                                        ggl_vector2f *a,
                                        ggl_vector2f *b,
                                        ggl_vector2f *c)
{
    ggl_vector2f local_a = {0.0f, 0.0f};
    ggl_vector2f local_b = {1.0f, 0.0f};
    ggl_vector2f local_c = {0.5f, 1.0f};
    ggl_vector2f center = {0.5f, 0.5f};
    ggl_vector2f size = triangle->_size;
    ggl_vector2f pos = triangle->_info._position;
    ggl_float rad = GGL_DEG_TO_RAD(triangle->_info._rotation);
    ggl_vector2f verts[3] = {local_a, local_b, local_c};
    ggl_vector2f *out[3] = {a, b, c};

    for (int i = 0; i < 3; i++) {
        ggl_vector2f v = {verts[i]._x - center._x, verts[i]._y - center._y};
        ggl_float cos_r = cosf(rad);
        ggl_float sin_r = sinf(rad);
        ggl_vector2f rotated = {
            v._x * cos_r - v._y * sin_r + center._x,
            v._x * sin_r + v._y * cos_r + center._y};
        ggl_vector2f scaled = {
            rotated._x * size._x,
            rotated._y * size._y * -1.0f};
        ggl_vector2f final_pos = {
            scaled._x + pos._x,
            scaled._y + pos._y};
        *out[i] = final_pos;
    }
}

/**
 * @brief Is a point in the bounds of the triangle?
 *        This function use the Barycentric method with improved precision.
 *
 * @param ctx           The context
 * @param triangle      The triangle
 * @param point         The point
 *
 * @return GGL_TRUE or FALSE.
 */
ggl_bool
ggl_triangle_contain(ggl_context *ctx,
                     ggl_triangle *triangle,
                     ggl_vector2f point)
{
    ggl_vector2f a = {0};
    ggl_vector2f b = {0};
    ggl_vector2f c = {0};
    ggl_float denom = 0;
    ggl_float alpha = 0;
    ggl_float beta = 0;
    ggl_float gamma = 0;
    const ggl_float EPSILON = 1e-6f;

    if (triangle == NULL || ctx == NULL) {
        return GGL_FALSE;
    }
    __ggl_triangle_get_transformed_vertices(triangle, &a, &b, &c);
    denom = (b._y - c._y) * (a._x - c._x) + (c._x - b._x) * (a._y - c._y);
    if (fabsf(denom) < EPSILON) {
        return GGL_FALSE;
    }
    alpha = ((b._y - c._y) * (point._x - c._x) + (c._x - b._x) * (point._y - c._y)) / denom;
    beta  = ((c._y - a._y) * (point._x - c._x) + (a._x - c._x) * (point._y - c._y)) / denom;
    gamma = 1.0f - alpha - beta;
    return (alpha >= -EPSILON && beta >= -EPSILON && gamma >= -EPSILON);
}
