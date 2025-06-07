/*
** EPITECH PROJECT, 2025
** src/renderer/geometry/ggl_triangle
** File description:
** GGL render triangle geometry
*/

#include "ggl.h"
#include "ggl_internal.h"

// ==============================================================

/**
 * @brief Content of the geometry triangle.
 *        Singleton of it using static variable.
 */
typedef struct {
    ggl_ressource_id _vao;
    ggl_ressource_id _shader_program;
    ggl_bool _is_initialized;
} ggl_triangle_renderer;
static ggl_triangle_renderer g_triangle_renderer = {0};

const char *GGL_TRIANGLE_VERTEX_SHADER =
    "#version 330 core\n"
    "layout (location = 0) in vec3 l_pos;\n"
    "uniform vec2 u_position;\n"
    "uniform vec2 u_size;\n"
    "void main() {\n"
    "    vec3 scaled_pos = l_pos * vec3(u_size, 1.0);\n"
    "    gl_Position = vec4(scaled_pos.xy + u_position, 0.0, 1.0);\n"
    "}\0";

const char *GGL_TRIANGLE_FRAGMENT_SHADER =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "uniform vec4 u_color;\n"
    "void main() {\n"
    "    frag_color = u_color;\n"
    "}\0";

// ==============================================================

/**
 * @brief Triangle init. DO NOT CALL THIS FUNCTION only if you know what to do.
 *
 * @return GGL_OK if the init was fine.
 */
ggl_status
__ggl_triangle_init(void)
{
    ggl_ressource_id vertex_shader = 0;
    ggl_ressource_id fragment_shader = 0;

    if (g_triangle_renderer._is_initialized == GGL_TRUE) {
        return GGL_OK;
    }
    glGenVertexArrays(1, &g_triangle_renderer._vao);
    vertex_shader = compile_shader(GL_VERTEX_SHADER, GGL_TRIANGLE_VERTEX_SHADER);
    fragment_shader = compile_shader(GL_FRAGMENT_SHADER, GGL_TRIANGLE_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return GGL_KO;
    } 
    g_triangle_renderer._shader_program = glCreateProgram();
    glAttachShader(g_triangle_renderer._shader_program, vertex_shader);
    glAttachShader(g_triangle_renderer._shader_program, fragment_shader);
    glLinkProgram(g_triangle_renderer._shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    g_triangle_renderer._is_initialized = GGL_TRUE;
    return GGL_OK;
}

/**
 * @brief Render a triangle.
 *
 * @param triangle              The triangle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_triangle_render(const ggl_triangle *triangle)
{
    ggl_ressource_id pos_location = 0;
    ggl_ressource_id size_location = 0;
    ggl_ressource_id color_location = 0;

    if (triangle == NULL) {
        return GGL_KO;
    }
    glBindVertexArray(g_triangle_renderer._vao);
    glBindBuffer(GL_ARRAY_BUFFER, triangle->__vbo__);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glUseProgram(g_triangle_renderer._shader_program);
    pos_location = glGetUniformLocation(g_triangle_renderer._shader_program, "u_position");
    size_location = glGetUniformLocation(g_triangle_renderer._shader_program, "u_size");
    color_location = glGetUniformLocation(g_triangle_renderer._shader_program, "u_color");
    glUniform2f(pos_location, triangle->_position._x, triangle->_position._y);
    glUniform2f(size_location, triangle->_size._x, triangle->_size._y);
    glUniform4f(color_location, 
        triangle->_color._r / 255.0f,
        triangle->_color._g / 255.0f,
        triangle->_color._b / 255.0f,
        triangle->_color._a / 255.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    return GGL_OK;
}

/**
 * @brief Create a triangle.
 *
 * @param position              The pos of the triangle using ggl_vector2f
 * @param size                  The size of the trignale using ggl_vector2f
 * @param color                 The color of the triangle using ggl_color
 *
 * @return The triangle geometry structure.
 */
ggl_triangle *
ggl_triangle_create(ggl_vector2f position, ggl_vector2f size, ggl_color color)
{
    ggl_triangle *triangle = malloc(sizeof(ggl_triangle));

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    if (g_triangle_renderer._is_initialized == GGL_FALSE) {
        __ggl_triangle_init();
    } 
    glGenBuffers(1, &triangle->__vbo__);
    glBindBuffer(GL_ARRAY_BUFFER, triangle->__vbo__);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    triangle->_position = position;
    triangle->_color = color;
    triangle->_size = size;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return triangle;
}
