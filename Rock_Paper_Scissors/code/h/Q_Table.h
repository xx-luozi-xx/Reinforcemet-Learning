#pragma once
#include <vector>
    using std::vector;

namespace RL{

class Q_Table{
public:
    Q_Table(size_t state_num, size_t action_num);

    size_t state_num()const;
    size_t action_num()const;

    const vector<double>& operator[](unsigned long long state)const;
    void update(unsigned long long state, unsigned long long action, double reward);
protected:
    size_t state_num_;
    size_t action_num_;
    vector<vector<double>> table;
};

}//namespace