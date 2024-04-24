#pragma once

#include <vector>
#include <string>

namespace Genetic_Algorithm{

class Agent{
public:
    Agent(int chromosome_len);
    Agent(const Agent& father, const Agent& mather);

    void cross();
    void mutation();

    int chromosome_len() const;
    std::string show_chromosome() const;
protected:
    int chromosome_len_;
    std::vector<int> chromosome_[2];
};

}//namespace