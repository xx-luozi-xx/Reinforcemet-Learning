#include "tic_tac_toe.h"
#include <vector>

namespace tic_tac_toe{

    int env_str_to_int(const std::string& str){
        int ret = 0;
        for(int i = 0; i < 9; ++i){
            ret*=3;
            ret+= str[i]-'0';
        }
        return ret;
    }

    std::string int_to_env_str(int num){
        std::string ret = "000000000";
        for(int i = 8; i >= 0; --i){
            ret[i] = num%3 + '0';
            num/=3;
        }
        return ret;
    }

    Game::Game():
        board_("000000000")
    {
        void();
    }

    const std::string& Game::get_environment()const{
        return board_; 
    }

    State Game::operate(int pos){
        if(0<=pos and pos <= 8){
            if(board_[pos] == '0'){
                board_[pos] = which_round_;
                which_round_= which_round_==BLACK?WHITE:BLACK;

                return judge();
            }else{
                return BAD_POR;
            }
        }else{
            return BAD_POR;
        }
    }

    bool Game::is_end()const{
        return judge()!= NOT_WIN;
    }

    State Game::judge()const{
        static std::vector<std::vector<int>> pos={
            {0,1,2},
            {3,4,5},
            {6,7,8},
            {0,3,6},
            {1,4,7},
            {2,5,8},
            {0,4,8},
            {2,4,6}
        };
        //is win?
        for(const auto& ps : pos){
            bool is_black_win = 1;
            for(auto i : ps){
                if(board_[i] != BLACK){
                    is_black_win = 0;
                    break;
                }
            }
            if(is_black_win){
                return BLACK_WIN;
            }
            
            bool is_white_win = 1;
            for(auto i : ps){
                if(board_[i] != WHITE){
                    is_white_win = 0;
                    break;
                }
            }
            if(is_white_win){
                return WHITE_WIN;
            }
        }

        //is draw?
        for(int i = 0; i < 9; ++i){
            if(board_[i] == SPACE){
                return NOT_WIN;
            }
        }
        return DRAW;
    }

}//namespace




