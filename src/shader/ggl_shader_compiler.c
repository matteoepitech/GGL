/*
** GGL PROJECT, 2025
** src/shader/ggl_shader_compiler
** File description:
** GGL file for shader compiling
*/

#include "ggl.h"

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
