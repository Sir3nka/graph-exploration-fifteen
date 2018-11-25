//
// Created by Dirkuu on 01.11.2018.
//

#ifndef FIFTEENGAME_HASHES_CPP
#define FIFTEENGAME_HASHES_CPP

#include "Board.h"

matrix Goal =  {{1,2,3,4},
                {5,6,7,8},
                {9,10,11,12},
                {13,14,15,0}};


template <typename T>
struct Hash{
    //
    inline int operator()(const matrix &v)const{
        std::hash<T> hasher;
        T seed(0);
        for(auto & it:v)
            for(auto & itt:it)
                seed ^= hasher(itt) + 0x933779b9 +(seed<<6) + (seed>>2);
        return seed;
    }
};
#endif //FIFTEENGAME_HASHES_CPP