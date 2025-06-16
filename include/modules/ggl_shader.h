/*
** GGL PROJECT, 2025
** include/modules/ggl_shader.h
** File description:
** GGL Shader module header file
*/

#ifndef _GGL_MODULE_SHADER_H_
    #define _GGL_MODULE_SHADER_H_

    #include "../misc/ggl_types.h"

// @brief Internal shaders
extern char *GGL_TRIANGLE_VERTEX_SHADER;
extern char *GGL_TRIANGLE_FRAGMENT_SHADER;

extern char *GGL_CONVEX_VERTEX_SHADER;
extern char *GGL_CONVEX_FRAGMENT_SHADER;

extern char *GGL_CIRCLE_VERTEX_SHADER;
extern char *GGL_CIRCLE_FRAGMENT_SHADER;

/**
 * @brief Init all shaders.
 *
 * @return GGL_TRUE if worked. GGL_FALSE otherwise.
 */
ggl_bool __ggl_shader_init(void);

/**
 * @brief Get a var location in a shader.
 *
 * @param program_id            The program ID
 * @param var_name              The var name
 *
 * @return The location of the var.
 */
ggl_ressource_id ggl_get_shader_var_location(ggl_ressource_id program_id,
                                             const char *var_name);

/**
 * @brief Compile a shader using the type of the shader in OpenGL
 *        and the string of the content of the shader.
 *
 * @param type          The type of the shader
 * @param source_str    The string of the shader
 *
 * @return The ID of the ressource we just created.
 */
ggl_ressource_id ggl_shader_create(unsigned int type,
                                   const char* source_str);

#endif /* ifndef _GGL_MODULE_SHADER_H_ */
