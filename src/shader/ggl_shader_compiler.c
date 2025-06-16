/*
** GGL PROJECT, 2025
** src/shader/ggl_shader_compiler
** File description:
** GGL file for shader compiling
*/

#include "ggl.h"

/**
 * @brief GGL Read a shader from file and give the output in a char *.
 *
 * @param path          The point of the file
 *
 * @return The char pointer.
 */
static char *
__ggl_read_shader_file(const char *path)
{
    FILE *file = fopen(path, "rb");
    char *buffer = NULL;
    long len = 0;

    if (file == NULL) {
        GGL_PERROR("Impossible to open %s.", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    rewind(file);
    buffer = malloc(len + 1);
    fread(buffer, 1, len, file);
    buffer[len] = '\0';
    fclose(file);
    return buffer;
}

/**
 * @brief Init all shaders.
 *
 * @return GGL_TRUE if worked. GGL_FALSE otherwise.
 */
ggl_bool
__ggl_shader_init(void)
{
    GGL_TRIANGLE_FRAGMENT_SHADER = __ggl_read_shader_file("/Users/del/Desktop/tmp_shaders/s_triangle.frag");
    if (GGL_TRIANGLE_FRAGMENT_SHADER == NULL)
        return GGL_FALSE;
    GGL_TRIANGLE_VERTEX_SHADER = __ggl_read_shader_file("/Users/del/Desktop/tmp_shaders/s_triangle.vert");
    if (GGL_TRIANGLE_VERTEX_SHADER == NULL)
        return GGL_FALSE;
    GGL_CIRCLE_FRAGMENT_SHADER = __ggl_read_shader_file("/Users/del/Desktop/tmp_shaders/s_circle.frag");
    if (GGL_CIRCLE_FRAGMENT_SHADER == NULL)
        return GGL_FALSE;
    GGL_CIRCLE_VERTEX_SHADER = __ggl_read_shader_file("/Users/del/Desktop/tmp_shaders/s_circle.vert");
    if (GGL_CIRCLE_VERTEX_SHADER == NULL)
        return GGL_FALSE;
    GGL_CONVEX_FRAGMENT_SHADER = __ggl_read_shader_file("/Users/del/Desktop/tmp_shaders/s_convex.frag");
    if (GGL_CONVEX_FRAGMENT_SHADER == NULL)
        return GGL_FALSE;
    GGL_CONVEX_VERTEX_SHADER = __ggl_read_shader_file("/Users/del/Desktop/tmp_shaders/s_convex.vert");
    if (GGL_CONVEX_VERTEX_SHADER == NULL)
        return GGL_FALSE;
    return GGL_TRUE;
}

/**
 * @brief Compile a shader using the type of the shader in OpenGL
 *        and the string of the content of the shader.
 *
 * @param type          The type of the shader
 * @param source_str    The string of the shader
 *
 * @return The ID of the ressource we just created.
 */
ggl_ressource_id
ggl_shader_create(unsigned int type,
                  const char* source_str)
{
    ggl_ressource_id shader = glCreateShader(type);
    char infoLog[512] = {0};
    int success = 0;

    glShaderSource(shader, 1, &source_str, NULL);
    glCompileShader(shader);    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GGL_FALSE) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader compilation error (%s): %s\n", 
            (type == GL_VERTEX_SHADER) ? "vertex" : "fragment", infoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
