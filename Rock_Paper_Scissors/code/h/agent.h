#pragma once
#include "Q_Table.h"
#include <string>

namespace RL{

class Agent{
public:
    Agent(size_t state_num, size_t action_num);

    unsigned long long reaction(unsigned long long state);
    double learn(unsigned long long state, unsigned long long action, double reward);

    const std::string& name()const;

    size_t state_num()const;
    size_t action_num() const;

    bool save()const;
    bool load(const std::string& path);

protected:
    std::string name_;
    Q_Table Q_;
};

}//namespace