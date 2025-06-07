/*
** GGL PROJECT, 2025
** main
** File description:
** Hot reloading game to try GGL
*/

#include "../../include/misc/ggl_types.h"

#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// =====================================================

void *lib_ggl_ptr = NULL;

typedef ggl_context *(*ggl_init_t)(void);
typedef ggl_status (*ggl_create_window_t)(ggl_context *, const char *, ggl_vector2i);
typedef ggl_status (*ggl_setup_debug_close_t)(ggl_context *);
typedef ggl_status (*ggl_clear_window_t)(ggl_color);
typedef ggl_status (*ggl_terminate_t)(ggl_context *);
typedef ggl_bool (*ggl_window_should_close_t)(ggl_context *);
typedef ggl_bool (*ggl_is_key_down_t)(ggl_context *, ggl_key);
typedef ggl_triangle *(*ggl_triangle_create_t)(ggl_vector2f, ggl_vector2f, ggl_color);
typedef ggl_rectangle *(*ggl_rectangle_create_t)(ggl_vector2f, ggl_vector2f, ggl_color);
typedef ggl_status (*ggl_triangle_render_t)(ggl_context *, const ggl_triangle *);
typedef ggl_status (*ggl_rectangle_render_t)(ggl_context *, const ggl_rectangle *);

ggl_init_t ggl_init;
ggl_create_window_t ggl_create_window;
ggl_setup_debug_close_t ggl_setup_debug_close;
ggl_clear_window_t ggl_clear_window;
ggl_terminate_t ggl_terminate;
ggl_window_should_close_t ggl_window_should_close;
ggl_is_key_down_t ggl_is_key_down;
ggl_triangle_create_t ggl_triangle_create;
ggl_triangle_render_t ggl_triangle_render;
ggl_rectangle_create_t ggl_rectangle_create;
ggl_rectangle_render_t ggl_rectangle_render;

// =====================================================

static void load_ggl_symbols(void)
{
    ggl_init = dlsym(lib_ggl_ptr, "ggl_init");
    ggl_create_window = dlsym(lib_ggl_ptr, "ggl_create_window");
    ggl_setup_debug_close = dlsym(lib_ggl_ptr, "ggl_setup_debug_close");
    ggl_clear_window = dlsym(lib_ggl_ptr, "ggl_clear_window");
    ggl_terminate = dlsym(lib_ggl_ptr, "ggl_terminate");
    ggl_window_should_close = dlsym(lib_ggl_ptr, "ggl_window_should_close");
    ggl_is_key_down = dlsym(lib_ggl_ptr, "ggl_is_key_down");
    ggl_triangle_create = dlsym(lib_ggl_ptr, "ggl_triangle_create");
    ggl_triangle_render = dlsym(lib_ggl_ptr, "ggl_triangle_render");
    ggl_rectangle_create = dlsym(lib_ggl_ptr, "ggl_rectangle_create");
    ggl_rectangle_render = dlsym(lib_ggl_ptr, "ggl_rectangle_render");
}

static ggl_context *reload_ggl_and_reinit(
    ggl_context *old_ctx,
    ggl_rectangle **r1)
{
    if (lib_ggl_ptr) {
        if (ggl_terminate && old_ctx)
            ggl_terminate(old_ctx);
        dlclose(lib_ggl_ptr);
        lib_ggl_ptr = NULL;
    }

    lib_ggl_ptr = dlopen("./libggl.dylib", RTLD_NOW);
    if (!lib_ggl_ptr) {
        fprintf(stderr, "Failed to load libggl: %s\n", dlerror());
        exit(1);
    }

    load_ggl_symbols();

    ggl_context *ctx = ggl_init();
    ggl_create_window(ctx, "Valentino's Window", (ggl_vector2i){1280, 720});
    ggl_setup_debug_close(ctx);

    *r1 = ggl_rectangle_create((ggl_vector2f) {640.0f, 360.0f}, (ggl_vector2f) {100.0f, 100.0f}, (ggl_color) {50, 100, 155, 255});

    return ctx;
}

static void process_inputs(
    ggl_context **ctx,
    ggl_rectangle **r1)
{
    if (ggl_is_key_down(*ctx, GLFW_KEY_R)) {
        printf("[HR] Reloading GGL...\n");
        system("cd ../../ && ./build.sh");
        *ctx = reload_ggl_and_reinit(*ctx, r1);
        usleep(2000);
        printf("[HR] Reloaded GGL!\n");
    }
}

int main(void)
{
    ggl_color bg_c = {50, 50, 50, 255};
    ggl_color t_color = {10, 10, 255, 255};
    ggl_color t2_color = {10, 255, 10, 155};
    ggl_triangle *t1 = NULL;
    ggl_triangle *t2 = NULL;
    ggl_rectangle *r1 = NULL;

    ggl_context *ctx = reload_ggl_and_reinit(NULL, &r1);

    while (!ggl_window_should_close(ctx)) {
        process_inputs(&ctx, &r1);
        ggl_clear_window(bg_c);
        ggl_triangle_render(ctx, t2);
        ggl_triangle_render(ctx, t1);
        ggl_rectangle_render(ctx, r1);
    }

    ggl_terminate(ctx);
    return 0;
}
