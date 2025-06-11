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

    #ifndef GGL_DEG_TO_RAD
        #define GGL_DEG_TO_RAD(deg) ((deg) * M_PI / 180.0f)
    #endif /* ifndef GGL_DEG_TO_RAD */
    
    #ifndef GGL_RAD_TO_DEG
        #define GGL_RAD_TO_DEG(rad) ((rad) * 180.0f / M_PI)
    #endif /* ifndef GGL_RAD_TO_DEG */

    #ifndef GGL_WIN_WIDTH
        #define GGL_WIN_WIDTH(x) ggl_get_window_width(x)
    #endif /* ifndef GGL_WIN_WIDTH */
    
    #ifndef GGL_WIN_HEIGHT
        #define GGL_WIN_HEIGHT(x) ggl_get_window_height(x)
    #endif /* ifndef GGL_WIN_HEIGHT */

#endif /* ifndef _GGL_MACROS_H_ */
