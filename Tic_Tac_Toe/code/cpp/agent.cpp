#include "agent.h"
#include "luozilib.h"   //rand()

#include <assert.h>     //assert()
#include <fstream>

namespace RL{
    
    Agent::Agent(const std::string& name, size_t state_num, size_t action_num,double learning_rate, double epsilon, double reward_inf):
        name_(name), 
        learning_rate_(learning_rate),
        epsilon_(epsilon),
        Q_(state_num, action_num, reward_inf)
    {
        void();    
    }

    unsigned long long Agent::reaction(unsigned long long state){
        if(luozi::rand(1.0) <= epsilon_){
            return rand()%action_num();
        }
        return Q_.take_action(state);
    }

    double Agent::learn(unsigned long long state, unsigned long long action, double reward){
        //Q_{n+1} = Q_n + alpha(R_n-Q_n)
        double new_val = Q_[state][action] + learning_rate_*(reward-Q_[state][action]);
        Q_.update(state, action, new_val);
    }

    void Agent::set_name(const std::string& name){
        name_ = name;
    }

    void Agent::set_learning_rate(double learning_rate){
        learning_rate_ = learning_rate; 
    }

    void Agent::set_epsilon(double epsilon){
        epsilon_ = epsilon;
    }

    const std::string& Agent::name()const{
        return name_;
    }

    size_t Agent::state_num()const{
        return Q_.state_num();
    }

    size_t Agent::action_num() const{
        return Q_.action_num();
    }

    bool Agent::save(const std::string& path)const{
        //saving a file need a name
        assert(name()!="");
        std::ofstream fout(path+name()+".agent");
        //open file failed
        assert(fout.is_open());

        fout << name() << '\n';
        fout << learning_rate_ << '\n';
        fout << Q_.state_num() << ' ' << Q_.action_num() << '\n';
        for(size_t i = 0; i < Q_.state_num(); ++i){
            for(size_t j = 0; j < Q_.action_num(); ++j){
                fout << Q_[i][j] << ' ';
            }
            fout << '\n';
        }

        return true;
    }

    bool Agent::load(const std::string& file_name){
        std::ifstream fin(file_name);
        //open file failed
        assert(fin.is_open());

        assert(fin >> name_);
        assert(fin >> learning_rate_);

        size_t state_num, action_num;
        assert(fin >> state_num >> action_num);

        Q_ = Q_Table(state_num, action_num, 0);
        for(size_t i = 0; i < Q_.state_num(); ++i){
            for(size_t j = 0; j < Q_.action_num(); ++j){
                double val; 
                assert(fin >> val);
                
                Q_.update(i, j, val);
            }
        }

        return true;
    }


}//namespace