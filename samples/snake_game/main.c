/*
** GGL PROJECT, 2025
** main
** File description:
** Snake Game using GGL
*/

#include "../../include/ggl.h"
#include "modules/ggl_core.h"
#include "modules/ggl_input.h"
#include "modules/ggl_math.h"
#include "modules/ggl_renderer.h"
#include "modules/ggl_window.h"

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define RECT_SIZE 30
#define RECT_COL 43
#define RECT_ROW 24
#define RECT_AMOUNT (RECT_ROW * RECT_COL)
#define MAX_TRAIL 100

typedef struct {
    int x;
    int y;
} trail_point;

typedef struct {
    int x;
    int y;
    bool active;
} food_point;

static trail_point trail[MAX_TRAIL];
static int trail_length = 1;
static int current_trail_length = 1;
static food_point food = {0, 0, false};
static int score = 0;
static bool game_over = false;

static void spawn_food(void)
{
    bool valid_position = false;
    
    while (!valid_position) {
        food.x = rand() % RECT_COL;
        food.y = rand() % RECT_ROW;
        valid_position = true;
        for (int i = 0; i < current_trail_length; i++) {
            if (trail[i].x == food.x && trail[i].y == food.y) {
                valid_position = false;
                break;
            }
        }
    } 
    food.active = true;
}

static void init_rectangles(ggl_rectangle *rects[RECT_AMOUNT])
{
    ggl_vector2f pos = {0, 0};
    for (int y = 0; y < RECT_ROW; y++) {
        for (int x = 0; x < RECT_COL; x++) {
            int i = y * RECT_COL + x;
            int is_even = (i % 2 == 0);
            rects[i] = ggl_rectangle_create(
                pos,
                (ggl_vector2f){RECT_SIZE, RECT_SIZE},
                is_even ? (ggl_color){90, 130, 126, 255} : (ggl_color){132, 174, 146, 255}
            );
            pos._x += RECT_SIZE;
        }
        pos._x = 0;
        pos._y += RECT_SIZE;
    }
    trail[0].x = RECT_COL / 2;
    trail[0].y = RECT_ROW / 2;
    spawn_food();
}

static bool check_self_collision(ggl_vector2i new_pos)
{
    for (int i = 1; i < current_trail_length; i++) {
        if (trail[i].x == new_pos._x && trail[i].y == new_pos._y) {
            return true;
        }
    }
    return false;
}

static void update_player_position(ggl_context *ctx, ggl_vector2i *pos)
{
    ggl_vector2i old_pos = *pos;
    ggl_vector2i new_pos = *pos;
    
    if (ggl_is_key_down(ctx, GLFW_KEY_W))
        new_pos._y--;
    if (ggl_is_key_down(ctx, GLFW_KEY_S))
        new_pos._y++;
    if (ggl_is_key_down(ctx, GLFW_KEY_D))
        new_pos._x++;
    if (ggl_is_key_down(ctx, GLFW_KEY_A))
        new_pos._x--;
    if (new_pos._x < 0)
        new_pos._x = 0;
    if (new_pos._x >= RECT_COL)
        new_pos._x = RECT_COL - 1;
    if (new_pos._y < 0)
        new_pos._y = 0;
    if (new_pos._y >= RECT_ROW)
        new_pos._y = RECT_ROW - 1;
    if (old_pos._x != new_pos._x || old_pos._y != new_pos._y) {
        if (check_self_collision(new_pos)) {
            game_over = true;
            return;
        }
        *pos = new_pos;
        if (food.active && pos->_x == food.x && pos->_y == food.y) {
            score++;
            trail_length++;
            food.active = false;
            spawn_food();
        }
        for (int i = current_trail_length - 1; i > 0; i--) {
            trail[i] = trail[i - 1];
        }
        trail[0].x = pos->_x;
        trail[0].y = pos->_y;
        if (current_trail_length < trail_length) {
            current_trail_length++;
        }
    }
}

static ggl_color get_trail_color(int position, int total_length)
{
    float ratio = (float)position / (float)(total_length - 1);
    unsigned char red = 255;
    unsigned char green = (unsigned char)(165 * ratio);
    unsigned char blue = 0;
    unsigned char alpha = (unsigned char)(255 - (50 * ratio));
    
    if (position == 0) {
        return (ggl_color) {255, 0, 0, 255};
    }
    return (ggl_color){red, green, blue, alpha};
}

static void render_grid(ggl_context *ctx, ggl_rectangle *rects[RECT_AMOUNT])
{
    for (int i = 0; i < RECT_AMOUNT; i++) {
        int x = i % RECT_COL;
        int y = i / RECT_COL;
        bool is_trail = false;
        bool is_food = false;
        int trail_position = -1;

        if (food.active && food.x == x && food.y == y) {
            is_food = true;
        }
        for (int j = 0; j < current_trail_length; j++) {
            if (trail[j].x == x && trail[j].y == y) {
                is_trail = true;
                trail_position = j;
                break;
            }
        }
        if (is_food) {
            ggl_rectangle_set_color(rects[i], (ggl_color){0, 0, 255, 255});
        } else if (is_trail) {
            ggl_rectangle_set_color(rects[i], get_trail_color(trail_position, current_trail_length));
        } else {
            int is_even = (i % 2 == 0);
            ggl_rectangle_set_color(rects[i],
                is_even ? (ggl_color){90, 130, 126, 255} : (ggl_color){132, 174, 146, 255});
        }
        ggl_rectangle_render(ctx, rects[i]);
    }
}

int main(void)
{
    ggl_context *ctx = ggl_init();
    ggl_rectangle *rectangles[RECT_AMOUNT];
    ggl_vector2i trail_pos = {RECT_COL / 2, RECT_ROW / 2};
    
    srand(time(NULL));
    if (!ctx || ggl_create_window(ctx, "Snake Game", (ggl_vector2i){1280, 720}) == GGL_KO)
        return 1;
    ggl_setup_debug_close(ctx);
    init_rectangles(rectangles);
    while (!ggl_window_should_close(ctx) && !game_over) {
        ggl_clear_window((ggl_color){0, 0, 0, 255});
        update_player_position(ctx, &trail_pos);
        render_grid(ctx, rectangles);
        printf("FPS : %d | Score: %d | Length: %d\n", (int) ctx->_current_fps, score, current_trail_length);
        usleep(32000);
    }
    if (game_over) {
        printf("\n=== GAME OVER ===\n");
        printf("Final Score: %d\n", score);
        printf("Snake Length: %d\n", current_trail_length);
        printf("=================\n");
    }
    ggl_terminate(ctx);
    return 0;
}
