/*
** GGL PROJECT, 2025
** include/misc/ggl_types.h
** File description:
** GGL header file for types
*/

#ifndef _GGL_TYPES_H_
    #define _GGL_TYPES_H_
    
    #include <assert.h>
    #include <errno.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <GLFW/glfw3.h>
    
    #include <GLFW/glfw3.h>

/**
 * @brief Used for status of functions.
 */
typedef int8_t ggl_status;

/**
 * @brief Used for bool.
 */
typedef int8_t ggl_bool;

/**
 * @brief Used for inputs.
 */
typedef int32_t ggl_key;

/**
 * @brief Type for coordinates in a 2D plan.
 */
typedef struct ggl_coords_s {
    int64_t _x;
    int64_t _y;
} ggl_coords_t;

/**
 * @brief Type for size.
 */
typedef struct ggl_size_s {
    int64_t _width;
    int64_t _height;
} ggl_vector2i_t;

/**
 * @brief Type for color. RGBA
 */
typedef struct ggl_color_s {
    int32_t _r;
    int32_t _g;
    int32_t _b;
    int32_t _a;
} ggl_color_t;

/**
 * @brief GGL window structure containing all informations about windows.
 */
typedef struct ggl_window_s {
    GLFWwindow *_win_glfw;
} ggl_window_t;

/**
 * @brief A context contains all informations about a program entirely.
 */
typedef struct ggl_context_s {
    ggl_window_t _ggl_window;
} ggl_context_t;


#endif /* ifndef _GGL_TYPES_H_ */
