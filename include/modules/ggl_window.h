/*
** GGL PROJECT, 2025
** include/modules/ggl_window.h
** File description:
** GGL Window module header file
*/

#ifndef _GGL_MODULE_WINDOW_H_
    #define _GGL_MODULE_WINDOW_H_
    
    #include "../misc/ggl_types.h"
    #include "../misc/ggl_defines.h"

/*
 * Location : src/window/ggl_window_manager.c
 */
ggl_status ggl_create_window(const char *title, ggl_vector2i size);
ggl_bool ggl_window_should_close(ggl_context *ctx);
ggl_status ggl_clear_window(ggl_color background_color);

#endif /* ifndef _GGL_MODULE_WINDOW_H_ */
