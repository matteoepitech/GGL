/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_convex
** File description:
** GGL render convex geometry
*/

#include "ggl.h"
#include "ggl_internal.h"

// ==============================================================

/**
 * @brief Content of the geometry convex.
 *        Singleton of it using static variable.
 */
typedef struct {
    ggl_ressource_id _vao;
    ggl_ressource_id _ebo;
    ggl_ressource_id _shader_program;
    ggl_ressource_id _pos_location;
    ggl_ressource_id _size_location;
    ggl_ressource_id _color_location;
    ggl_bool _is_initialized;
} ggl_convex_renderer;
static ggl_convex_renderer g_convex_renderer = {0};

// ==============================================================

/**
 * @brief convex init.
 *        DO NOT CALL THIS FUNCTION only if you know what to do.
 *
 * @return GGL_OK if the init was fine.
 */
ggl_status
__ggl_convex_init(void)
{
    ggl_ressource_id vertex_shader = 0;
    ggl_ressource_id fragment_shader = 0;
    unsigned int indices[] = {0};

    if (g_convex_renderer._is_initialized == GGL_TRUE) {
        return GGL_OK;
    }
    glGenVertexArrays(1, &g_convex_renderer._vao);
    glBindVertexArray(g_convex_renderer._vao);
    //glGenBuffers(1, &g_convex_renderer._ebo);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_convex_renderer._ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    vertex_shader = compile_shader(GL_VERTEX_SHADER, GGL_TRIANGLE_VERTEX_SHADER);
    fragment_shader = compile_shader(GL_FRAGMENT_SHADER, GGL_TRIANGLE_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return GGL_KO;
    } 
    g_convex_renderer._shader_program = glCreateProgram();
    glAttachShader(g_convex_renderer._shader_program, vertex_shader);
    glAttachShader(g_convex_renderer._shader_program, fragment_shader);
    glLinkProgram(g_convex_renderer._shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    g_convex_renderer._is_initialized = GGL_TRUE;
    g_convex_renderer._pos_location = glGetUniformLocation(g_convex_renderer._shader_program, "u_position");
    g_convex_renderer._size_location = glGetUniformLocation(g_convex_renderer._shader_program, "u_size");
    g_convex_renderer._color_location = glGetUniformLocation(g_convex_renderer._shader_program, "u_color");
    glBindVertexArray(0);
    return GGL_OK;
}

/**
 * @brief Render a convex.
 *
 * @param convex              The convex to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_convex_render(ggl_context *ctx, const ggl_convex *convex)
{
    ggl_vector2f final_pos = {0};
    ggl_vector2f final_size = {0};

    if (convex == NULL || ctx == NULL) {
        return GGL_KO;
    }
    final_pos = ggl_coords_normalize_to_ndc_pos(ctx, convex->_position);
    final_size = ggl_coords_normalize_to_ndc_size(ctx, convex->_size);
    glBindVertexArray(g_convex_renderer._vao);
    glUseProgram(g_convex_renderer._shader_program);
    glUniform2f(g_convex_renderer._pos_location, final_pos._x, final_pos._y);
    glUniform2f(g_convex_renderer._size_location, final_size._x, final_size._y);
    glUniform4f(g_convex_renderer._color_location, 
        convex->_color._r / 255.0f,
        convex->_color._g / 255.0f,
        convex->_color._b / 255.0f,
        convex->_color._a / 255.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    return GGL_OK;
}

/**
 * @brief Create a convex.
 *
 * @param position              The pos of the convex using ggl_vector2f
 * @param size                  The size of the trignale using ggl_vector2f
 * @param color                 The color of the convex using ggl_color
 *
 * @return The convex geometry structure.
 */
ggl_convex *
ggl_convex_create(ggl_vector2f position, ggl_vector2f size, ggl_color color)
{
    ggl_convex *convex = malloc(sizeof(ggl_convex));
    float vertices[] = {
         1.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,
         0.0f,  0.0f, 0.0f // Anchor left up
    };

    if (convex == NULL) {
        return NULL;
    }
    if (g_convex_renderer._is_initialized == GGL_FALSE) {
        __ggl_convex_init();
    } 
    glBindVertexArray(g_convex_renderer._vao);
    glGenBuffers(1, &convex->__vbo__);
    glBindBuffer(GL_ARRAY_BUFFER, convex->__vbo__);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    convex->_position = position;
    convex->_color = color;
    convex->_size = size;
    return convex;
}

/**
 * @brief Convex get position.
 *
 * @param convex             The convex
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_convex_get_position(ggl_convex *convex)
{
    if (convex == NULL)
        return (ggl_vector2f) {0, 0};
    return convex->_position;
}

/**
 * @brief Convex get color.
 *
 * @param convex             The convex
 *
 * @return The color.
 */
ggl_color
ggl_convex_get_color(ggl_convex *convex)
{
    if (convex == NULL)
        return (ggl_color) {0, 0, 0, 0};
    return convex->_color;
}

/**
 * @brief Convex get size.
 *
 * @param convex             The convex
 *
 * @return The size.
 */
ggl_vector2f
ggl_convex_get_size(ggl_convex *convex)
{
    if (convex == NULL)
        return (ggl_vector2f) {0, 0};
    return convex->_size;
}

/**
 * @brief Convex get bounds.
 *
 * @param convex             The convex
 *
 * @return The bounds of the convex.
 */
ggl_bounds
ggl_convex_get_bounds(ggl_context *ctx, ggl_convex *convex)
{
    // @TODO
    return (ggl_bounds) {0, 0, 0, 0};
}

/**
 * @brief Convex set position.
 *
 * @param convex             The convex
 * @param position              The new position
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_convex_set_position(ggl_convex *convex, ggl_vector2f position)
{
    convex->_position = position;
    return position;
}

/**
 * @brief Convex get color.
 *
 * @param convex             The convex
 * @param color                 The new color
 *
 * @return The color.
 */
ggl_color
ggl_convex_set_color(ggl_convex *convex, ggl_color color)
{
    convex->_color = color;
    return color;
}

/**
 * @brief Convex set size.
 *
 * @param convex             The convex
 *
 * @return The size.
 */
ggl_vector2f
ggl_convex_set_size(ggl_convex *convex, ggl_vector2f size)
{
    convex->_size = size;
    return size;
}
