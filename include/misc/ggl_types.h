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
    #include <math.h>
    
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
 * @brief Used for int values.
 */
typedef int32_t ggl_int;

/**
 * @brief Used for unsigned int values.
 */
typedef uint32_t ggl_uint;

/**
 * @brief Used for float values.
 */
typedef float ggl_float;


/**
 * @brief Used for double values.
 */
typedef double ggl_double;

/**
 * @brief Used for ressource like createShader, program VAO, VBO, EBO..
 */
typedef uint32_t ggl_ressource_id;


// =====================================

/**
 * @brief Type for vector 2 int.
 */
typedef struct {
    ggl_int _x;
    ggl_int _y;
} ggl_vector2i;

/**
 * @brief Type for vector 2 float.
 */
typedef struct {
    ggl_float _x;
    ggl_float _y;
} ggl_vector2f;

/**
 * @brief Type for color. RGBA
 */
typedef struct {
    ggl_int _r;
    ggl_int _g;
    ggl_int _b;
    ggl_int _a;
} ggl_color;


// =====================================

/**
 * @brief GGL window structure containing all informations about windows.
 */
typedef struct {
    GLFWwindow *_win_glfw;
    ggl_int _fb_width;
    ggl_int _fb_height;
    ggl_int _fb_ref_width;
    ggl_int _fb_ref_height;
    ggl_int _ref_width;
    ggl_int _ref_height;
} ggl_window;

/**
 * @brief A context contains all informations about a program entirely.
 */
typedef struct {
    ggl_window _ggl_window;
    ggl_double _current_fps;
} ggl_context;

/**
 * @brief A structure containins informations about a texture.
 */
typedef struct {
    ggl_int _width;
    ggl_int _height;
    ggl_int _nr_channels;
    unsigned char *_data;
} ggl_texture;

// =====================================

/**
 * @brief A structure containing misc data for a shape. Like textures,shaders..
 */
typedef struct {
    ggl_ressource_id __texture_id__;  // @INTERNAL USAGE;
} ggl_shape_data;

// =====================================

/**
 * @brief Triangle structure object.
 */
typedef struct {
    ggl_vector2f _position;
    ggl_vector2f _size;
    ggl_color _color;
    ggl_shape_data _info;
} ggl_triangle;

/**
 * @brief Rectangle structure object.
 */
typedef struct {
    ggl_vector2f _position;
    ggl_vector2f _size;
    ggl_color _color;
    ggl_shape_data _info;
} ggl_rectangle;

/**
 * @brief Convex structure object.
 */
typedef struct {
    ggl_vector2f _position;
    ggl_float *_vertices;
    ggl_color *_vertices_color;
    ggl_uint _vertices_count;
    ggl_uint *_indices;
    ggl_shape_data _info;
    ggl_ressource_id __vao__; // @INTERNAL USAGE
    ggl_ressource_id __vbo__; // @INTERNAL USAGE
    ggl_ressource_id __ebo__; // @INTERNAL USAGE
} ggl_convex;

/**
 * @brief Circle structure object.
 */
typedef struct {
    ggl_vector2f _position;
    ggl_int _radius;
    ggl_int _step;
    ggl_color _color;
    ggl_shape_data _info;
    ggl_ressource_id __vao__; // @INTERNAL USAGE
    ggl_ressource_id __vbo__; // @INTERNAL USAGE
    ggl_ressource_id __ebo__; // @INTERNAL USAGE
    ggl_int __triangle_count__; // @INTERNAL USAGE
} ggl_circle;

#endif /* ifndef _GGL_TYPES_H_ */
