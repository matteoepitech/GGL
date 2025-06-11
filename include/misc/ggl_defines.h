/*
** GGL PROJECT, 2025
** include/misc/ggl_defines.h
** File description:
** GGL header file for defines
*/

#ifndef _GGL_DEFINES_H_
    #define _GGL_DEFINES_H_
    
    // @brief GGL_DEBUG_MODE can be used to print a lot of debug infos.
    #ifndef GGL_DEBUG_MODE
        #define GGL_DEBUG_MODE 1
    #endif /* ifndef GGL_DEBUG_MODE */

    #ifndef GGL_OK
        #define GGL_OK 0
    #endif /* ifndef GGL_OK */
    
    #ifndef GGL_KO
        #define GGL_KO 1
    #endif /* ifndef GGL_KO */
    
    #ifndef GGL_TRUE
        #define GGL_TRUE 1
    #endif /* ifndef GGL_TRUE */
    
    #ifndef GGL_FALSE
        #define GGL_FALSE 0
    #endif /* ifndef GGL_FALSE */
    
    #ifndef M_PI
        #define M_PI 3.14159265358979323846f
    #endif /* ifndef M_PI */

    #ifndef GGL_COLORS 
        #define GGL_COLOR_RED (ggl_color) {255, 0, 0, 255}
        #define GGL_COLOR_GREEN (ggl_color) {0, 255, 0, 255}
        #define GGL_COLOR_BLUE (ggl_color) {0, 0, 255, 255}
        #define GGL_COLOR_WHITE (ggl_color) {255, 255, 255, 255}
        #define GGL_COLOR_BLACK (ggl_color) {0, 0, 0, 255}
    #endif /* ifndef GGL_COLORS */

#endif /* ifndef _GGL_DEFINES_H_ */
