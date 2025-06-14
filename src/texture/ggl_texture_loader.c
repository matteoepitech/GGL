/*
** GGL PROJECT, 2025
** src/renderer/geometry/ggl_texture_loader
** File description:
** GGL functions for loading/creating textures
*/

#include "ggl.h"
#include "ggl_internal.h"
#include "misc/ggl_macros.h"
#include "stb_image.h"

// @INTERNAL USAGE : When no texture is passed we use a blank texture.
ggl_ressource_id __texture_id_white__ = 0;

/**
 * @brief Create a blank texture. This function should be called 1 time only.
 *
 * @return The ressource ID of the texture white.
 */
static ggl_ressource_id
ggl_create_blank_texture(void)
{
    unsigned char white_pixel[4] = { 255, 255, 255, 255 };

    glGenTextures(1, &__texture_id_white__);
    glBindTexture(GL_TEXTURE_2D, __texture_id_white__);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, white_pixel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    return __texture_id_white__;
}

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
    glActiveTexture(GL_TEXTURE0);
    if (tid == 0) {
        if (__texture_id_white__ == 0) {
            GGL_DEBUG("Creating the blank texture.");
            ggl_create_blank_texture();
        }
        glBindTexture(GL_TEXTURE_2D, __texture_id_white__);
        return GGL_TRUE;
    }
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
