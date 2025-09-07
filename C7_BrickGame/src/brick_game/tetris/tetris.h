#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define NEXT_BLOCK_SIZE 4

#define ESCAPE 27
#define ENTER_KEY 10

#define LEFT_X 0
#define RIGHT_X 21
#define TOP_Y 0
#define BOT_Y 20
#define NEXT_TOP_Y 1
#define NEXT_BOT_Y 5
#define ESCAPE 27
#define ENTER_KEY 10
#define NEXT_LEFT_X 24
#define NEXT_RIGHT_X 33
#define NEXT_TOP_Y 1
#define NEXT_BOT_Y 5

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define NEXT_BLOCK_SIZE 4
#define SCORE_SINGLE_LINE 100
#define SCORE_DOUBLE_LINE 300
#define SCORE_TRIPLE_LINE 700
#define SCORE_TETRIS 1500
#define LEVEL_UP_SCORE 600
#define BASE_SPEED 12000
#define SPEED_DECREMENT 150
#define MIN_SPEED 10000
#define HIGH_SCORE_FILE "./highscore_tetris.txt"

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  ROTATE,
  SHIFTING,
  COLLIDE,
  GAMEOVER,
  EXIT_STATE,
  PAUSE
} tetris_state;

typedef enum {
  MOVE_DOWN = 0,
  MOVE_RIGHT,
  MOVE_LEFT,
  ESCAPE_BTN,
  ENTER_BTN,
  NOSIG
} signals;

typedef enum {
  Up,
  Down,
  Right,
  Left,
  Action,
  Pause,
  Terminate,
  Start
} UserAction_t;

typedef enum { I = 0, J, L, O, S, T, Z } block;

typedef struct {
  int x1, y1, x2, y2, x3, y3, x4, y4;
  int rotate_state;
  block type;
} Tetramino;

typedef struct {
  int **field;
  int **next;
  int high_score;
  int score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum { first = 0, second, third, fourth } rotateState;

tetris_state game_loop(GameInfo_t *gameInfo, UserAction_t sig);

void infoInit(GameInfo_t *gameInfo);
void infoFree(GameInfo_t *gameInfo);
int spawn_block(GameInfo_t *gameInfo, block block_type, Tetramino *current);
int is_not_spawnable(GameInfo_t *gameInfo, Tetramino *current);
void tetramino_init_I(Tetramino *current);
void tetramino_init_J(Tetramino *current);
void tetramino_init_L(Tetramino *current);
void tetramino_init_O(Tetramino *current);
void tetramino_init_S(Tetramino *current);
void tetramino_init_T(Tetramino *current);
void tetramino_init_Z(Tetramino *current);
void next_init_I(GameInfo_t *board);
void next_init_J(GameInfo_t *board);
void next_init_L(GameInfo_t *board);
void next_init_O(GameInfo_t *board);
void next_init_S(GameInfo_t *board);
void next_init_T(GameInfo_t *board);
void next_init_Z(GameInfo_t *board);
int check_full_line(GameInfo_t *board);
void lines_to_score(GameInfo_t *gameInfo, int lines);
int board_update(GameInfo_t *board, Tetramino *current);
void next_update(GameInfo_t *board, block nextBlock);

GameInfo_t *get_gameInfo(GameInfo_t *gameInfo);
tetris_state *get_state(tetris_state *state);
Tetramino *get_current(Tetramino *current);
block *get_nextBlock(block *nextBlock);
bool *get_fallTime(bool *fallTime);
void userInput(UserAction_t action, bool hold);
void sigact(UserAction_t *sig, const bool *fallTime, tetris_state *state,
            GameInfo_t *gameInfo, Tetramino *current, block *nextBlock);
void spawn_state(GameInfo_t *gameInfo, Tetramino *current, block *nextBlock,
                 tetris_state *state);
void move_state(UserAction_t *sig, GameInfo_t *gameInfo, Tetramino *current,
                tetris_state *state);
void pause_state(UserAction_t *sig, GameInfo_t *gameInfo, tetris_state *state);
int movedown(Tetramino *current, GameInfo_t *gameInfo);
void moveright(Tetramino *current, GameInfo_t *gameInfo);
void moveleft(Tetramino *current, GameInfo_t *gameInfo);
void movedown_clock_check(GameInfo_t *gameInfo, Tetramino *current,
                          tetris_state *state);
int rotate(Tetramino *current, GameInfo_t *gameInfo);
void rotate_I(Tetramino *current, GameInfo_t *gameInfo);
int rotate_J_first(Tetramino *current, GameInfo_t *gameInfo);
void rotate_J_second(Tetramino *current, GameInfo_t *gameInfo);
void rotate_J(Tetramino *current, GameInfo_t *gameInfo);
int rotate_L_first(Tetramino *current, GameInfo_t *gameInfo);
void rotate_L_second(Tetramino *current, GameInfo_t *gameInfo);
void rotate_L(Tetramino *current, GameInfo_t *gameInfo);
void rotate_S(Tetramino *current, GameInfo_t *gameInfo);
int rotate_T_first(Tetramino *current, GameInfo_t *gameInfo);
void rotate_T_second(Tetramino *current, GameInfo_t *gameInfo);
void rotate_T(Tetramino *current, GameInfo_t *gameInfo);
void rotate_Z(Tetramino *current, GameInfo_t *gameInfo);
void clear_backpos(Tetramino *current, GameInfo_t *gameInfo);

#endif // TETRIS_H_