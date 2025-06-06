/*
** GGL PROJECT, 2025
** include/modules/ggl_window.h
** File description:
** GGL Window module header file
*/

#ifndef _GGL_MODULE_WINDOW_H_
    #define _GGL_MODULE_WINDOW_H_
    
    #include <GLFW/glfw3.h>

/**
 * @brief GGL window structure containing all informations about windows.
 */
typedef struct ggl_window_s {
    GLFWwindow *_win_glfw;
} ggl_window_t;

#endif /* ifndef _GGL_MODULE_WINDOW_H_ */
