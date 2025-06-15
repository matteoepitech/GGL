/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_convex
** File description:
** GGL render convex geometry
*/

#include "ggl.h"

// ==============================================================

/**
 * @brief Content of the geometry convex.
 *        Singleton of it using static variable.
 */
typedef struct {
    ggl_ressource_id _shader_program;
    ggl_ressource_id _pos_location;
    ggl_ressource_id _size_location;
    ggl_ressource_id _color_location;
    ggl_bool _is_initialized;
} ggl_convex_renderer;
static ggl_convex_renderer g_convex_renderer = {0};

const char *GGL_CONVEX_VERTEX_SHADER =
    "#version 330 core\n"
    "layout (location = 0) in vec3 l_pos;\n"
    "layout (location = 1) in vec4 l_color;\n"
    "uniform vec2 u_position;\n"
    "uniform vec2 u_size;\n"
    "out vec4 v_color;\n"
    "void main() {\n"
    "    vec2 final_size = vec2(u_size.x, u_size.y * -1);\n"
    "    vec3 scaled_pos = l_pos * vec3(final_size, 1.0);\n"
    "    gl_Position = vec4(scaled_pos.xy + u_position, 0.0, 1.0);\n"
    "    v_color = l_color;\n"
    "}\0";

const char *GGL_CONVEX_FRAGMENT_SHADER =
    "#version 330 core\n"
    "in vec4 v_color;\n"
    "out vec4 frag_color;\n"
    "uniform vec4 u_color;\n"
    "void main() {\n"
    "    frag_color = v_color;\n"
    "}\0";

// ==============================================================

/**
 * @brief Update the VAO/VBO/EBO of the convex shape.
 *        @INFO the vertex data has the following pattern :
 *        x,y,z,r,g,b,a so 7 bytes is 1 stride.
 *
 * @param convex                The shape structure pointer
 *
 * @return GGL_OK or GGL_KO.
 */
static ggl_status
__ggl_convex_update(ggl_convex *convex)
{
    uint32_t *indices_arr = NULL;
    float *vertex_data = NULL;
    int indices_count = 0;
    int vertex_data_size = 0;

    if (convex == NULL || convex->_vertices == NULL)
        return GGL_KO;
    if (convex->_vertices_count >= 3) {
        indices_count = (convex->_vertices_count - 2) * 3;
    }
    if (indices_count == 0 || convex->_indices == NULL) {
        return GGL_KO;
    }
    indices_arr = convex->_indices;
    vertex_data_size = convex->_vertices_count * 7;
    vertex_data = malloc(sizeof(float) * vertex_data_size);
    for (int i = 0; i < convex->_vertices_count; i++) {
        vertex_data[i * 7 + 0] = convex->_vertices[i * 3 + 0];
        vertex_data[i * 7 + 1] = convex->_vertices[i * 3 + 1];
        vertex_data[i * 7 + 2] = convex->_vertices[i * 3 + 2];
        vertex_data[i * 7 + 3] = convex->_vertices_color[i]._r / 255.0f;
        vertex_data[i * 7 + 4] = convex->_vertices_color[i]._g / 255.0f;
        vertex_data[i * 7 + 5] = convex->_vertices_color[i]._b / 255.0f;
        vertex_data[i * 7 + 6] = convex->_vertices_color[i]._a / 255.0f;
    } 
    glGenVertexArrays(1, &convex->__vao__);
    glBindVertexArray(convex->__vao__);
    glGenBuffers(1, &convex->__ebo__);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, convex->__ebo__);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices_count,
        indices_arr, GL_STATIC_DRAW); 
    glGenBuffers(1, &convex->__vbo__);
    glBindBuffer(GL_ARRAY_BUFFER, convex->__vbo__);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data_size,
        vertex_data, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    free(vertex_data);
    return GGL_OK;
}

/**
 * @brief convex init.
 *        DO NOT CALL THIS FUNCTION only if you know what to do.
 *
 * @return GGL_OK if the init was fine.
 */
static ggl_status
__ggl_convex_init(void)
{
    ggl_ressource_id vertex_shader = 0;
    ggl_ressource_id fragment_shader = 0;

    if (g_convex_renderer._is_initialized == GGL_TRUE) {
        return GGL_OK;
    }
    vertex_shader = ggl_shader_create(GL_VERTEX_SHADER, GGL_CONVEX_VERTEX_SHADER);
    fragment_shader = ggl_shader_create(GL_FRAGMENT_SHADER, GGL_CONVEX_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        return GGL_KO;
    } 
    g_convex_renderer._shader_program = glCreateProgram();
    glAttachShader(g_convex_renderer._shader_program, vertex_shader);
    glAttachShader(g_convex_renderer._shader_program, fragment_shader);
    glLinkProgram(g_convex_renderer._shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    g_convex_renderer._pos_location = ggl_get_shader_var_location(g_convex_renderer._shader_program, "u_position");
    g_convex_renderer._size_location = ggl_get_shader_var_location(g_convex_renderer._shader_program, "u_size");
    g_convex_renderer._color_location = ggl_get_shader_var_location(g_convex_renderer._shader_program, "u_color");
    g_convex_renderer._is_initialized = GGL_TRUE;
    return GGL_OK;
}

/**
 * @brief Create a convex.
 *
 * @param position              The pos of the convex using ggl_vector2f
 *
 * @return The convex geometry structure.
 */
ggl_convex *
ggl_convex_create(ggl_vector2f position)
{
    ggl_convex *convex = malloc(sizeof(ggl_convex));

    if (convex == NULL) {
        return NULL;
    }
    if (g_convex_renderer._is_initialized == GGL_FALSE) {
        __ggl_convex_init();
    }
    convex->_position = position;
    convex->_vertices = NULL;
    convex->_indices = NULL;
    convex->_vertices_color = NULL;
    convex->_vertices_count = 0;
    return convex;
}

/**
 * @brief Free a convex.
 *
 * @param convex                The convex
 *
 * @return GGL_TRUE if everything worked. GGL_FALSE otherwise.
 */
ggl_bool
ggl_convex_free(ggl_convex *convex)
{
    if (convex == NULL)
        return GGL_FALSE;
    free(convex->_vertices_color);
    free(convex->_vertices);
    free(convex->_indices);
    free(convex);
    return GGL_TRUE;
}

/**
 * @brief Render a convex.
 *
 * @param ctx                    The context
 * @param convex              The convex to render
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_convex_render(ggl_context *ctx,
                  const ggl_convex *convex)
{
    ggl_vector2f final_pos = {0};
    ggl_vector2f final_size = {0};

    if (convex == NULL || ctx == NULL || convex->_vertices_count < 0) {
        return GGL_KO;
    }
    final_pos = ggl_coords_normalize_to_ndc_pos(ctx, convex->_position);
    final_size = ggl_coords_normalize_to_ndc_size(ctx, (ggl_vector2f) {1, 1});
    glBindVertexArray(convex->__vao__);
    glUseProgram(g_convex_renderer._shader_program);
    glUniform2f(g_convex_renderer._pos_location, final_pos._x, final_pos._y);
    glUniform2f(g_convex_renderer._size_location, final_size._x, final_size._y);
    glDrawElements(GL_TRIANGLES, (convex->_vertices_count - 2) * 3, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    return GGL_OK;
}

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
ggl_convex *
ggl_convex_add_vertex(ggl_convex *convex,
                      ggl_vector2f position,
                      ggl_color color)
{
    int triangle_count = 0;

    if (convex == NULL)
        return NULL;
    convex->_vertices_count++;
    convex->_vertices = realloc(convex->_vertices,
        sizeof(float) * 3 * convex->_vertices_count);
    convex->_vertices[(3 * convex->_vertices_count) - 3] = position._x;
    convex->_vertices[(3 * convex->_vertices_count) - 2] = position._y;
    convex->_vertices[(3 * convex->_vertices_count) - 1] = 0.0f;
    convex->_vertices_color = realloc(convex->_vertices_color,
        sizeof(ggl_color) * convex->_vertices_count);
    convex->_vertices_color[convex->_vertices_count - 1] = color;
    if (convex->_vertices_count >= 3) {
        triangle_count = convex->_vertices_count - 2;
        convex->_indices = realloc(convex->_indices,
            sizeof(uint32_t) * triangle_count * 3);
        for (int i = 0; i < triangle_count; i++) {
            convex->_indices[i * 3] = 0;
            convex->_indices[i * 3 + 1] = i + 1;
            convex->_indices[i * 3 + 2] = i + 2;
        }
    }
    __ggl_convex_update(convex);
    return convex;
}

/**
 * @brief Set color for a specific vertex.
 *
 * @param convex                The convex shape
 * @param vertex_index          The index of the vertex
 * @param color                 The color to set
 *
 * @return GGL_OK if successful, GGL_KO otherwise.
 */
ggl_status
ggl_convex_set_vertex_color(ggl_convex *convex,
                            int vertex_index,
                            ggl_color color)
{
    if (convex == NULL || vertex_index < 0 ||
        vertex_index >= convex->_vertices_count) {
        return GGL_KO;
    } 
    convex->_vertices_color[vertex_index] = color;
    __ggl_convex_update(convex);
    return GGL_OK;
}

/**
 * @brief Get color of a specific vertex.
 *
 * @param convex                The convex shape
 * @param vertex_index          The index of the vertex
 *
 * @return The color of the vertex.
 */
ggl_color
ggl_convex_get_vertex_color(ggl_convex *convex,
                            int vertex_index)
{
    if (convex == NULL || vertex_index < 0 ||
        vertex_index >= convex->_vertices_count) {
        return (ggl_color) {0, 0, 0, 0};
    } 
    return convex->_vertices_color[vertex_index];
}

/**
 * @brief Get the position of the convex shape.
 *
 * @param convex        The shape
 *
 * @return The position.
 */
ggl_vector2f
ggl_convex_get_position(ggl_convex *convex)
{
    return convex->_position;
}

/**
 * @brief Set the position of the convex shape.
 *
 * @param convex                The shape
 * @param position              The position
 *
 * @return The new position.
 */
ggl_vector2f
ggl_convex_set_position(ggl_convex *convex,
                        ggl_vector2f position)
{
    convex->_position = position;
    return position;
}
