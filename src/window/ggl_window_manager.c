/*
** EPITECH PROJECT, 2025
** src/core/ggl_window_manager
** File description:
** GGL window manager
*/

#include "ggl.h"

// @TEMPORARY stuff for checking the FPS
#define MAX_SAMPLES 100
double fps_samples[MAX_SAMPLES] = {0};
int fps_index = 0;
static void ggl_smooth_fps(ggl_context *ctx, double new_fps) {
    fps_samples[fps_index] = new_fps;
    fps_index = (fps_index + 1) % MAX_SAMPLES;

    double sum = 0;
    for (int i = 0; i < MAX_SAMPLES; i++)
        sum += fps_samples[i];
    ctx->_current_fps = sum / MAX_SAMPLES;
}
// @TEMPORARY stuff for checking the FPS

/**
 * @brief Set the size of the viewport of OpenGL.
 *        This is an OpenGL default callback.
 *
 * @param window        The window
 * @param width         The width
 * @param height        The height
 */
static void
ggl_set_viewport_size(GLFWwindow *win,
                      int width,
                      int height)
{
    glViewport(0, 0, width, height);
}  

/**
 * @brief Create a GGL window.
 *
 * @param ctx           The context
 * @param title         The title of the window
 * @param size          The size of the window
 *
 * @return GGL_OK if everything worked. GGL_KO if not.
 */
ggl_status
ggl_window_create(ggl_context *ctx,
                  const char *title,
                  ggl_vector2i size)
{
    GLFWwindow* window = NULL;
    int framebuffer_width = 0;
    int framebuffer_height = 0;

    if (ctx == NULL)
        return GGL_KO;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    window = glfwCreateWindow(size._x, size._y, title, NULL, NULL);
    if (window == NULL) {
        GGL_PERROR("Cannot create the window.");
        return GGL_KO;
    }
    ctx->_ggl_window._win_glfw = window;
    ctx->_ggl_window._ref_width = size._x;
    ctx->_ggl_window._ref_height = size._y;
    GGL_DEBUG("Window created with name '%s'.", title);
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
    ctx->_ggl_window._fb_ref_height = framebuffer_height;
    ctx->_ggl_window._fb_ref_width = framebuffer_width;
    ggl_set_viewport_size(window, framebuffer_width, framebuffer_height);
    glfwSetFramebufferSizeCallback(window, ggl_set_viewport_size);
    return GGL_OK;
}

/**
 * @brief Is the window need to be closed ?
 *        It does the swap buffers and poll events as well, and FPS.
 *
 * @param ctx           The context of the program
 *
 * @return GGL_TRUE if yes GGL_FALSE if no.
 */
ggl_bool ggl_window_should_close(ggl_context *ctx)
{
    static double prev_time = 0.0;
    double current_time;
    double delta_time;

    if (ctx == NULL || ctx->_ggl_window._win_glfw == NULL)
        return GGL_TRUE;
    if (glfwWindowShouldClose(ctx->_ggl_window._win_glfw) == GLFW_TRUE)
        return GGL_TRUE;
    current_time = glfwGetTime();
    if (prev_time != 0.0) {
        delta_time = current_time - prev_time;
        ggl_smooth_fps(ctx, 1.0 / delta_time);
    }
    prev_time = current_time;
    glfwGetFramebufferSize(ctx->_ggl_window._win_glfw,
        &ctx->_ggl_window._fb_width, &ctx->_ggl_window._fb_height);
    glfwSwapBuffers(ctx->_ggl_window._win_glfw);
    glfwPollEvents();
    return GGL_FALSE;
}

/**
 * @brief Clear the window and put this background color.
 *
 * @param background_color      The background color
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_window_clear(ggl_color background_color)
{
    glClearColor(background_color._r / 255.0f,
        background_color._g / 255.0f,
        background_color._b / 255.0f,
        background_color._a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return GGL_OK;
}
