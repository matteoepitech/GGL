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

    #include "ggl_window.h"

/**
 * @brief A context contains all informations about a program entirely.
 */
typedef struct ggl_context_s {
    ggl_window_t *_ggl_window;
} ggl_context_t;

/*
 * Location : src/core/ggl_init.c
 */
ggl_status ggl_init(void);
ggl_status ggl_terminate(void);

/*
 * Location : src/core/ggl_context.c
 */
extern ggl_context_t *__ggl_context__;
ggl_context_t *ggl_get_context(void);

#endif /* ifndef _GGL_MODULE_CORE_H */
