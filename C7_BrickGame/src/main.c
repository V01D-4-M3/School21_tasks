#include "./brick_game/tetris/tetris.h"
#include "./gui/cli/cli.h"

#define TETRIS_GAME_INDEX 0

void initialize_game_screen();
void cleanup_game_screen();
void show_start_screen();
void wait_for_game_start();
void run_main_game_loop(GameInfo_t *game_info);
void run_tetris_game();
int handle_game_over_state(GameInfo_t *game_info);

int main() {
  initialize_game_screen();
  show_start_screen();
  wait_for_game_start();

  print_overlay();
  run_tetris_game();

  cleanup_game_screen();
  return 0;
}

void initialize_game_screen() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(40);
  srand((unsigned int)time(NULL));
}

void cleanup_game_screen() { endwin(); }

void show_start_screen() {
  print_start_screen();
  refresh();
}

void wait_for_game_start() {
  while (1) {
    UserAction_t user_action = get_signal(getch());
    if (user_action == Action) {
      clear_start_screen();
      break;
    } else if (user_action == Terminate) {
      cleanup_game_screen();
      exit(0);
    }
  }
}

void run_tetris_game() {
  GameInfo_t game_info;
  infoInit(&game_info);
  change_GameInfo_t(&game_info);

  run_main_game_loop(&game_info);
  handle_game_over_state(&game_info);

  infoFree(&game_info);
}

void run_main_game_loop(GameInfo_t *game_info) {
  UserAction_t user_action = -1;
  game_loop(game_info, user_action);

  int game_state = -1;
  while (game_state != EXIT_STATE && game_state != GAMEOVER) {
    if (game_state == START || game_state == MOVING || game_state == PAUSE) {
      user_action = get_signal(getch());
    }

    game_state = game_loop(game_info, user_action);
    updateCurrentState(game_info);
    refresh();
  }
}

int handle_game_over_state(GameInfo_t *game_info) {
  tetris_state *state_ptr = get_state(NULL);
  int game_state = (state_ptr) ? *state_ptr : GAMEOVER;

  if (game_state == GAMEOVER) {
    print_banner(game_info);
    refresh();
    while (1) {
      UserAction_t user_action = get_signal(getch());
      if (user_action == Terminate) {
        return 1;
      }
    }
  }

  return 0;
}