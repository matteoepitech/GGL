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
    #include <time.h>
    #include <stdlib.h>
    
    #include <OpenGL/gl3.h>
    #include <GLFW/glfw3.h>

    #include "ggl_defines.h"

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
 * @brief Used for ressource like createShader, program VAO, VBO, EBO..
 */
typedef uint32_t ggl_ressource_id;


// =====================================

/**
 * @brief Type for vector 2 int.
 */
typedef struct {
    int64_t _x;
    int64_t _y;
} ggl_vector2i;

/**
 * @brief Type for vector 2 float.
 */
typedef struct {
    float _x;
    float _y;
} ggl_vector2f;

/**
 * @brief Type for bound, like bounds of a rectangle.
 */
typedef struct {
    float _start_x;
    float _start_y;
    float _end_x;
    float _end_y;
} ggl_bounds;

/**
 * @brief Type for color. RGBA
 */
typedef struct {
    int32_t _r;
    int32_t _g;
    int32_t _b;
    int32_t _a;
} ggl_color;


// =====================================

/**
 * @brief GGL window structure containing all informations about windows.
 */
typedef struct {
    GLFWwindow *_win_glfw;
    int32_t _fb_width;
    int32_t _fb_height;
    int32_t _fb_ref_width;
    int32_t _fb_ref_height;
    int32_t _ref_width;
    int32_t _ref_height;
} ggl_window;

/**
 * @brief A context contains all informations about a program entirely.
 */
typedef struct {
    ggl_window _ggl_window;
    double _current_fps;
} ggl_context;


// =====================================

/**
 * @brief Triangle structure object.
 */
typedef struct {
    ggl_vector2f _position;
    ggl_vector2f _size;
    ggl_color _color;
} ggl_triangle;

/**
 * @brief Rectangle structure object.
 */
typedef struct {
    ggl_vector2f _position;
    ggl_vector2f _size;
    ggl_color _color;
} ggl_rectangle;

/**
 * @brief Convex structure object.
 */
typedef struct {
    ggl_vector2f _position;
    float *_vertices;
    ggl_color *_vertices_color;
    uint32_t _vertices_count;
    uint32_t *_indices;
    ggl_ressource_id __vao__; // @INTERNAL USAGE
    ggl_ressource_id __vbo__; // @INTERNAL USAGE
    ggl_ressource_id __ebo__; // @INTERNAL USAGE
} ggl_convex;

#endif /* ifndef _GGL_TYPES_H_ */
