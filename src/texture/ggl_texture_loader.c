/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_texture_loader
** File description:
** GGL functions for loading/creating textures
*/

#include "ggl.h"
#include "stb_image.h"

/**
 * @brief Create a texture.
 *
 * @param texture_path          The path of the texture
 *
 * @return The texture structure allocated in the memory.
 */
ggl_texture *
ggl_texture_create(const char *texture_path)
{
    ggl_texture *tex = NULL;

    if (texture_path == NULL)
        return NULL;
    stbi_set_flip_vertically_on_load(GGL_TRUE);
    tex = malloc(sizeof(ggl_texture));
    tex->_data = stbi_load(texture_path, &tex->_width,
        &tex->_height, &tex->_nr_channels, 0);
    if (tex->_data == NULL) {
        free(tex);
        return NULL;
    }
    return tex;
}

/**
 * @brief Load a texture from his ID.
 *
 * @param tid
 *
 * @return GGL_TRUE if loaded. GGL_FALSE otherwise.
 */
ggl_bool
ggl_texture_load_from_id(ggl_ressource_id tid)
{
    if (tid == 0)
        return GGL_FALSE;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tid);
    return GGL_TRUE;
}

/**
 * @brief Unload the current binded texture.
 *
 * @return GGL_OK.
 */
ggl_status
ggl_texture_unload(void)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    return GGL_OK;
}
