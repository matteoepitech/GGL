/*
** GGL PROJECT, 2025
** include/misc/ggl_macros.h
** File description:
** GGL header file for macros
*/

#ifndef _GGL_MACROS_H_
    #define _GGL_MACROS_H_

    #include "misc/ggl_defines.h"

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

#endif /* ifndef _GGL_MACROS_H_ */
