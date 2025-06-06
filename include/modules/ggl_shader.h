/*
** GGL PROJECT, 2025
** include/modules/ggl_shader.h
** File description:
** GGL Shader module header file
*/

#ifndef _GGL_MODULE_SHADER_H_
    #define _GGL_MODULE_SHADER_H_

    #include "../misc/ggl_types.h"

/*
 * Location : src/utils/shader/ggl_shader_compiler.c
 */
ggl_ressource_id compile_shader(unsigned int type, const char* source_str);

#endif /* ifndef _GGL_MODULE_SHADER_H_ */
