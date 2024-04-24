#include "entity.h"

#include <stdlib.h>
#include <assert.h> //assert();

#include <vector>

namespace Genetic_Algorithm{

Entity::Entity(int chromosome_len, int num_operate)
        :Agent(chromosome_len), num_operate_(num_operate){
    void();        
}

Entity::Entity(const Entity& father, const Entity& mather)
        :Agent(father, mather){
    assert(father.num_operate() == mather.num_operate());
    num_operate_ = father.num_operate();
}

int Entity::num_operate() const{
    return num_operate_;
}

int Entity::reaction(const std::vector<int>& env) const{
    //In the future, this place could get more and more complicated.
    //! coding like this temporarily
    std::vector<int> proteins;
    for(int i = 0; i < chromosome_len(); ++i){
        proteins.push_back(std::max(chromosome_[0][i], chromosome_[1][i]));
    }

    //layer 0
    int x = env[0];

    //layer 1
    std::vector<int> layer_1; 
    for(int i = 0; i < 6; i+=2){
        layer_1.push_back(x*proteins[i]+proteins[i+1]);
        x*=x;
    }

    //layer 2
    int layer_2 = 0;
    for(int i = 0, j = 6; i < 3; ++i, ++j){
        layer_2 += layer_1[i]*proteins[j];
    }
    layer_2 += proteins[9];
    //out reaction
    return layer_2/30;
}

}//namespace