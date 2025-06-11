/*
** GGL PROJECT, 2025
** include/misc/ggl_macros.h
** File description:
** GGL header file for macros
*/

#ifndef _GGL_MACROS_H_
    #define _GGL_MACROS_H_

    #ifndef PERROR
        #define GGL_PERROR(...) \
            fprintf(stderr, "[\x1b[31mGGL ERROR\x1b[0m] (%s:%d:%s) ", \
            __FILE__, __LINE__, __func__); \
            fprintf(stderr, __VA_ARGS__); \
            fprintf(stderr, "\n")
    #endif /* ifndef GGL_PERROR */

    #ifndef GGL_DEBUG
        #define GGL_DEBUG(...) \
            do { \
                if (GGL_DEBUG_MODE) { \
                    fprintf(stderr, "[\x1b[34mGGL DEBUG\x1b[0m] (%s:%d:%s) ", \
                        __FILE__, __LINE__, __func__); \
                    fprintf(stderr, __VA_ARGS__); \
                    fprintf(stderr, "\n"); \
                } \
            } while(0)
    #endif /* ifndef GGL_DEBUG */

    #define GGL_DEG_TO_RAD(deg) ((deg) * M_PI / 180.0f)
    #define GGL_RAD_TO_DEG(rad) ((rad) * 180.0f / M_PI)

    #ifndef M_PI
        #define M_PI 3.14159265358979323846f
    #endif /* ifndef M_PI */

#endif /* ifndef _GGL_MACROS_H_ */
