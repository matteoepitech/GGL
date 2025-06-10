/*
** GGL PROJECT, 2025
** include/modules/ggl_texture.h
** File description:
** GGL Texture module header file
*/

#ifndef _GGL_MODULE_TEXTURE_H_
    #define _GGL_MODULE_TEXTURE_H_
    
    #include "../misc/ggl_types.h"

/*
 * Location : src/texture/ggl_texture_loader.c
 */
ggl_texture *ggl_texture_create(const char *texture_path);

#endif /* ifndef _GGL_MODULE_TEXTURE_H_ */
