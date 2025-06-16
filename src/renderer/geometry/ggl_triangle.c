/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_triangle
** File description:
** GGL render triangle geometry
*/

#include "ggl.h"

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
    ggl_ressource_id _sampler_texture_location;
    ggl_bool _is_initialized;
} ggl_triangle_renderer;
static ggl_triangle_renderer g_triangle_renderer = {0};

const char *GGL_TRIANGLE_VERTEX_SHADER =
    "#version 330 core\n"
    "layout (location = 0) in vec3 l_pos;\n"
    "layout (location = 1) in vec2 l_texcoord;\n"
    "uniform vec2 u_position;\n"
    "uniform vec2 u_size;\n"
    "uniform float u_rad;\n"
    "uniform vec2 u_center;\n"
    "out vec2 tex_coord;\n"
    "void main() {\n"
    "    vec2 pos = l_pos.xy - u_center;\n"
    "    float cos_r = cos(u_rad);\n"
    "    float sin_r = sin(u_rad);\n"
    "    vec2 rotated = vec2(\n"
    "        pos.x * cos_r - pos.y * sin_r,\n"
    "        pos.x * sin_r + pos.y * cos_r\n"
    "    );\n"
    "    rotated.x = rotated.x + u_center.x;\n"
    "    rotated.y = rotated.y + u_center.y;\n"
    "    vec2 scaled = rotated * u_size;\n"
    "    vec2 final_pos = scaled + u_position;\n"
    "    gl_Position = vec4(final_pos, 0.0, 1.0);\n"
    "    tex_coord = l_texcoord;\n"
    "}";

const char *GGL_TRIANGLE_FRAGMENT_SHADER =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "uniform vec4 u_color;\n"
    "in vec2 tex_coord;\n"
    "uniform sampler2D u_sampler_texture;\n"
    "void main() {\n"
    "   frag_color = texture(u_sampler_texture, tex_coord) * u_color;\n"
    "}";

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
    triangle->_info.__texture_id__ = 0;
    triangle->_info._position = position;
    triangle->_info._color = color;
    triangle->_info._rotation = 0.0f;
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
