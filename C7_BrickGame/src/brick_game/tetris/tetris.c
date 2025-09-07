#include "tetris.h"


static GameInfo_t *stored_game_info = NULL;
static tetris_state *stored_state = NULL;
static Tetramino *stored_current = NULL;
static block *stored_next_block = NULL;
static bool *stored_fall_time = NULL;

static void initialize_tetramino_coordinates(Tetramino *current, int x1, int y1,
                                             int x2, int y2, int x3, int y3,
                                             int x4, int y4, block type);
static void initialize_next_block_display(GameInfo_t *board, int row1_col0,
                                          int row1_col1, int row1_col2,
                                          int row1_col3, int row2_col0,
                                          int row2_col1, int row2_col2,
                                          int row2_col3);
static void update_game_speed(clock_t *last_move_time, GameInfo_t *game_info);
static int calculate_game_speed(int level);

void clear_backpos(Tetramino *current, GameInfo_t *gameInfo) {
  gameInfo->field[current->x1][current->y1] = 0;
  gameInfo->field[current->x2][current->y2] = 0;
  gameInfo->field[current->x3][current->y3] = 0;
  gameInfo->field[current->x4][current->y4] = 0;
}

int movedown(Tetramino *current, GameInfo_t *gameInfo) {
  clear_backpos(current, gameInfo);

  if (current->y1 >= FIELD_HEIGHT - 1 || current->y2 >= FIELD_HEIGHT - 1 ||
      current->y3 >= FIELD_HEIGHT - 1 || current->y4 >= FIELD_HEIGHT - 1) {
    return 1;
  }

  if (gameInfo->field[current->x1][current->y1 + 1] != 0 ||
      gameInfo->field[current->x2][current->y2 + 1] != 0 ||
      gameInfo->field[current->x3][current->y3 + 1] != 0 ||
      gameInfo->field[current->x4][current->y4 + 1] != 0) {
    return 1;
  }

  current->y1 += 1;
  current->y2 += 1;
  current->y3 += 1;
  current->y4 += 1;

  return 0;
}

void moveright(Tetramino *current, GameInfo_t *gameInfo) {
  clear_backpos(current, gameInfo);

  if (current->x1 >= FIELD_WIDTH - 1 || current->x2 >= FIELD_WIDTH - 1 ||
      current->x3 >= FIELD_WIDTH - 1 || current->x4 >= FIELD_WIDTH - 1) {
    return;
  }

  if (gameInfo->field[current->x1 + 1][current->y1] != 0 ||
      gameInfo->field[current->x2 + 1][current->y2] != 0 ||
      gameInfo->field[current->x3 + 1][current->y3] != 0 ||
      gameInfo->field[current->x4 + 1][current->y4] != 0) {
    return;
  }

  current->x1 += 1;
  current->x2 += 1;
  current->x3 += 1;
  current->x4 += 1;
}

void moveleft(Tetramino *current, GameInfo_t *gameInfo) {
  clear_backpos(current, gameInfo);

  if (current->x1 <= 0 || current->x2 <= 0 || current->x3 <= 0 ||
      current->x4 <= 0) {
    return;
  }

  if (gameInfo->field[current->x1 - 1][current->y1] != 0 ||
      gameInfo->field[current->x2 - 1][current->y2] != 0 ||
      gameInfo->field[current->x3 - 1][current->y3] != 0 ||
      gameInfo->field[current->x4 - 1][current->y4] != 0) {
    return;
  }

  current->x1 -= 1;
  current->x2 -= 1;
  current->x3 -= 1;
  current->x4 -= 1;
}

void rotate_I(Tetramino *current, GameInfo_t *gameInfo) {
  clear_backpos(current, gameInfo);

  if (current->rotate_state == 0) {
    if (current->y1 > 1 && current->y2 > 1 && current->y3 > 1 &&
        current->y4 > 1 && current->y1 < FIELD_HEIGHT - 1 &&
        current->y2 < FIELD_HEIGHT - 1 && current->y3 < FIELD_HEIGHT - 1 &&
        current->y4 < FIELD_HEIGHT - 1) {
      if (gameInfo->field[current->x1 + 2][current->y1 - 2] == 0 &&
          gameInfo->field[current->x2 + 1][current->y2 - 1] == 0 &&
          gameInfo->field[current->x3][current->y3] == 0 &&
          gameInfo->field[current->x4 - 1][current->y4 + 1] == 0) {
        current->x1 += 2;
        current->y1 -= 2;
        current->x2 += 1;
        current->y2 -= 1;
        current->x4 -= 1;
        current->y4 += 1;
        current->rotate_state = 1;
      }
    }
  } else {
    if (current->x1 > 1 && current->x2 > 1 && current->x3 > 1 &&
        current->x4 > 1 && current->x1 < FIELD_WIDTH - 1 &&
        current->x2 < FIELD_WIDTH - 1 && current->x3 < FIELD_WIDTH - 1 &&
        current->x4 < FIELD_WIDTH - 1) {
      if (gameInfo->field[current->x1 - 2][current->y1 + 2] == 0 &&
          gameInfo->field[current->x2 - 1][current->y2 + 1] == 0 &&
          gameInfo->field[current->x3][current->y3] == 0 &&
          gameInfo->field[current->x4 + 1][current->y4 - 1] == 0) {
        current->x1 -= 2;
        current->y1 += 2;
        current->x2 -= 1;
        current->y2 += 1;
        current->x4 += 1;
        current->y4 -= 1;
        current->rotate_state = 0;
      }
    }
  }
}

int rotate_J_first(Tetramino *current, GameInfo_t *gameInfo) {
  int is_changed = 0;
  clear_backpos(current, gameInfo);

  if (current->rotate_state == 0) {
    if (current->y2 < FIELD_HEIGHT - 1) {
      if (gameInfo->field[current->x1 + 2][current->y1] == 0 &&
          gameInfo->field[current->x2 + 1][current->y2 - 1] == 0 &&
          gameInfo->field[current->x4 - 1][current->y4 + 1] == 0) {
        current->x1 += 2;
        current->x2 += 1;
        current->y2 -= 1;
        current->x4 -= 1;
        current->y4 += 1;
        current->rotate_state = 1;
      }
    }
  } else if (current->rotate_state == 1) {
    if (current->x2 > 0) {
      if (gameInfo->field[current->x1][current->y1 + 2] == 0 &&
          gameInfo->field[current->x2 + 1][current->y2 + 1] == 0 &&
          gameInfo->field[current->x4 - 1][current->y4 - 1] == 0) {
        current->y1 += 2;
        current->x2 += 1;
        current->y2 += 1;
        current->x4 -= 1;
        current->y4 -= 1;
        current->rotate_state = 2;
        is_changed = 1;
      }
    }
  }

  return is_changed;
}

void rotate_J_second(Tetramino *current, GameInfo_t *gameInfo) {
  if (current->rotate_state == 2) {
    if (current->y2 > 0) {
      if (gameInfo->field[current->x1 - 2][current->y1] == 0 &&
          gameInfo->field[current->x2 - 1][current->y2 + 1] == 0 &&
          gameInfo->field[current->x4 + 1][current->y4 - 1] == 0) {
        current->x1 -= 2;
        current->x2 -= 1;
        current->y2 += 1;
        current->x4 += 1;
        current->y4 -= 1;
        current->rotate_state = 3;
      }
    }
  } else if (current->rotate_state == 3) {
    if (current->x2 < FIELD_WIDTH - 1) {
      if (gameInfo->field[current->x1][current->y1 - 2] == 0 &&
          gameInfo->field[current->x2 - 1][current->y2 - 1] == 0 &&
          gameInfo->field[current->x4 + 1][current->y4 + 1] == 0) {
        current->y1 -= 2;
        current->x2 -= 1;
        current->y2 -= 1;
        current->x4 += 1;
        current->y4 += 1;
        current->rotate_state = 0;
      }
    }
  }
}

void rotate_J(Tetramino *current, GameInfo_t *gameInfo) {
  if (!rotate_J_first(current, gameInfo)) {
    rotate_J_second(current, gameInfo);
  }
}

int rotate_L_first(Tetramino *current, GameInfo_t *gameInfo) {
  int is_changed = 0;
  clear_backpos(current, gameInfo);

  if (current->rotate_state == 0) {
    if (current->y2 < FIELD_HEIGHT - 1) {
      if (gameInfo->field[current->x1 + 1][current->y1 - 1] == 0 &&
          gameInfo->field[current->x3 - 1][current->y3 + 1] == 0 &&
          gameInfo->field[current->x4][current->y4 + 2] == 0) {
        current->x1 += 1;
        current->y1 -= 1;
        current->x3 -= 1;
        current->y3 += 1;
        current->y4 += 2;
        current->rotate_state = 1;
      }
    }
  } else if (current->rotate_state == 1) {
    if (current->x2 > 0) {
      if (gameInfo->field[current->x1 + 1][current->y1 + 1] == 0 &&
          gameInfo->field[current->x3 - 1][current->y3 - 1] == 0 &&
          gameInfo->field[current->x4 - 2][current->y4] == 0) {
        current->x1 += 1;
        current->y1 += 1;
        current->x3 -= 1;
        current->y3 -= 1;
        current->x4 -= 2;
        current->rotate_state = 2;
        is_changed = 1;
      }
    }
  }

  return is_changed;
}

void rotate_L_second(Tetramino *current, GameInfo_t *gameInfo) {
  if (current->rotate_state == 2) {
    if (current->y2 > 0) {
      if (gameInfo->field[current->x1 - 1][current->y1 + 1] == 0 &&
          gameInfo->field[current->x3 + 1][current->y3 - 1] == 0 &&
          gameInfo->field[current->x4][current->y4 - 2] == 0) {
        current->x1 -= 1;
        current->y2 += 1;
        current->x3 += 1;
        current->y3 -= 1;
        current->y4 -= 2;
        current->rotate_state = 3;
      }
    }
  } else if (current->rotate_state == 3) {
    if (current->x2 < FIELD_WIDTH - 1) {
      if (gameInfo->field[current->x1 - 1][current->y1 - 1] == 0 &&
          gameInfo->field[current->x3 + 1][current->y3 + 1] == 0 &&
          gameInfo->field[current->x4 + 2][current->y4] == 0) {
        current->x1 -= 1;
        current->y2 -= 1;
        current->x3 += 1;
        current->y3 += 1;
        current->x4 += 2;
        current->rotate_state = 0;
      }
    }
  }
}

void rotate_L(Tetramino *current, GameInfo_t *gameInfo) {
  if (!rotate_L_first(current, gameInfo)) {
    rotate_L_second(current, gameInfo);
  }
}

void rotate_S(Tetramino *current, GameInfo_t *gameInfo) {
  clear_backpos(current, gameInfo);

  if (current->rotate_state == 0) {
    if (current->y1 > 0) {
      if (gameInfo->field[current->x1 + 1][current->y1] == 0 &&
          gameInfo->field[current->x2][current->y2 + 1] == 0 &&
          gameInfo->field[current->x3 + 1][current->y3 - 2] == 0 &&
          gameInfo->field[current->x4][current->y4 - 1] == 0) {
        current->x1 += 1;
        current->y2 += 1;
        current->x3 += 1;
        current->y3 -= 2;
        current->y4 -= 1;
        current->rotate_state = 1;
      }
    }
  } else if (current->rotate_state == 1) {
    if (current->x3 > 0) {
      if (gameInfo->field[current->x1 - 1][current->y1] == 0 &&
          gameInfo->field[current->x2][current->y2 - 1] == 0 &&
          gameInfo->field[current->x3 - 1][current->y3 + 2] == 0 &&
          gameInfo->field[current->x4][current->y4 + 1] == 0) {
        current->x1 -= 1;
        current->y2 -= 1;
        current->x3 -= 1;
        current->y3 += 2;
        current->y4 += 1;
        current->rotate_state = 0;
      }
    }
  }
}

int rotate_T_first(Tetramino *current, GameInfo_t *gameInfo) {
  int is_changed = 0;
  clear_backpos(current, gameInfo);

  if (current->rotate_state == 0) {
    if (current->y2 < FIELD_HEIGHT - 1) {
      if (gameInfo->field[current->x1 + 1][current->y1 + 1] == 0 &&
          gameInfo->field[current->x2 + 1][current->y2 - 1] == 0 &&
          gameInfo->field[current->x4 - 1][current->y4 + 1] == 0) {
        current->x1 += 1;
        current->y1 += 1;
        current->x2 += 1;
        current->y2 -= 1;
        current->x4 -= 1;
        current->y4 += 1;
        current->rotate_state = 1;
      }
    }
  } else if (current->rotate_state == 1) {
    if (current->x2 > 0) {
      if (gameInfo->field[current->x1 - 1][current->y1 + 1] == 0 &&
          gameInfo->field[current->x2 + 1][current->y2 + 1] == 0 &&
          gameInfo->field[current->x4 - 1][current->y4 - 1] == 0) {
        current->x1 -= 1;
        current->y1 += 1;
        current->x2 += 1;
        current->y2 += 1;
        current->x4 -= 1;
        current->y4 -= 1;
        current->rotate_state = 2;
        is_changed = 1;
      }
    }
  }

  return is_changed;
}

void rotate_T_second(Tetramino *current, GameInfo_t *gameInfo) {
  if (current->rotate_state == 2) {
    if (current->y2 > 0) {
      if (gameInfo->field[current->x1 - 1][current->y1 - 1] == 0 &&
          gameInfo->field[current->x2 - 1][current->y2 + 1] == 0 &&
          gameInfo->field[current->x4 + 1][current->y4 - 1] == 0) {
        current->x1 -= 1;
        current->y1 -= 1;
        current->x2 -= 1;
        current->y2 += 1;
        current->x4 += 1;
        current->y4 -= 1;
        current->rotate_state = 3;
      }
    }
  } else if (current->rotate_state == 3) {
    if (current->x2 < FIELD_WIDTH - 1) {
      if (gameInfo->field[current->x1 + 1][current->y1 - 1] == 0 &&
          gameInfo->field[current->x2 - 1][current->y2 - 1] == 0 &&
          gameInfo->field[current->x4 + 1][current->y4 + 1] == 0) {
        current->x1 += 1;
        current->y1 -= 1;
        current->x2 -= 1;
        current->y2 -= 1;
        current->x4 += 1;
        current->y4 += 1;
        current->rotate_state = 0;
      }
    }
  }
}

void rotate_T(Tetramino *current, GameInfo_t *gameInfo) {
  if (!rotate_T_first(current, gameInfo)) {
    rotate_T_second(current, gameInfo);
  }
}

void rotate_Z(Tetramino *current, GameInfo_t *gameInfo) {
  clear_backpos(current, gameInfo);

  if (current->rotate_state == 0) {
    if (current->y1 > 0) {
      if (gameInfo->field[current->x1 + 2][current->y1 - 1] == 0 &&
          gameInfo->field[current->x2 + 1][current->y2] == 0 &&
          gameInfo->field[current->x3][current->y3 - 1] == 0 &&
          gameInfo->field[current->x4 - 1][current->y4] == 0) {
        current->x1 += 2;
        current->y1 -= 1;
        current->x2 += 1;
        current->y3 -= 1;
        current->x4 -= 1;
        current->rotate_state = 1;
      }
    }
  } else if (current->rotate_state == 1) {
    if (current->x3 > 0) {
      if (gameInfo->field[current->x1 - 2][current->y1 + 1] == 0 &&
          gameInfo->field[current->x2 - 1][current->y2] == 0 &&
          gameInfo->field[current->x3][current->y3 + 1] == 0 &&
          gameInfo->field[current->x4 + 1][current->y4] == 0) {
        current->x1 -= 2;
        current->y1 += 1;
        current->x2 -= 1;
        current->y3 += 1;
        current->x4 += 1;
        current->rotate_state = 0;
      }
    }
  }
}

int rotate(Tetramino *current, GameInfo_t *gameInfo) {
  switch (current->type) {
  case I:
    rotate_I(current, gameInfo);
    break;
  case J:
    rotate_J(current, gameInfo);
    break;
  case L:
    rotate_L(current, gameInfo);
    break;
  case S:
    rotate_S(current, gameInfo);
    break;
  case T:
    rotate_T(current, gameInfo);
    break;
  case Z:
    rotate_Z(current, gameInfo);
    break;
  default:
    break;
  }

  return 0;
}

void movedown_clock_check(GameInfo_t *gameInfo, Tetramino *current,
                          tetris_state *state) {
  if (movedown(current, gameInfo)) {
    *state = SPAWN;
    board_update(gameInfo, current);
    int lines = check_full_line(gameInfo);
    lines_to_score(gameInfo, lines);
  } else {
    board_update(gameInfo, current);
  }
}

void spawn_state(GameInfo_t *gameInfo, Tetramino *current, block *nextBlock,
                 tetris_state *state) {
  if (spawn_block(gameInfo, *nextBlock, current)) {
    *state = GAMEOVER;
  } else {
    *nextBlock = rand() % 7;
    next_update(gameInfo, *nextBlock);
    board_update(gameInfo, current);
    *state = MOVING;
  }
}

void move_state(UserAction_t *sig, GameInfo_t *gameInfo, Tetramino *current,
                tetris_state *state) {
  switch (*sig) {
  case Down:
    movedown(current, gameInfo);
    board_update(gameInfo, current);
    break;
  case Right:
    moveright(current, gameInfo);
    board_update(gameInfo, current);
    break;
  case Left:
    moveleft(current, gameInfo);
    board_update(gameInfo, current);
    break;
  case Action:
    rotate(current, gameInfo);
    board_update(gameInfo, current);
    break;
  case Terminate:
    *state = EXIT_STATE;
    break;
  case Pause:
    gameInfo->pause = 1;
    *state = PAUSE;
    break;
  default:
    break;
  }

  if (*state != EXIT_STATE && *state != PAUSE) {
    *state = SHIFTING;
  }
}

void pause_state(UserAction_t *sig, GameInfo_t *gameInfo, tetris_state *state) {
  switch (*sig) {
  case Pause:
    gameInfo->pause = 0;
    *state = MOVING;
    break;
  case Terminate:
    *state = EXIT_STATE;
    break;
  default:
    break;
  }
}

GameInfo_t *get_gameInfo(GameInfo_t *gameInfo) {
  if (gameInfo == NULL) {
    return stored_game_info;
  }
  stored_game_info = gameInfo;
  return stored_game_info;
}

tetris_state *get_state(tetris_state *state) {
  if (state == NULL) {
    return stored_state;
  }
  stored_state = state;
  return stored_state;
}

Tetramino *get_current(Tetramino *current) {
  if (current == NULL) {
    return stored_current;
  }
  stored_current = current;
  return stored_current;
}

block *get_nextBlock(block *nextBlock) {
  if (nextBlock == NULL) {
    return stored_next_block;
  }
  stored_next_block = nextBlock;
  return stored_next_block;
}

bool *get_fallTime(bool *fallTime) {
  if (fallTime == NULL) {
    return stored_fall_time;
  }
  stored_fall_time = fallTime;
  return stored_fall_time;
}

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *gameInfo = get_gameInfo(NULL);
  tetris_state *state = get_state(NULL);
  Tetramino *current = get_current(NULL);
  block *nextBlock = get_nextBlock(NULL);
  bool *fallTime = get_fallTime(NULL);

  if (hold) {
    sigact(&action, fallTime, state, gameInfo, current, nextBlock);
  }

  get_gameInfo(gameInfo);
  get_state(state);
  get_current(current);
  get_nextBlock(nextBlock);
}

void sigact(UserAction_t *sig, const bool *fallTime, tetris_state *state,
            GameInfo_t *gameInfo, Tetramino *current, block *nextBlock) {
  if (*fallTime && *state != START && *state != GAMEOVER && *state != SPAWN &&
      *state != PAUSE) {
    movedown_clock_check(gameInfo, current, state);
  }

  switch (*state) {
  case START:
    switch (*sig) {
    case Action:
      *state = SPAWN;
      break;
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      break;
    }
    break;
  case SPAWN:
    spawn_state(gameInfo, current, nextBlock, state);
    break;
  case MOVING:
    move_state(sig, gameInfo, current, state);
    break;
  case SHIFTING:
    if (*state != SPAWN) {
      *state = MOVING;
    }
    break;
  case PAUSE:
    pause_state(sig, gameInfo, state);
    break;
  case GAMEOVER:
    switch (*sig) {
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void infoInit(GameInfo_t *gameInfo) {
  gameInfo->level = 1;
  gameInfo->score = 0;
  gameInfo->speed = 1;
  gameInfo->high_score = 0;
  gameInfo->pause = 0;

  gameInfo->field = (int **)malloc(sizeof(int *) * FIELD_WIDTH);
  gameInfo->next = (int **)malloc(sizeof(int *) * NEXT_BLOCK_SIZE);

  for (int i = 0; i < FIELD_WIDTH; i++) {
    gameInfo->field[i] = (int *)calloc(sizeof(int), FIELD_HEIGHT);
  }

  for (int i = 0; i < NEXT_BLOCK_SIZE; i++) {
    gameInfo->next[i] = (int *)calloc(sizeof(int), NEXT_BLOCK_SIZE);
  }

  FILE *highScore = fopen(HIGH_SCORE_FILE, "r");
  if (highScore) {
    if (fscanf(highScore, "%d", &gameInfo->high_score) == 0) {
      gameInfo->high_score = 0;
    }
    fclose(highScore);
  }
}

void infoFree(GameInfo_t *gameInfo) {
  for (int i = 0; i < FIELD_WIDTH; i++) {
    free(gameInfo->field[i]);
  }

  for (int i = 0; i < NEXT_BLOCK_SIZE; i++) {
    free(gameInfo->next[i]);
  }

  free(gameInfo->field);
  free(gameInfo->next);
}

void tetramino_init_I(Tetramino *current) {
  initialize_tetramino_coordinates(current, 3, 0, 4, 0, 5, 0, 6, 0, I);
}

void tetramino_init_J(Tetramino *current) {
  initialize_tetramino_coordinates(current, 4, 0, 4, 1, 5, 1, 6, 1, J);
}

void tetramino_init_L(Tetramino *current) {
  initialize_tetramino_coordinates(current, 4, 1, 5, 1, 6, 1, 6, 0, L);
}

void tetramino_init_O(Tetramino *current) {
  initialize_tetramino_coordinates(current, 4, 0, 5, 0, 4, 1, 5, 1, O);
}

void tetramino_init_S(Tetramino *current) {
  initialize_tetramino_coordinates(current, 5, 0, 6, 0, 4, 1, 5, 1, S);
}

void tetramino_init_T(Tetramino *current) {
  initialize_tetramino_coordinates(current, 5, 0, 4, 1, 5, 1, 6, 1, T);
}

void tetramino_init_Z(Tetramino *current) {
  initialize_tetramino_coordinates(current, 4, 0, 5, 0, 5, 1, 6, 1, Z);
}

static void initialize_tetramino_coordinates(Tetramino *current, int x1, int y1,
                                             int x2, int y2, int x3, int y3,
                                             int x4, int y4, block type) {
  current->x1 = x1;
  current->y1 = y1;
  current->x2 = x2;
  current->y2 = y2;
  current->x3 = x3;
  current->y3 = y3;
  current->x4 = x4;
  current->y4 = y4;
  current->type = type;
}

int board_update(GameInfo_t *board, Tetramino *current) {
  board->field[current->x1][current->y1] = 1;
  board->field[current->x2][current->y2] = 1;
  board->field[current->x3][current->y3] = 1;
  board->field[current->x4][current->y4] = 1;
  return 0;
}

void next_update(GameInfo_t *board, block nextBlock) {
  switch (nextBlock) {
  case I:
    next_init_I(board);
    break;
  case J:
    next_init_J(board);
    break;
  case L:
    next_init_L(board);
    break;
  case O:
    next_init_O(board);
    break;
  case S:
    next_init_S(board);
    break;
  case T:
    next_init_T(board);
    break;
  case Z:
    next_init_Z(board);
    break;
  default:
    break;
  }
}

void next_init_I(GameInfo_t *board) {
  initialize_next_block_display(board, 1, 1, 1, 1, 0, 0, 0, 0);
}

void next_init_J(GameInfo_t *board) {
  initialize_next_block_display(board, 1, 0, 0, 0, 1, 1, 1, 0);
}

void next_init_L(GameInfo_t *board) {
  initialize_next_block_display(board, 0, 0, 0, 1, 1, 1, 1, 0);
}

void next_init_O(GameInfo_t *board) {
  initialize_next_block_display(board, 0, 1, 1, 0, 0, 1, 1, 0);
}

void next_init_S(GameInfo_t *board) {
  initialize_next_block_display(board, 0, 1, 1, 0, 1, 1, 0, 0);
}

void next_init_T(GameInfo_t *board) {
  initialize_next_block_display(board, 0, 1, 0, 0, 1, 1, 1, 0);
}

void next_init_Z(GameInfo_t *board) {
  initialize_next_block_display(board, 1, 1, 0, 0, 0, 1, 1, 0);
}

static void initialize_next_block_display(GameInfo_t *board, int row1_col0,
                                          int row1_col1, int row1_col2,
                                          int row1_col3, int row2_col0,
                                          int row2_col1, int row2_col2,
                                          int row2_col3) {
  board->next[1][0] = row1_col0;
  board->next[1][1] = row1_col1;
  board->next[1][2] = row1_col2;
  board->next[1][3] = row1_col3;

  board->next[2][0] = row2_col0;
  board->next[2][1] = row2_col1;
  board->next[2][2] = row2_col2;
  board->next[2][3] = row2_col3;
}

int spawn_block(GameInfo_t *gameInfo, block block_type, Tetramino *current) {
  switch (block_type) {
  case I:
    tetramino_init_I(current);
    break;
  case J:
    tetramino_init_J(current);
    break;
  case L:
    tetramino_init_L(current);
    break;
  case O:
    tetramino_init_O(current);
    break;
  case S:
    tetramino_init_S(current);
    break;
  case T:
    tetramino_init_T(current);
    break;
  case Z:
    tetramino_init_Z(current);
    break;
  default:
    break;
  }

  current->rotate_state = 0;
  return is_not_spawnable(gameInfo, current);
}

int is_not_spawnable(GameInfo_t *gameInfo, Tetramino *current) {
  if (gameInfo->field[current->x1][current->y1] == 0 &&
      gameInfo->field[current->x2][current->y2] == 0 &&
      gameInfo->field[current->x3][current->y3] == 0 &&
      gameInfo->field[current->x4][current->y4] == 0) {
    return 0;
  }
  return 1;
}

void lines_to_score(GameInfo_t *gameInfo, int lines) {
  switch (lines) {
  case 1:
    gameInfo->score += SCORE_SINGLE_LINE;
    break;
  case 2:
    gameInfo->score += SCORE_DOUBLE_LINE;
    break;
  case 3:
    gameInfo->score += SCORE_TRIPLE_LINE;
    break;
  case 4:
    gameInfo->score += SCORE_TETRIS;
    break;
  default:
    if (lines > 4) {
      gameInfo->score += SCORE_TETRIS;
    }
    break;
  }

  if (gameInfo->score > gameInfo->high_score) {
    gameInfo->high_score = gameInfo->score;
    FILE *highScore = fopen(HIGH_SCORE_FILE, "w");
    if (highScore) {
      fprintf(highScore, "%d", gameInfo->high_score);
      fclose(highScore);
    }
  }

  int new_level = gameInfo->score / LEVEL_UP_SCORE + 1;
  if (new_level > 10) {
    new_level = 10;
  }
  gameInfo->level = new_level;
  gameInfo->speed = gameInfo->level;
}

int check_full_line(GameInfo_t *board) {
  int lines = 0;

  for (int y = 0; y < FIELD_HEIGHT; y++) {
    int isFull = 1;
    for (int x = 0; x < FIELD_WIDTH; x++) {
      if (board->field[x][y] == 0) {
        isFull = 0;
        break;
      }
    }

    if (isFull) {
      lines++;
      for (int y1 = y; y1 > 0; y1--) {
        for (int x1 = 0; x1 < FIELD_WIDTH; x1++) {
          board->field[x1][y1] = board->field[x1][y1 - 1];
        }
      }
      for (int x1 = 0; x1 < FIELD_WIDTH; x1++) {
        board->field[x1][0] = 0;
      }

      y--;
    }
  }

  return lines;
}

tetris_state game_loop(GameInfo_t *gameInfo, UserAction_t sig) {
  static tetris_state state = START;
  static Tetramino current;
  static block nextBlock;
  static bool fallTime = false;
  static clock_t last_move_time = 0;
  static bool initialized = false;

  if (!initialized) {
    fallTime = false;
    last_move_time = clock();
    nextBlock = rand() % 7;
    state = START;

    current.rotate_state = 0;
    current.type = 0;
    current.x1 = 0;
    current.x2 = 0;
    current.x3 = 0;
    current.x4 = 0;
    current.y1 = 0;
    current.y2 = 0;
    current.y3 = 0;
    current.y4 = 0;

    initialized = true;

    if (gameInfo != NULL) {
      get_gameInfo(gameInfo);
      get_state(&state);
      get_current(&current);
      get_nextBlock(&nextBlock);
      get_fallTime(&fallTime);
    }
  }

  if (gameInfo != NULL) {
    get_gameInfo(gameInfo);
    get_state(&state);
    get_current(&current);
    get_nextBlock(&nextBlock);
    get_fallTime(&fallTime);

    if (state == START || state == MOVING || state == GAMEOVER ||
        state == PAUSE) {
      update_game_speed(&last_move_time, gameInfo);
    }

    userInput(sig, true);
    fallTime = false;
  }

  return state;
}

static void update_game_speed(clock_t *last_move_time, GameInfo_t *game_info) {
  clock_t current_time = clock();
  int required_speed = calculate_game_speed(game_info->speed);

  if (current_time - *last_move_time >= required_speed) {
    *last_move_time = current_time;
    bool fall_time_flag = true;
    get_fallTime(&fall_time_flag);
  }
}

static int calculate_game_speed(int level) {
  int speed = BASE_SPEED - (level * SPEED_DECREMENT + MIN_SPEED);
  if (speed < MIN_SPEED) {
    speed = MIN_SPEED;
  }
  return speed;
}