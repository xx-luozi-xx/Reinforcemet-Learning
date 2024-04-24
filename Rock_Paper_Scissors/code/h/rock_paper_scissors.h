#pragma once

#include <string>

namespace rock_paper_scissors{

const int WIN_SCORE = 3;
const int LOSE_SCORE = -3;
const int DRAW_SCORE = 0;

const int ERROR_SCORE = -100; 

enum type{
    ROCK,
    PAPER,
    SCISSORS
};

std::string to_type(int type_);

class Game{
public:
    //init game with random env
    Game();
    //init game with env
    Game(type env);
    
    //return the env now
    type get_environment();
    //input your operate and return your score
    int operate(type op);
private:
    type environment_;
    
    //game rule
    int judge_(type op);
    //next game
    void next_tick();
};

}//namespace