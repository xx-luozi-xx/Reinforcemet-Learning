#include "RL_setting.h"
#include "agent.h"
#include "tic_tac_toe.h"


#include <time.h>   //time()
#include <stdlib.h> //rand(), srand()
#include <assert.h> //assert()
#include <math.h>   //pow()

#include <iostream>  

using namespace RL;
using namespace tic_tac_toe;

int main(){
    srand(time(0)^rand());
    Agent player_black("player_black", pow(3,9), 9, LEARNING_RATE, EPSILON, WIN_SCORE);
    Agent player_white("player_white", pow(3,9), 9, LEARNING_RATE, EPSILON, WIN_SCORE);


    // while(!game.is_end()){
    //     int pos = rand()%9;
    //     game.operate(pos);
    //     std::string baord = game.get_environment();
    //     std::cout << pos << '\n';
    //     std::cout << baord.substr(0,3) << '\n';
    //     std::cout << baord.substr(3,3) << '\n';
    //     std::cout << baord.substr(6,3) << '\n';
    //
    //     int board_num = env_str_to_int(baord);
    //     std::cout << board_num << '\n';
    //     std::string board_str = int_to_env_str(board_num);
    //     assert(board_str == baord);
    // }

    player_white.set_epsilon(0);
    for(int _ = 1; _ <= GAME_ROUND; ++_){
        Game game;
        while(!game.is_end()){
            //black do
            while(1){
                int env = env_str_to_int(game.get_environment()); 
                int opr = player_black.reaction(env);
                State rc = game.operate(opr);
                if(rc != BAD_POR)   
            }

            //white do
        }
    }

    //testing the action of the agent

    // for(int env = 0; env < 3; ++env){
    //     int reaction = player.reaction((type)env);
    //     std::cout << "env:" << to_type(env) 
    //               << "   reaction:" << to_type(reaction) << '\n'; 
    // } 
    
    player_black.save(SAVING_PATH);
    player_white.save(SAVING_PATH);

    return 0;
}