#include "rock_paper_scissors.h"

#include <stdlib.h>     //rand()
namespace rock_paper_scissors{
//init game with env
Game::Game(type env):environment_(env){
    void();
}

//init game with random env
Game::Game(){
    environment_ = type(rand()%3);
}

//return the env now
type Game::get_environment(){
    return environment_;
}

//input your operate and return your score
int Game::operate(type op){
    int ret = judge_(op);
    next_tick();
    return ret;
}

//game rule
int Game::judge_(type op){
    if(op == environment_){
        return DRAW_SCORE;
    }else if(op == ROCK){
        if(environment_ == PAPER){
            return LOSE_SCORE;
        }else{// SCISSORS
            return WIN_SCORE;
        }
    }else if(op == PAPER){
        if(environment_ == SCISSORS){
            return LOSE_SCORE;
        }else{// ROCK
            return WIN_SCORE;
        }
    }else if(op == SCISSORS){
        if(environment_ == ROCK){
            return LOSE_SCORE;
        }else{// PAPER
            return WIN_SCORE;
        }
    }else{//not a allow type
        return ERROR_SCORE;
    }
}

//next game
void Game::next_tick(){
    environment_ = type(rand()%3);
}

std::string to_type(int type_){
    switch (type(type_)){
    case ROCK:      return "rock";
    case PAPER:     return "paper";
    case SCISSORS:  return "scissors";
    default:        return "error_type";
    }
}



}//namespace



