#include "agent.h"
#include "luozilib.h"   //rand()

#include <assert.h>     //assert()
#include <fstream>
#include <vector>

namespace RL{
    
    Agent::Agent(const std::string& name, const std::vector<size_t>& shape,
        size_t state_dim, size_t aciton_num,  
        double learning_rate, double epsilon):
        name_(name), 
        state_dim_(state_dim),
        action_num_(aciton_num),
        learning_rate_(learning_rate),
        epsilon_(epsilon),
        mlp_(shape)
    {
        void();    
    }

    unsigned long long Agent::reaction(const std::vector<double>& state){
        if(luozi::rand(1.0) <= epsilon_){
            return rand()%action_num();
        }
        double max_val = -1e9;
        unsigned long long ret = 0;
        for(int i = 0; i < action_num(); ++i){
            std::vector<double> input(mlp_.input_dim(), 0);
            for(int j = 0; j < state.size(); ++j){
                input[j] = state[j];
            }
            input[state.size()+i] = 1;
            double val = mlp_.val(input)[0];
            if(val > max_val){
                max_val = val;
                ret = i;
            }
        }
        printf("%llf, %d\n", max_val, ret);
        system("pause");
        return ret;
    }

    double Agent::learn(const std::vector<double>& state, unsigned long long action, double reward){
        std::vector<double> input(mlp_.input_dim(), 0);
        for(int i = 0; i < state.size(); ++i){
            input[i] = state[i];
        }

        input[state.size()+action] = 1;
        return mlp_.learn(input, {reward}, learning_rate_);
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

    size_t Agent::state_dim()const{
        return state_dim_;
    }

    size_t Agent::action_num() const{
        return action_num_;
    }

    bool Agent::save(const std::string& path)const{
        assert(0);


        // //saving a file need a name
        // assert(name()!="");
        // std::ofstream fout(path+name()+".agent");
        // //open file failed
        // assert(fout.is_open());

        // fout << name() << '\n';
        // fout << learning_rate_ << '\n';
        // fout << Q_.state_num() << ' ' << Q_.action_num() << '\n';
        // for(size_t i = 0; i < Q_.state_num(); ++i){
        //     for(size_t j = 0; j < Q_.action_num(); ++j){
        //         fout << Q_[i][j] << ' ';
        //     }
        //     fout << '\n';
        // }

        return true;
    }

    bool Agent::load(const std::string& file_name){
        assert(0);


        // std::ifstream fin(file_name);
        // //open file failed
        // assert(fin.is_open());

        // assert(fin >> name_);
        // assert(fin >> learning_rate_);

        // size_t state_num, action_num;
        // assert(fin >> state_num >> action_num);

        // Q_ = Q_Table(state_num, action_num, 0);
        // for(size_t i = 0; i < Q_.state_num(); ++i){
        //     for(size_t j = 0; j < Q_.action_num(); ++j){
        //         double val; 
        //         assert(fin >> val);
                
        //         Q_.update(i, j, val);
        //     }
        // }

        return true;
    }


}//namespace