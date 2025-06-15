/*
** GGL PROJECT, 2025
** include/modules/ggl_core.h
** File description:
** GGL Core module header file
*/

#ifndef _GGL_MODULE_CORE_H_
    #define _GGL_MODULE_CORE_H_

    #include "../misc/ggl_types.h"

/**
 * @brief Init of GGL. This is the first function you should call.
 *
 * @return The context of the GGL program.
 */
ggl_context *ggl_init(void);

/**
 * @brief Terminate the GGL library. This is the last function you
 *        should call
 *
 * @return GGL_OK if everything worked, GGL_KO, if not.
 */
ggl_status ggl_terminate(ggl_context *ctx);

#endif /* ifndef _GGL_MODULE_CORE_H */
