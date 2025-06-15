/*
** GGL PROJECT, 2025
** include/modules/ggl_texture.h
** File description:
** GGL Texture module header file
*/

#ifndef _GGL_MODULE_TEXTURE_H_
    #define _GGL_MODULE_TEXTURE_H_
    
    #include "../misc/ggl_types.h"

/**
 * @brief Create a texture.
 *
 * @param texture_path          The path of the texture
 *
 * @return The texture structure allocated in the memory.
 */
ggl_texture *ggl_texture_create(const char *texture_path);

/**
 * @brief Load a texture from his ID.
 *        INTERNAL USAGE
 *
 * @param tid                   The ID of the texture
 *
 * @return GGL_TRUE if loaded. GGL_FALSE otherwise.
 */
ggl_bool __ggl_texture_load_from_id(ggl_ressource_id tid);

/**
 * @brief Unload the current binded texture.
 *        INTERNAL USAGE
 *
 * @return GGL_OK.
 */
ggl_status __ggl_texture_unload(void);

#endif /* ifndef _GGL_MODULE_TEXTURE_H_ */
