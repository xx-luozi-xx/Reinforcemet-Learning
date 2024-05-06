#include <stdlib.h>

namespace luozi{
int rand(int down, int up){
    int range = up-down+1;
    return ::rand()%range + down;
}

double rand(double){
    return ::rand()/double(RAND_MAX);
}

}//namespace
