#ifndef CLI_H_
#define CLI_H_

#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

UserAction_t get_signal(int user_input);
void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_vertical_borders(int top_y, int bottom_y, int left_x, int right_x);
void print_horizontal_dots(int top_y, int bottom_y, int left_x, int right_x);
void print_bottom_border(int bottom_y, int left_x, int right_x);
void print_stats(GameInfo_t *stats);
void print_board(GameInfo_t *board);
void print_board_cell(int x, int y, int cell_value);
void print_banner(GameInfo_t *stats);
void print_next_section(GameInfo_t *stats);
void print_next_cell(int i, int j, int cell_value);
void print_pause(void);
void updateCurrentState(GameInfo_t *gameInfo);
GameInfo_t *change_GameInfo_t(GameInfo_t *gameInfo);
void select_game(int selectedGame);
void print_game_selection_title();
void print_start_option();
void highlight_start_option(int selectedGame);
void clear_select_game_screen();

#endif // CLI_H_