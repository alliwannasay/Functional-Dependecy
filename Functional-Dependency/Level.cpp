//
//  Level.cpp
//  FD
//
//  Created by zzqmyos on 17/4/16.
//
//

#include "Level.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

Level::Level(int indexInput,int attrNumInput)
{
    this->index = indexInput;
    this->attrNum = attrNumInput;
    if(indexInput == 0) this->initRoot();
    if(indexInput == 1) this->initSnd();
}

void Level::update(Level& preLevel)
{
    this->index = preLevel.index + 1;
    this->attrNum = preLevel.attrNum;
    set<int>::iterator itb = preLevel.elemSets.begin();
    set<int>::iterator ite = preLevel.elemSets.end();
    set<int>::iterator it;
    for(it = itb; it !=  ite; it++)
    {
        int tmpSingle = 1;
        int tmpPre = *it;
        for(int j = 0; j < this->attrNum; j++)
        {
            int tmpNew = tmpSingle | tmpPre;
            if(tmpNew == tmpPre) continue;
            this->elemSets.insert(tmpNew);
            tmpSingle <<= 1;
        }
    }
}

void Level::initRoot()
{
    this->index = 0;
    this->elemSets.insert(0);
}

void Level::initSnd()
{
    this->index = 1;
    for(int j = 0; j < this->attrNum; j++)
    {
        this->elemSets.insert((1 << j));
    }
}
