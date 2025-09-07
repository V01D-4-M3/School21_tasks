#include "./brick_game/tetris/tetris.h"
#include "./gui/cli/cli.h"

#define INITIAL_GAME_SELECTION 0
#define TETRIS_GAME_INDEX 0
#define EXIT_GAME_SELECTION -1

void initialize_game_screen();
void cleanup_game_screen();
int handle_game_selection();
void wait_for_game_start();
int process_game_selection_input(int current_selection,
                                 UserAction_t user_action);
void run_main_game_loop(GameInfo_t *game_info);
void run_tetris_game();
int handle_game_over_state(GameInfo_t *game_info);

int main() {
  initialize_game_screen();
  int selected_game = handle_game_selection();

  if (selected_game == TETRIS_GAME_INDEX) {
    clear_select_game_screen();
    print_overlay();
    wait_for_game_start();
    run_tetris_game();
  }

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

int handle_game_selection() {
  int current_selection = INITIAL_GAME_SELECTION;

  while (1) {
    select_game(current_selection);
    UserAction_t user_action = get_signal(getch());

    int selection_result =
        process_game_selection_input(current_selection, user_action);
    if (selection_result != current_selection || user_action == Action) {
      if (user_action == Action) {
        return current_selection; // Запускаем выбранную игру
      }
      return selection_result; // Выход или другой выбор
    }

    current_selection = selection_result;
  }
}

int process_game_selection_input(int current_selection,
                                 UserAction_t user_action) {

  if (user_action == Terminate) {
    return EXIT_GAME_SELECTION;
  }

  if (user_action == Action) {
    return current_selection;
  }

  return current_selection;
}

void wait_for_game_start() {
  while (1) {
    UserAction_t user_action = get_signal(getch());
    if (user_action == Action) {
      break;
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
  }
}

int handle_game_over_state(GameInfo_t *game_info) {
  tetris_state *state_ptr = get_state(NULL);
  int game_state = (state_ptr) ? *state_ptr : GAMEOVER;

  if (game_state == GAMEOVER) {
    print_banner(game_info);
    while (1) {
      UserAction_t user_action = get_signal(getch());
      if (user_action == Terminate) {
        return 1;
      }
    }
  }

  return 0;
}
