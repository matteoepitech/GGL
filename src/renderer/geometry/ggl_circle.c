/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_circle
** File description:
** GGL render circle geometry
*/

#include "ggl.h"

// ==============================================================

/**
 * @brief Content of the geometry circle.
 *        Singleton of it using static variable.
 */
typedef struct {
    ggl_ressource_id _vao;
    ggl_ressource_id _vbo;
    ggl_ressource_id _shader_program;
    ggl_ressource_id _pos_location;
    ggl_ressource_id _size_location;
    ggl_ressource_id _color_location;
    ggl_bool _is_initialized;
} ggl_circle_renderer;
static ggl_circle_renderer g_circle_renderer = {0};

const char *GGL_CIRCLE_VERTEX_SHADER =
    "#version 330 core\n"
    "layout (location = 0) in vec3 l_pos;\n"
    "layout (location = 1) in vec4 l_color;\n"
    "uniform vec2 u_position;\n"
    "uniform vec2 u_size;\n"
    "void main() {\n"
    "    vec3 scaled_pos = l_pos * vec3(u_size, 1.0);\n"
    "    gl_Position = vec4(scaled_pos.xy + u_position, 0.0, 1.0);\n"
    "}";

const char *GGL_CIRCLE_FRAGMENT_SHADER =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "uniform vec4 u_color;\n"
    "void main() {\n"
    "    frag_color = u_color;\n"
    "}";

// ==============================================================

/**
 * @brief circle init.
 *        DO NOT CALL THIS FUNCTION only if you know what to do.
 *
 * @return GGL_OK if the init was fine.
 */
static ggl_status
__ggl_circle_init(void)
{
    ggl_ressource_id vertex_shader = 0;
    ggl_ressource_id fragment_shader = 0;

    if (g_circle_renderer._is_initialized == GGL_TRUE) {
        return GGL_OK;
    }
    vertex_shader = ggl_create_shader(GL_VERTEX_SHADER, GGL_CIRCLE_VERTEX_SHADER);
    fragment_shader = ggl_create_shader(GL_FRAGMENT_SHADER, GGL_CIRCLE_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return GGL_KO;
    } 
    g_circle_renderer._shader_program = glCreateProgram();
    glAttachShader(g_circle_renderer._shader_program, vertex_shader);
    glAttachShader(g_circle_renderer._shader_program, fragment_shader);
    glLinkProgram(g_circle_renderer._shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    g_circle_renderer._pos_location = ggl_get_shader_var_location(g_circle_renderer._shader_program, "u_position");
    g_circle_renderer._size_location = ggl_get_shader_var_location(g_circle_renderer._shader_program, "u_size");
    g_circle_renderer._color_location = ggl_get_shader_var_location(g_circle_renderer._shader_program, "u_color");
    g_circle_renderer._is_initialized = GGL_TRUE;
    return GGL_OK;
}

/**
 * @brief Build a circle with step.
 *
 * @param step          The number of step to make the circle smoother
 *
 * @return The array of vertices (X|Y|Z|X|Y|Z|...).
 */
static float *
__ggl_circle_build(ggl_int step)
{
    float angle = 360.0f / step;
    float *vertices = malloc(sizeof(float) * 3  * 3 * step);
    int vertex_index = 0;
    float c_angle_one = 0;
    float c_angle_two = 0;

    for (int i = 0; i < step; i++) {
        vertices[vertex_index++] = 0.0f;
        vertices[vertex_index++] = 0.0f;
        vertices[vertex_index++] = 0.0f;
        c_angle_one = angle * i;
        vertices[vertex_index++] = cos(GGL_DEG_TO_RAD(c_angle_one));
        vertices[vertex_index++] = sin(GGL_DEG_TO_RAD(c_angle_one));
        vertices[vertex_index++] = 0.0f;
        c_angle_two = angle * (i + 1);
        vertices[vertex_index++] = cos(GGL_DEG_TO_RAD(c_angle_two));
        vertices[vertex_index++] = sin(GGL_DEG_TO_RAD(c_angle_two));
        vertices[vertex_index++] = 0.0f;
    }
    return vertices;
}

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
ggl_circle *
ggl_circle_create(ggl_vector2f position,
                  ggl_int radius,
                  ggl_int step,
                  ggl_color color)
{
    ggl_circle *circle = malloc(sizeof(ggl_circle));
    float *vertices = NULL;

    if (circle == NULL) {
        return NULL;
    }
    if (g_circle_renderer._is_initialized == GGL_FALSE) {
        __ggl_circle_init();
    }
    vertices = __ggl_circle_build(step);
    circle->_info.__texture_id__ = 0;
    circle->_position = position;
    circle->_color = color;
    circle->_radius = radius;
    circle->_step = step;
    glGenVertexArrays(1, &circle->__vao__);
    glBindVertexArray(circle->__vao__);
    glGenBuffers(1, &circle->__vbo__);
    glBindBuffer(GL_ARRAY_BUFFER, circle->__vbo__);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3 * step, vertices, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    free(vertices);
    return circle;
}

/**
 * @brief Render a circle.
 *
 * @param ctx                    The context
 * @param circle              The circle to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_circle_render(ggl_context *ctx,
                  const ggl_circle *circle)
{
    ggl_vector2f final_pos = {0};
    ggl_vector2f final_size = {0};

    if (circle == NULL || ctx == NULL) {
        return GGL_KO;
    }
    final_pos = ggl_coords_normalize_to_ndc_pos(ctx, circle->_position);
    final_size = ggl_coords_normalize_to_ndc_size(ctx,
        (ggl_vector2f) { circle->_radius, circle->_radius});
    glBindVertexArray(circle->__vao__);
    glUseProgram(g_circle_renderer._shader_program);
    glUniform2f(g_circle_renderer._pos_location, final_pos._x, final_pos._y);
    glUniform2f(g_circle_renderer._size_location, final_size._x, final_size._y);
    glUniform4f(g_circle_renderer._color_location, 
        circle->_color._r / 255.0f,
        circle->_color._g / 255.0f,
        circle->_color._b / 255.0f,
        circle->_color._a / 255.0f);
    glDrawArrays(GL_TRIANGLES, 0, circle->_step * 3);
    glBindVertexArray(0);
    return GGL_OK;
}

/**
 * @brief circle get position.
 *
 * @param circle              The circle
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_circle_get_position(ggl_circle *circle)
{
    return circle->_position;
}

/**
 * @brief circle get color.
 *
 * @param circle              The circle
 *
 * @return The color.
 */
ggl_color
ggl_circle_get_color(ggl_circle *circle)
{
    return circle->_color;
}

/**
 * @brief circle get radius.
 *
 * @param circle              The circle
 *
 * @return The radius.
 */
ggl_int
ggl_circle_get_radius(ggl_circle *circle)
{
    return circle->_radius;
}

/**
 * @brief circle set position.
 *
 * @param circle             The circle
 * @param position              The new position
 *
 * @return The vector of position.
 */
ggl_vector2f
ggl_circle_set_position(ggl_circle *circle,
                        ggl_vector2f position)
{
    circle->_position = position;
    return position;
}

/**
 * @brief circle set color.
 *
 * @param circle             The circle
 * @param color                 The new color
 *
 * @return The color.
 */
ggl_color
ggl_circle_set_color(ggl_circle *circle,
                     ggl_color color)
{
    circle->_color = color;
    return color;
}

/**
 * @brief circle set radius.
 *
 * @param circle              The circle
 *
 * @return The radius.
 */
ggl_int
ggl_circle_set_radius(ggl_circle *circle,
                      ggl_int radius)
{
    circle->_radius = radius;
    return radius;
}

/**
 * @brief Set a texture for a circle.
 *
 * @param circle              The circle
 * @param texture               The texture to add
 *
 * @return GGL_OK.
 */
ggl_status
ggl_circle_set_texture(ggl_circle *circle,
                       ggl_texture *texture)
{
    if (circle->_info.__texture_id__ != 0) {
        glDeleteTextures(1, &circle->_info.__texture_id__);
    }
    glGenTextures(1, &circle->_info.__texture_id__);
    glBindTexture(GL_TEXTURE_2D, circle->_info.__texture_id__); 
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
