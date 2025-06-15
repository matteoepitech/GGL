/*
** GGL PROJECT, 2025
** include/modules/ggl_input.h
** File description:
** GGL Input module header file
*/

#ifndef _GGL_MODULE_INPUT_H_
    #define _GGL_MODULE_INPUT_H_
    
    #include "../misc/ggl_types.h"

/**
 * @brief Setup the debug close. If you don't call this function
 *        you will not gonna have this feature.
 *
 * @param ctx           The context
 *
 * @return GGL_OK if worked, GGL_KO if not.
 */
ggl_status ggl_setup_debug_close(ggl_context *ctx);

/**
 * @brief Is a key is down or not.
 *
 * @param ctx           The context
 * @param key           The key (int)
 *
 * @return GGL_TRUE or GGL_FALSE.
 */
ggl_bool ggl_is_key_down(ggl_context *ctx,
                         ggl_key key);

/**
 * @brief Get cursor position using context. SCREEN position.
 *
 * @param ctx           The context
 *
 * @return The vector of position.
 */
ggl_vector2f ggl_get_cursor_screen_position(ggl_context *ctx);

/**
 * @brief Get cursor position using context. SCALED position
 *        (adapted to framebuffer).
 *
 * @param ctx           The context
 *
 * @return The vector of position (scaled to reference resolution).
 */
ggl_vector2f ggl_get_cursor_scaled_position(ggl_context *ctx);

#endif /* ifndef _GGL_MODULE_INPUT_H_ */
