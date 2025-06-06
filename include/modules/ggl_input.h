/*
** GGL PROJECT, 2025
** include/modules/ggl_input.h
** File description:
** GGL Input module header file
*/

#ifndef _GGL_MODULE_INPUT_H_
    #define _GGL_MODULE_INPUT_H_
    
    #include "../misc/ggl_types.h"
    #include "../misc/ggl_defines.h"
    
    #include <GLFW/glfw3.h>

/*
 * Location : src/input/ggl_debug_close.c
 */
ggl_status ggl_setup_debug_close(ggl_context_t *ctx);

/*
 * Location : src/input/ggl_input_manager.c
 */
ggl_bool ggl_is_key_down(ggl_context_t *ctx, ggl_key key);

#endif /* ifndef _GGL_MODULE_INPUT_H_ */
