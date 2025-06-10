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
    tex = malloc(sizeof(ggl_texture));
    tex->_data = stbi_load(texture_path, &tex->_width,
        &tex->_height, &tex->_nr_channels, 0);
    if (tex->_data == NULL) {
        free(tex);
        return NULL;
    }
    return tex;
}
