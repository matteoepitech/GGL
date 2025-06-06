/*
** GGL PROJECT, 2025
** include/modules/ggl_core.h
** File description:
** GGL Core module header file
*/

#ifndef _GGL_MODULE_CORE_H_
    #define _GGL_MODULE_CORE_H_

    #include "../misc/ggl_types.h"
    #include "../misc/ggl_defines.h"

/*
 * Location : src/core/ggl_init.c
 */
ggl_status ggl_init(void);
ggl_status ggl_terminate(void);

/*
 * Location : src/core/ggl_context.c
 */
extern ggl_context *__ggl_context__;
ggl_context *ggl_get_context(void);

#endif /* ifndef _GGL_MODULE_CORE_H */
