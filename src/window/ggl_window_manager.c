/*
** EPITECH PROJECT, 2025
** src/core/ggl_window_manager
** File description:
** GGL window manager
*/

#include "ggl.h"

/**
 * @brief Set the size of the viewport of OpenGL.
 *
 * @param window        The window
 * @param width         The width
 * @param height        The height
 */
static void
ggl_set_viewport_size(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

/**
 * @brief Create a GGL window.
 *
 * @param title         The title of the window
 * @param size          The size of the window
 *
 * @return GGL_OK if everything worked. GGL_KO if not.
 */
ggl_status
ggl_create_window(const char *title, ggl_vector2i_t size)
{
    GLFWwindow* window = NULL;
    ggl_context_t *ctx = ggl_get_context();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(size._width, size._height, title, NULL, NULL);
    if (window == NULL) {
        GGL_PERROR("Cannot create the window.");
        return GGL_KO;
    }
    ctx->_ggl_window._win_glfw = window;
    GGL_DEBUG("Window created with name '%s'.", title);
    glfwMakeContextCurrent(window);
    ggl_set_viewport_size(window, size._width, size._height);
    glfwSetFramebufferSizeCallback(window, ggl_set_viewport_size);  
    return GGL_OK;
}

/**
 * @brief Is the window need to be closed ?
 *        It does the swap buffers and poll events as well.
 *
 * @param ctx           The context of the program
 *
 * @return GGL_TRUE if yes GGL_FALSE if no.
 */
ggl_bool
ggl_window_should_close(ggl_context_t *ctx)
{
    if (ctx == NULL)
        ctx = ggl_get_context();
    if (ctx == NULL || ctx->_ggl_window._win_glfw == NULL)
        return GGL_TRUE;
    if (glfwWindowShouldClose(ctx->_ggl_window._win_glfw) == GLFW_TRUE)
        return GGL_TRUE;
    glfwSwapBuffers(ctx->_ggl_window._win_glfw);
    glfwPollEvents();
    return GGL_FALSE;
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

/**
 * @brief Clear the window and put this background color.
 *
 * @param background_color      The background color
 *
 * @return GGL_OK if worked. GGL_KO if not.
 */
ggl_status
ggl_clear_window(ggl_color_t background_color)
{
    glClearColor(background_color._r / 255.0f,
        background_color._g / 255.0f,
        background_color._b / 255.0f,
        background_color._a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(success == GGL_KO)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(success == GGL_KO)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if(success == GGL_KO)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    glUseProgram(shaderProgram);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    return GGL_OK;
}
