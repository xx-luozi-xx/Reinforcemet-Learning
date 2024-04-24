#include "RL_setting.h"
#include "agent.h"
#include "rock_paper_scissors.h"


#include <time.h>   //time()
#include <stdlib.h> //rand(), srand()

#include <iostream>  

using namespace RL;
using namespace rock_paper_scissors;

int main(){
    srand(time(0)^rand());
    Agent player("player_init", 3, 3, LEARNING_RATE, 10);
    Game game;

    for(int _ = 1; _ <= GAME_ROUND; ++_){
        type now_state = game.get_environment();
        type player_reaction = (type)player.reaction(now_state);
        double reward = game.operate(player_reaction);
        player.learn(now_state, player_reaction, reward);
    }

    //testing the action of the agent

    for(int env = 0; env < 3; ++env){
        int reaction = player.reaction((type)env);
        std::cout << "env:" << to_type(env) 
                  << "   reaction:" << to_type(reaction) << '\n'; 
    } 
    
    player.save(SAVING_PATH);

    return 0;
}