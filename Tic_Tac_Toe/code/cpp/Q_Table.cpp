#include "Q_Table.h"
#include "luozilib.h" //rand()
namespace RL{
    Q_Table::Q_Table(size_t state_num, size_t action_num, double init_val):
        state_num_(state_num),
        action_num_(action_num),
        table_(vector<vector<double>>(state_num, vector<double>(action_num, init_val)))
    {
        void();
    }

    size_t Q_Table::state_num()const{
        return state_num_;
    }

    size_t Q_Table::action_num()const {
        return action_num_;
    }

    const vector<double>& Q_Table::operator[](unsigned long long state)const{
        return table_[state];
    }

    //find the i such that table_[state][i] is max.
    unsigned long long Q_Table::take_action(unsigned long long state){
        std::vector<size_t> rets;
        double max_val = table_[state][0];
        for(size_t i = 0; i < action_num(); ++i){
            if(table_[state][i] > max_val){
                rets.clear();
                rets.push_back(i);
                max_val = table_[state][i];
            }else if(table_[state][i] == max_val){
                rets.push_back(i);
            }else{
                void();
            }
        }
        return rets[luozi::rand(0, rets.size()-1)];
    }

    void Q_Table::update(unsigned long long state, unsigned long long action, double reward){
        table_[state][action] = reward;
    }


}//namespace