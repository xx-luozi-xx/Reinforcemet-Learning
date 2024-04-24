#include <stdlib.h>

namespace luozi{
int rand(int down, int up){
    int range = up-down+1;
    return ::rand()%range + down;
}

}//namespace
