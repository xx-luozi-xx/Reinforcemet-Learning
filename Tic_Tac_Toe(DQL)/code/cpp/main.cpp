#include "RL_setting.h"
#include "agent.h"
#include "tic_tac_toe.h"
#include "luozilib.h"

#include <time.h>   //time()
#include <stdlib.h> //rand(), srand()
#include <assert.h> //assert()
#include <math.h>   //pow()

#include <iostream>  
#include <algorithm> //max(), min()
#include <tuple>     //pair
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::pair;
using namespace RL;
using namespace tic_tac_toe;

int main(){
    srand(time(0)^rand());
    Agent player_black("player_black", {18, 8, 4, 1}, 9, 9, LEARNING_RATE, EPSILON);
    Agent player_white("player_white", {18, 8, 4, 1}, 9, 9, LEARNING_RATE, EPSILON);
    player_black.set_name(player_black.name()+"_"+TEST_ID);
    player_white.set_name(player_white.name()+"_"+TEST_ID);
    
    printf("%llu %llu\n", sizeof(player_black), sizeof(player_white));
    vector<State> final_history;
    for(int _ = 1; _ <= GAME_ROUND; ++_){

        double epsilon;
        if(std::string(TEST_ID) == "0"){
            epsilon = (30000-(_-10000))/double(30000);
            epsilon = std::max(0.0, epsilon);
            epsilon = std::min(1.0, epsilon);
            player_black.set_epsilon(epsilon);
            player_white.set_epsilon(epsilon);

            player_black.set_epsilon(_<10000?1:0.5);
            player_white.set_epsilon(_<10000?1:0.5);
        }else if(std::string(TEST_ID) == "1"){
            epsilon = _<=30000?0.1:0;
            player_black.set_epsilon(epsilon);
            player_white.set_epsilon(1);
        }else if(std::string(TEST_ID) == "2"){
            epsilon = _<=30000?0.1:0;
            player_black.set_epsilon(1);
            player_white.set_epsilon(epsilon);
        }


        if(_%1000 == 0) std::cout << "round " << _ << "epsilon:" << epsilon << "\n";
        if(_%100 == 0 and _>39000) std::cout << "round " << _ << "epsilon:" << epsilon << "\n";

        Game game;
        vector<pair<vector<double>, int>> history_black;
        vector<pair<vector<double>, int>> history_white;
        while(!game.is_end()){
            //black do
            if(_>=10000) printf("\nB\n");
            while(!game.is_end()){
                string env_str = game.get_environment(); 
                vector<double> env;
                for(char i : env_str){
                    env.push_back(i-'0');
                }
                if(_>=10000) printf("reB ");
                int opr = player_black.reaction(env);
                State rc = game.operate(opr);

                if(rc != BAD_POR){
                    history_black.push_back({env, opr});
                    player_black.learn(env, opr, NORMAL_SCORE);
                    break;
                }else if(rc == BAD_POR){
                    //打你一巴掌，重新下
                    if(_>=10000) printf("lnB ");
                    player_black.learn(env, opr, ERROR_SCORE);
                    continue;
                }
            }

            if(_>=10000) printf("\nW\n");
            //white do
            while(!game.is_end()){
                string env_str = game.get_environment(); 
                vector<double> env;
                for(char i : env_str){
                    env.push_back(i-'0');
                }
                if(_>=10000) printf("reW ");
                int opr = player_white.reaction(env);
                State rc = game.operate(opr);

                if(rc != BAD_POR){
                    history_white.push_back({env, opr});
                    player_white.learn(env, opr, NORMAL_SCORE);
                    break;
                }else if(rc == BAD_POR){
                    //打你一巴掌，重新下
                    if(_>=10000) printf("lnW ");
                    player_white.learn(env, opr, ERROR_SCORE);
                    continue;
                }
            }
        }
        // printf("\n-----\n");
        State rc = game.judge();
        final_history.push_back(rc);
        if(rc == BLACK_WIN){
            for(int i = 0; i < history_black.size(); ++i){
                player_black.learn(history_black[i].first, history_black[i].second, WIN_SCORE-(i+1));
            }
            for(int i = 0; i < history_white.size(); ++i){
                player_white.learn(history_white[i].first, history_white[i].second, LOSE_SCORE-(i+1));
            }
        }else if(rc == WHITE_WIN){
            for(int i = 0; i < history_black.size(); ++i){
                player_black.learn(history_black[i].first, history_black[i].second, LOSE_SCORE-(i+1));
            }
            for(int i = 0; i < history_white.size(); ++i){
                player_white.learn(history_white[i].first, history_white[i].second, WIN_SCORE-(i+1));
            }
        }else if(rc == DRAW){
            for(int i = 0; i < history_black.size(); ++i){
                player_black.learn(history_black[i].first, history_black[i].second, DRAW_SCORE-(i+1));
            }
            for(int i = 0; i < history_white.size(); ++i){
                player_white.learn(history_white[i].first, history_white[i].second, DRAW_SCORE-(i+1));
            }
        }else{  
            assert(0);
        }
    }
    printf("\nend");
    // player_black.save(SAVING_PATH);
    // player_white.save(SAVING_PATH);

    int win_black_cnt = 0;
    int win_white_cnt = 0;
    vector<double>rate_black;
    vector<double>rate_white;
    for(int i = 0, cnt = 0; i < final_history.size(); ++i, ++cnt, cnt%=1000){
        if(cnt == 0){
            if(i != 0){
                rate_black.push_back(win_black_cnt/double(1000));
                rate_white.push_back(win_white_cnt/double(1000));
            }
            win_black_cnt = 0;
            win_white_cnt = 0;
        }
        win_black_cnt += (final_history[i]==BLACK_WIN);
        win_white_cnt += (final_history[i]==WHITE_WIN);
    }
    rate_black.push_back(win_black_cnt/double(1000));
    rate_white.push_back(win_white_cnt/double(1000));

    std::ofstream fout(std::string(SAVING_PATH)+"Winning_Rage_"+TEST_ID);
    fout << rate_black.size() << '\n';
    for(int i = 0; i < rate_black.size(); ++i){
        fout << '\t' << rate_black[i] << ' ';
    }
    fout << '\n';
    fout << rate_white.size() << '\n';
    for(int i = 0; i < rate_white.size(); ++i){
        fout << '\t' << rate_white[i] << ' ';
    }
    fout.close();
    
    system("python -u show.py");

    return 0;
}