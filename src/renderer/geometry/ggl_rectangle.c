/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_rectangle
** File description:
** GGL render rectangle geometry
*/

#include "ggl.h"
#include "ggl_internal.h"

// ==============================================================

/**
 * @brief Content of the geometry rectangle.
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
} ggl_rectangle_renderer;
static ggl_rectangle_renderer g_rectangle_renderer = {0};

// ==============================================================

/**
 * @brief Rectangle init.
 *        DO NOT CALL THIS FUNCTION only if you know what to do.
 *
 * @return GGL_OK if the init was fine.
 */
ggl_status
__ggl_rectangle_init(void)
{
    ggl_ressource_id vertex_shader = 0;
    ggl_ressource_id fragment_shader = 0;
    unsigned int indices[] = { 0, 1, 3, 1, 2, 3};

    if (g_rectangle_renderer._is_initialized == GGL_TRUE) {
        return GGL_OK;
    }
    glGenVertexArrays(1, &g_rectangle_renderer._vao);
    glBindVertexArray(g_rectangle_renderer._vao);
    glGenBuffers(1, &g_rectangle_renderer._ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_rectangle_renderer._ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    vertex_shader = compile_shader(GL_VERTEX_SHADER, GGL_TRIANGLE_VERTEX_SHADER);
    fragment_shader = compile_shader(GL_FRAGMENT_SHADER, GGL_TRIANGLE_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return GGL_KO;
    } 
    g_rectangle_renderer._shader_program = glCreateProgram();
    glAttachShader(g_rectangle_renderer._shader_program, vertex_shader);
    glAttachShader(g_rectangle_renderer._shader_program, fragment_shader);
    glLinkProgram(g_rectangle_renderer._shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    g_rectangle_renderer._is_initialized = GGL_TRUE;
    g_rectangle_renderer._pos_location = glGetUniformLocation(g_rectangle_renderer._shader_program, "u_position");
    g_rectangle_renderer._size_location = glGetUniformLocation(g_rectangle_renderer._shader_program, "u_size");
    g_rectangle_renderer._color_location = glGetUniformLocation(g_rectangle_renderer._shader_program, "u_color");
    glBindVertexArray(0);
    return GGL_OK;
}

/**
 * @brief Render a rectangle.
 *
 * @param rectangle              The rectangle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_rectangle_render(ggl_context *ctx, const ggl_rectangle *rectangle)
{
    ggl_vector2f final_pos = {0};
    ggl_vector2f final_size = {0};

    if (rectangle == NULL || ctx == NULL) {
        return GGL_KO;
    }
    final_pos = ggl_coords_normalize_to_ndc_pos(ctx, rectangle->_position);
    final_size = ggl_coords_normalize_to_ndc_size(ctx, rectangle->_size);
    glBindVertexArray(g_rectangle_renderer._vao);
    glUseProgram(g_rectangle_renderer._shader_program);
    glUniform2f(g_rectangle_renderer._pos_location, final_pos._x, final_pos._y);
    glUniform2f(g_rectangle_renderer._size_location, final_size._x, final_size._y);
    glUniform4f(g_rectangle_renderer._color_location, 
        rectangle->_color._r / 255.0f,
        rectangle->_color._g / 255.0f,
        rectangle->_color._b / 255.0f,
        rectangle->_color._a / 255.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    return GGL_OK;
}

/**
 * @brief Create a rectangle.
 *
 * @param position              The pos of the rectangle using ggl_vector2f
 * @param size                  The size of the trignale using ggl_vector2f
 * @param color                 The color of the rectangle using ggl_color
 *
 * @return The rectangle geometry structure.
 */
ggl_rectangle *
ggl_rectangle_create(ggl_vector2f position, ggl_vector2f size, ggl_color color)
{
    ggl_rectangle *rectangle = malloc(sizeof(ggl_rectangle));
    float vertices[] = {
         1.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,
         0.0f,  0.0f, 0.0f // Anchor left up
    };

    if (rectangle == NULL) {
        return NULL;
    }
    if (g_rectangle_renderer._is_initialized == GGL_FALSE) {
        __ggl_rectangle_init();
    } 
    glBindVertexArray(g_rectangle_renderer._vao);
    glGenBuffers(1, &rectangle->__vbo__);
    glBindBuffer(GL_ARRAY_BUFFER, rectangle->__vbo__);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    rectangle->_position = position;
    rectangle->_color = color;
    rectangle->_size = size;
    return rectangle;
}
