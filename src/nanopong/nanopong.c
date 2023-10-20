#include "nanopong.h"


static const t_paddle_position_map paddle_position_map[] = {
  {0, 0b00000111}, {1, 0b00001110}, {2, 0b00011100},
  {3, 0b00111000}, {4, 0b01110000}, {5, 0b11100000}
};

static const uint8_t ball_position_map[] = {
  0b00000001, 0b00000010, 0b00000100, 0b00001000,
  0b00010000, 0b00100000, 0b01000000, 0b10000000
};

static const t_adcValue_position_map adcValue_pos_map[] = {
  {170, 0}, {341, 1}, {512, 2}, {682, 3}, {852, 4}, {1023, 5}
};

t_ball initBall() {
    //Create the ball.
    t_ball ball;
    ball.direction = generate_random_number(0, 5);
    ball.x = generate_random_number(3, 4);
    ball.y = generate_random_number(3, 4);
    
    //printf("Ball has been init : x = %d | y = %d | dir = %d\n", ball.x, ball.y, ball.direction);
    return ball;
}

t_ball updateBall(t_game game) {
    game.ball = checkAndOrChangeDirection(game.ball, game.players[0], game.players[1]);
    game.ball = moveBall(game.ball);
    return game.ball;
}

t_ball checkAndOrChangeDirection(t_ball ball, t_player player1, t_player player2) {
    if (((ball.x == 1) || ball.x == 6) && ((ball.y == 0) || (ball.y == 7))){
        ball = checkDirectionVertical(ball);
    }
    ball = checkDirectionHorizontal(ball, player1, player2);
    ball = checkDirectionVertical(ball);
    
    return ball;
}

t_ball checkDirectionHorizontal(t_ball ball, t_player player1, t_player player2) {
    if (ball.x == 1) {   //Check if ball is neighboring the Left Paddle (Player 1).
        if (ball.direction % 2 == 0) {  //Check if ball is going left.
            if (ball.y == (player1.paddlePosition + 1)) { //Ball hit the middle of the paddle.
                ball.direction = Right;
                //printf("!!! EVENT !!! - Ball hit Left paddle in the center.\n");
            } else if ((ball.y == (player1.paddlePosition + 1) - 1) || ((ball.y == (player1.paddlePosition + 1) - 2) && (ball.direction == Diagonal_Down_Left))) { //Ball hit the top side of the paddle.
                ball.direction = Diagonal_Up_Right;
                //printf("!!! EVENT !!! - Ball hit Left paddle on the top side or top diagonal.\n");
            } else if ((ball.y == (player1.paddlePosition + 1) + 1) || ((ball.y == (player1.paddlePosition + 1) + 2) && (ball.direction == Diagonal_Up_Left))) { //Ball hit the bottom side of the paddle.
                ball.direction = Diagonal_Down_Right;
                //printf("!!! EVENT !!! - Ball hit Left paddle on the bottom side or bottom diagonal.\n");     
            }
        }
    }

    if (ball.x == 6) { //Check if ball is neighboring the Right Paddle (Player 2).
        if (ball.direction % 2 == 1) {  //Check if ball is going right.
            if (ball.y == (player2.paddlePosition + 1)) { //Ball hit the middle of the paddle.
                ball.direction = Left;
                //printf("!!! EVENT !!! - Ball hit Right paddle in the center.\n");
            } else if ((ball.y == (player2.paddlePosition + 1) - 1) || ((ball.y == (player2.paddlePosition + 1) - 2) && (ball.direction == Diagonal_Down_Right))) { //Ball hit the top side of the paddle.
                ball.direction = Diagonal_Up_Left;
                //printf("!!! EVENT !!! - Ball hit Right paddle on the top side or top diagonal.\n");
            } else if ((ball.y == (player2.paddlePosition + 1) + 1) || ((ball.y == (player2.paddlePosition + 1) + 2) && (ball.direction == Diagonal_Up_Right))) { //Ball hit the bottom side of the paddle.
                ball.direction = Diagonal_Down_Left;
                //printf("!!! EVENT !!! - Ball hit Right paddle on the bottom side or bottom diagonal.\n");     
            }
        }
    }
    
    return ball;
}

t_ball checkDirectionVertical(t_ball ball) {
    if (ball.y == 0) { //Top
        if (ball.direction % 2 == 0) { //Left.
            ball.direction = Diagonal_Down_Left;
            //printf("!!! EVENT !!! - Ball hit the Top of the grid while going Left.\n");
        } else { //Right.
            ball.direction = Diagonal_Down_Right;
            //printf("!!! EVENT !!! - Ball hit the Botto of the grid while going Right.\n");
        }
    }
    if (ball.y == 7) { //Bottom
        if (ball.direction % 2 == 0) { //Left.
            ball.direction = Diagonal_Up_Left;
            //printf("!!! EVENT !!! - Ball hit the Bottom of the grid while going Left.\n");
        } else { //Right.
            ball.direction = Diagonal_Up_Right;
            //printf("!!! EVENT !!! - Ball hit the Bottom of the grid while going Right.\n");
        }
    }
    
    return ball;
}

t_ball moveBall(t_ball ball) {    //Check if the ball is out of bounds.
    
    if (!((ball.x > 0 && ball.x < 7) || (ball.y >= 0 && 7 <= ball.y))) {
        //printf(" !!! EVENT !!! - Ball is out of bounds.\n");
        //If ball is out of bounds then don't move it.
    } else {
        if (ball.direction % 2 == 0) { //True = Left | False = Right.
            ball.x--;
            //printf("Ball moved Left 1.\n");
        } else {
            ball.x++;
            //printf("Ball moved Right 1.\n");
        }

        if (ball.direction != 0 && ball.direction != 1) { //True = Diagonal
            if (ball.direction == 2 || ball.direction == 3) { //True = Up | False = Down.
                ball.y--;
                //printf("Ball moved Up 1.\n");
            } else {
                ball.y++;
                
                //printf("Ball moved Down 1.\n");
            }
        }
    }
    
    //printf("Ball has been updated to : x = %d | y = %d | direction = %s\n", ball.x, ball.y, getDirectionString(ball));
    return ball;
}

t_game init_game() {
  t_player player1 = {0, get_paddle_position(player1), 0};
  t_player player2 = {1, get_paddle_position(player2), 0};
  t_ball ball = initBall();

  return (t_game){ {player1, player2}, ball, 0, 0 };
}

uint8_t get_paddle_position(t_player player) {
  uint16_t adcValue;
  if (player.index == 0) 
  {
    adcValue = analog_read(A0) & 0b1111111111111100; 
  }
  else 
  {
    adcValue = analog_read(A1) & 0b1111111111111100;
  }

  for (uint8_t pos = 0; pos < 6; pos++) 
  {
    if (adcValue <= adcValue_pos_map[pos].adcValue) 
      return adcValue_pos_map[pos].position;
  }
}

void draw_game(t_game game)
{
  for (uint8_t player = 0; player < 2; player++) {
    if (player == 0)
      write_column_MAX7219(1, paddle_position_map[game.players[player].paddlePosition].bit);
    else 
      write_column_MAX7219(8, paddle_position_map[game.players[player].paddlePosition].bit);
  }

  write_column_MAX7219(game.ball.x + 1, ball_position_map[game.ball.y]);
}

uint8_t generate_random_number(uint8_t lower, uint8_t upper)
{
  srand(analog_read(A5));
  return (rand() % (upper - lower + 1)) + lower;
}

void updatePaddles(t_game* game) {
    for (uint8_t i = 0; i < 2; i++) {
        game->players[i].paddlePosition = get_paddle_position(game->players[i]);
  }
  //printf("Paddles have been updated to : Paddle-1 = %d | Paddle-2 = %d\n", game->players[0].paddlePosition + 1, game->players[1].paddlePosition + 1);
}

char* getDirectionString(t_ball ball) {
    switch (ball.direction) {
        case 0:
            return "Left";
        case 1:
            return "Right";
        case 2:
            return "Diagonal_Up_Left";
        case 3:
            return "Diagonal_Up_Right";
        case 4:
            return "Diagonal_Down_Left";
        case 5:
            return "Diagonal_Down_Right";
    }
    return ". . ."; 
}

void displayPointsLed(t_game game) {
switch (game.players[0].score) { //Player-2 (Right).
        case 1:
            write_output_GPIO(D2, HIGH);
            write_output_GPIO(D3, LOW);
            write_output_GPIO(D4, LOW);
            break;
        case 2:
            write_output_GPIO(D2, HIGH);
            write_output_GPIO(D3, HIGH);
            write_output_GPIO(D4, LOW);
            break;
        case 3:
            write_output_GPIO(D2, HIGH);
            write_output_GPIO(D3, HIGH);
            write_output_GPIO(D4, HIGH);
            break;
        default:
            write_output_GPIO(D2, LOW);
            write_output_GPIO(D3, LOW);
            write_output_GPIO(D4, LOW);
            break;
    }

    switch (game.players[1].score) { //Player-1 (Left).
        case 1:
            write_output_GPIO(D5, HIGH);
            write_output_GPIO(D6, LOW);
            write_output_GPIO(D7, LOW);
            break;
        case 2:
            write_output_GPIO(D5, HIGH);
            write_output_GPIO(D6, HIGH);
            write_output_GPIO(D7, LOW);
            break;
        case 3:
            write_output_GPIO(D5, HIGH);
            write_output_GPIO(D6, HIGH);
            write_output_GPIO(D7, HIGH);
            break;
        default:
            write_output_GPIO(D5, LOW);
            write_output_GPIO(D6, LOW);
            write_output_GPIO(D7, LOW);
            break;
    }
}

void waitForButtonPress() {
    printf("Press button to start.\n");
    for(;;) {
      if (read_input_GPIO(D8) == LOW) {
        printf("-> Start !\n");
        return;
      }
    }
}


