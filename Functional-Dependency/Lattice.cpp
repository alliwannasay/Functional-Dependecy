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

Lattice::Lattice(int attrNumInput)
{
    this->attrNum = attrNumInput;
    Level firstLevel(0,attrNumInput);
    firstLevel.initRoot();
    this->levelList.push_back(firstLevel);
    Level preLevel = firstLevel;
    
    for(int i = 1; i <= attrNumInput; i++)
    {
        Level tmp(i,attrNumInput);
        preLevel = tmp.update(preLevel);
        
        this->levelList.pop_back();
        this->levelList.push_back(preLevel);
        this->levelList.push_back(tmp);
        preLevel = tmp;
    }
}

Lattice::Lattice()
{
    this->attrNum = 0;
    Level firstLevel(0,0);
    firstLevel.initRoot();
    this->levelList.push_back(firstLevel);
}
