#pragma once
#include "MLP.h"
#include <string>
#include <stddef.h>     //size_t
namespace RL{

class Agent{
public:
    Agent(const std::string& name, const std::vector<size_t>& shape, size_t state_dim, size_t action_num,double learning_rate, double epsilon = 0);

    unsigned long long reaction(const std::vector<double>& state);
    //return loss
    double learn(const std::vector<double>& state, unsigned long long action, double reward);

    void set_name(const std::string& name);
    void set_learning_rate(double learning_rate);
    void set_epsilon(double epsilon);

    const std::string& name()const;
    size_t state_dim()const;
    size_t action_num() const;

    bool save(const std::string& path)const;
    bool load(const std::string& file_name);

protected:
    std::string name_;
    size_t state_dim_;
    size_t action_num_;
    double learning_rate_;
    double epsilon_;
    DL::MLP mlp_;
};

}//namespace