#ifndef nanopong_h
#define nanopong_h

#include "nanolib.h"

typedef struct s_paddle_position_map {
    uint8_t position;
    uint8_t bit;
} t_paddle_position_map;

typedef struct s_adcValue_position_map {
    uint16_t adcValue;
    uint8_t position;
} t_adcValue_position_map;

typedef enum e_ball_direction {
    Left,               //0
    Right,              //1
    Diagonal_Up_Left,   //2
    Diagonal_Up_Right,  //3
    Diagonal_Down_Left, //4
    Diagonal_Down_Right //5
} t_ball_direction;

typedef struct s_ball {
    //Defined by: e_ball_direction.
    t_ball_direction direction;      
    //Top left corner is 0,0.
    //Bottom right corner is 7,7.
    uint8_t x;  //Min = 0, Max = 7
    uint8_t y;  //Min = 0, Max = 7
} t_ball;

typedef struct s_player {
    uint8_t index;          //Min = 0, Max = 1
    uint8_t paddlePosition; //Min = 0, Max = 5 (To sync coords with ball offset by +1 !)
    uint8_t score;          //Min = 0, Max = 3
} t_player;

typedef struct s_game {
    t_player players[2];
    t_ball ball;
    uint8_t isGameStarted;
    uint8_t isGameFinished;
} t_game;

t_ball initBall();

t_ball updateBall(t_game game);

void updatePaddles(t_game* game);

t_ball checkAndOrChangeDirection(t_ball ball, t_player player1, t_player player2);

t_ball checkDirectionHorizontal(t_ball ball, t_player player1, t_player player2);

t_ball checkDirectionVertical(t_ball ball);

t_ball moveBall(t_ball ball);

uint8_t get_paddle_position(t_player player);

t_game init_game();

void start_game();

void draw_game(t_game game);

uint8_t get_paddle_position(t_player player);

uint8_t generate_random_number(uint8_t lower, uint8_t upper); //upper inclusive

char* getDirectionString(t_ball ball);

void displayPointsLed(t_game game);

void waitForButtonPress();

#endif