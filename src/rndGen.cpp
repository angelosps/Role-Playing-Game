/* file: rndGen.cpp */

#include "../include/rndGen.hpp"

RndGen::RndGen(int a, int b) : min(a), max(b) {}

int RndGen::getNum() {
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(this->min, this->max);
    return distrib(gen);
} 
