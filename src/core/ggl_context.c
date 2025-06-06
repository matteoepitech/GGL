/*
** EPITECH PROJECT, 2025
** src/core/ggl_context
** File description:
** GGL context file
*/

#include "ggl.h"

// @brief context global variable.
ggl_context *__ggl_context__;

/**
 * @brief Get the context using this function.
 *
 * @return The context structure.
 */
ggl_context *
ggl_get_context(void)
{
    if (__ggl_context__ == NULL)
        return NULL;
    return __ggl_context__;
}
