/*
** GGL PROJECT, 2025
** include/modules/ggl_window.h
** File description:
** GGL Window module header file
*/

#ifndef _GGL_MODULE_WINDOW_H_
    #define _GGL_MODULE_WINDOW_H_
    
    #include "../misc/ggl_types.h"

/**
 * @brief Create a GGL window.
 *
 * @param ctx           The context
 * @param title         The title of the window
 * @param size          The size of the window
 *
 * @return GGL_OK if everything worked. GGL_KO if not.
 */
ggl_status ggl_create_window(ggl_context *ctx,
                             const char *title,
                             ggl_vector2i size);

/**
 * @brief Clear the window and put this background color.
 *
 * @param background_color      The background color
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status ggl_clear_window(ggl_color background_color);

/**
 * @brief Is the window need to be closed ?
 *        It does the swap buffers and poll events as well, and FPS.
 *
 * @param ctx           The context of the program
 *
 * @return GGL_TRUE if yes GGL_FALSE if no.
 */
ggl_bool ggl_window_should_close(ggl_context *ctx);

/**
 * @brief Get the height of the window.
 *
 * @param ctx           The context
 *
 * @return The height of the window.
 */
ggl_int ggl_get_window_height(ggl_context *ctx);

/**
 * @brief Get the width of the window.
 *
 * @param ctx           The context
 *
 * @return The width of the window.
 */
ggl_int ggl_get_window_width(ggl_context *ctx);

/**
 * @brief Get the size of the window.
 *
 * @param ctx           The context
 *
 * @return The size of the window.
 */
ggl_vector2f ggl_get_window_size(ggl_context *ctx);

#endif /* ifndef _GGL_MODULE_WINDOW_H_ */
