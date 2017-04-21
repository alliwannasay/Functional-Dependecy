//
//  Lattice.cpp
//  FD
//
//  Created by zzqmyos on 17/4/17.
//
//

#include "Level.hpp"
#include "Lattice.hpp"
#include <iostream>
#include <set>
#include <vector>
using namespace std;

Lattice::Lattice(int attrNumInput,Table& tableIn)
{
    this->attrNum = attrNumInput;
    Level firstLevel(0,attrNumInput,tableIn);
    this->levelList.resize(attrNumInput+1,firstLevel);
    firstLevel.initRoot();
    this->levelList[0] = firstLevel;
    Level sndLevel(1,attrNumInput,tableIn);
    sndLevel.initSnd();
    this->levelList[1] = sndLevel;
}

Lattice::Lattice(Table& tableIn)
{
    this->attrNum = 0;
    Level firstLevel(0,0,tableIn);
    firstLevel.initRoot();
    this->levelList.push_back(firstLevel);
}

Lattice::Lattice()
{
    this->attrNum = 0;
}
