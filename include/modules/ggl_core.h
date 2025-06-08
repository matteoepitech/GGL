/*
** GGL PROJECT, 2025
** include/modules/ggl_core.h
** File description:
** GGL Core module header file
*/

#ifndef _GGL_MODULE_CORE_H_
    #define _GGL_MODULE_CORE_H_

    #include "../misc/ggl_types.h"

/*
 * Location : src/core/ggl_init.c
 */
ggl_context *ggl_init(void);
ggl_status ggl_terminate(ggl_context *ctx);

/*
 * Location : src/core/ggl_cursor.c
 */
ggl_vector2f ggl_get_cursor_position(ggl_context *ctx);

#endif /* ifndef _GGL_MODULE_CORE_H */
