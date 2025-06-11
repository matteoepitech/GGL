/*
** GGL PROJECT, 2025
** src/shader/ggl_shader_helper
** File description:
** GGL file for shader helper
*/

#include "ggl.h"

/**
 * @brief Get a var location in a shader.
 *
 * @param program_id            The program ID
 * @param var_name              The var name
 *
 * @return The location of the var.
 */
ggl_ressource_id
ggl_get_shader_var_location(ggl_ressource_id program_id,
                            const char *var_name)
{
    if (program_id == 0 || var_name == NULL)
        return 0;
    return glGetUniformLocation(program_id, var_name);
}
