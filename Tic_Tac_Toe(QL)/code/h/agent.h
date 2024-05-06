#pragma once
#include "Q_Table.h"
#include <string>
#include <stddef.h>     //size_t
namespace RL{

class Agent{
public:
    Agent(const std::string& name, size_t state_num, size_t action_num,double learning_rate, double epsilon = 0, double reward_inf = 1e9);

    unsigned long long reaction(unsigned long long state);
    double learn(unsigned long long state, unsigned long long action, double reward);

    void set_name(const std::string& name);
    void set_learning_rate(double learning_rate);
    void set_epsilon(double epsilon);

    const std::string& name()const;
    size_t state_num()const;
    size_t action_num() const;

    bool save(const std::string& path)const;
    bool load(const std::string& file_name);

protected:
    std::string name_;
    double learning_rate_;
    double epsilon_;
    Q_Table Q_;
};

}//namespace