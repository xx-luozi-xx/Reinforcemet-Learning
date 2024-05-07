#pragma once

#include <string>

namespace tic_tac_toe{

const int WIN_SCORE = 10000;
const int LOSE_SCORE = -10000;
const int DRAW_SCORE = 0;

const int ERROR_SCORE = -100; 
const int NORMAL_SCORE = 100; 

int env_str_to_int(const std::string& str);
std::string int_to_env_str(int num);

enum Piece{
    SPACE = '0', BLACK, WHITE, 
};

enum State{
    NOT_WIN, BLACK_WIN, WHITE_WIN, DRAW, BAD_POR
};

class Game{
public:
    //init game with init env
    Game();
    
    //return the env now
    const std::string& get_environment()const;
    //input your operate and return the game state
    State operate(int pos);
    bool is_end() const;
    State judge()const;

private:
    Piece which_round_ = BLACK;
    std::string board_;

};

}//namespace