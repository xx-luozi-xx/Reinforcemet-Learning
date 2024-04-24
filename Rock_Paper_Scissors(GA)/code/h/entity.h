#pragma once

#include <vector>

#include "agent.h"

namespace Genetic_Algorithm{

class Entity: public Agent{
public:
    Entity(int chromosome_len, int num_operate);
    Entity(const Entity& father, const Entity& mather);

    int reaction(const std::vector<int>& env) const;
    int num_operate() const;

private:
    int num_operate_;
};


}//namesepace
