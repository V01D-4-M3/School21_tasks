#include "cli.h"

#define GAME_TITLE_Y 4
#define GAME_TITLE_X 7
#define START_OPTION_Y 6
#define START_OPTION_X 4

UserAction_t get_signal(int user_input) {
  UserAction_t action = -1;

  if (user_input == KEY_UP) {
    action = Up;
  } else if (user_input == KEY_DOWN) {
    action = Down;
  } else if (user_input == KEY_LEFT) {
    action = Left;
  } else if (user_input == KEY_RIGHT) {
    action = Right;
  } else if (user_input == ESCAPE) {
    action = Terminate;
  } else if (user_input == ENTER_KEY) {
    action = Action;
  } else if (user_input == KEY_BACKSPACE) {
    action = Pause;
  }

  return action;
}

void print_overlay(void) {
  print_rectangle(TOP_Y, BOT_Y, LEFT_X, RIGHT_X);
  print_rectangle(NEXT_TOP_Y, NEXT_BOT_Y, NEXT_LEFT_X, NEXT_RIGHT_X);

  mvprintw(0, 27, "NEXT");
  mvprintw(5, 27, "LEVEL");
  mvprintw(8, 27, "SPEED");
  mvprintw(11, 27, "SCORE");
  mvprintw(14, 25, "HIGH SCORE");

  mvprintw(17, 24, "ESC - exit");
  mvprintw(18, 24, "BACKSPACE - pause");
  mvprintw(19, 24, "arrows - move");
  mvprintw(20, 24, "ENTER - rotate");

  mvprintw(10, 1, "Press ENTER to START");
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  print_vertical_borders(top_y, bottom_y, left_x, right_x);
  print_horizontal_dots(top_y, bottom_y, left_x, right_x);
  print_bottom_border(bottom_y, left_x, right_x);
}

void print_vertical_borders(int top_y, int bottom_y, int left_x, int right_x) {
  for (int y = top_y; y < bottom_y + 1; y++) {
    mvprintw(y, left_x, "|");
    mvprintw(y, right_x, "|");
  }
}

void print_horizontal_dots(int top_y, int bottom_y, int left_x, int right_x) {
  for (int y = top_y; y < bottom_y + 1; y++) {
    for (int x = left_x; x < right_x; x++) {
      if (x % 2 == 1) {
        mvaddch(y, x + 1, '.');
      }
    }
  }
}

void print_bottom_border(int bottom_y, int left_x, int right_x) {
  for (int x = left_x; x < right_x + 1; x++) {
    mvaddch(bottom_y, x, '=');
  }
}

void print_stats(GameInfo_t *stats) {
  mvprintw(6, 29, "%d", stats->level);
  mvprintw(9, 29, "%d", stats->speed);
  mvprintw(12, 27, "%d", stats->score);
  mvprintw(15, 26, "%d", stats->high_score);
}

void print_board(GameInfo_t *board) {
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      print_board_cell(x, y, board->field[x][y]);
    }
  }
}

void print_board_cell(int x, int y, int cell_value) {
  if (cell_value == 1) {
    mvaddch(y + TOP_Y, x * 2 + (LEFT_X + 1), '[');
    mvaddch(y + TOP_Y, x * 2 + 1 + (LEFT_X + 1), ']');
  } else {
    mvaddch(y + TOP_Y, x * 2 + (LEFT_X + 1), ' ');
    mvaddch(y + TOP_Y, x * 2 + 1 + (LEFT_X + 1), '.');
  }
}

void print_banner(GameInfo_t *stats) {
  mvprintw(6, 4, "            ");
  mvprintw(7, 4, "  GAMEOVER  ");
  mvprintw(8, 4, "            ");
  mvprintw(9, 4, "  Level: %d  ", stats->level);
  mvprintw(10, 4, "              ");
  mvprintw(11, 3, "  Score: %d  ", stats->score);
  mvprintw(12, 3, "                 ");
  mvprintw(13, 2, "  High Score: %d  ", stats->high_score);
  mvprintw(14, 2, "                      ");
  mvprintw(15, 1, "  Press ESC to Quit  ");
  mvprintw(16, 1, "                     ");
}

void print_next_section(GameInfo_t *stats) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      print_next_cell(i, j, stats->next[j][i]);
    }
  }
}

void print_next_cell(int i, int j, int cell_value) {
  if (cell_value == 1) {
    mvprintw(NEXT_TOP_Y + j, NEXT_LEFT_X + 1 + i * 2, "[]");
  } else {
    mvprintw(NEXT_TOP_Y + j, NEXT_LEFT_X + 1 + i * 2, " .");
  }
}

void print_pause(void) { mvprintw(10, 4, " GAME PAUSED "); }

void updateCurrentState(GameInfo_t *gameInfo) { // Принимаем параметр
  if (gameInfo == NULL)
    return;

  if (gameInfo->pause == 1) {
    print_pause();
  } else {
    print_board(gameInfo);
    print_next_section(gameInfo);
    print_stats(gameInfo);
  }
}

GameInfo_t *change_GameInfo_t(GameInfo_t *gameInfo) {
  static GameInfo_t *stored_info = NULL;

  if (gameInfo == NULL) {
    return stored_info;
  }

  stored_info = gameInfo;
  return stored_info;
}

void select_game(int selectedGame) {
  print_game_selection_title();
  print_start_option();
  highlight_start_option(selectedGame);
}

void print_game_selection_title() {
  mvprintw(GAME_TITLE_Y, GAME_TITLE_X, "TETRIS GAME");
}

void print_start_option() {
  mvprintw(START_OPTION_Y, START_OPTION_X, "   START GAME");
}

void highlight_start_option(int selectedGame) {
  if (selectedGame == 0) {
    mvprintw(START_OPTION_Y, START_OPTION_X, "[] START GAME");
  }
}

void clear_select_game_screen() {
  mvprintw(GAME_TITLE_Y, GAME_TITLE_X, "            ");
  mvprintw(START_OPTION_Y, START_OPTION_X, "             ");
}