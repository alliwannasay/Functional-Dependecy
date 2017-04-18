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

void Lattice::cascadeDelete(int levelNum, int loc)
{
    if(levelNum == 2 && loc == 2)
    {
        int p = 0;
    }
    Level tmpLevel = this->levelList[levelNum];
    if(tmpLevel.elemSets[loc].nodeElem.size() == 0) return;
    Node tmpNode = tmpLevel.elemSets[loc];
    Level nextLevel = this->levelList[levelNum+1];
    for(int i = 0; i < tmpNode.downPnt.size();i++)
    {
        if(levelNum < this->attrNum)
        {
            Node nextNode = nextLevel.elemSets[tmpNode.downPnt[i]];
            if(nextNode.upPnt.size() == 1 && nextNode.upPnt[0] == loc)
            {
                cascadeDelete(levelNum+1,tmpNode.downPnt[i]);
                vector<int>::iterator itp = find(tmpNode.downPnt.begin(),tmpNode.downPnt.end(),tmpNode.downPnt[i]);
                tmpNode.downPnt.erase(itp);
            }
            else
            {
                vector<int>::iterator ito = find(nextNode.upPnt.begin(),nextNode.upPnt.end(),loc);
                nextNode.upPnt.erase(ito);
                nextLevel.elemSets[tmpNode.downPnt[i]] = nextNode;
            }
            
        }
    }
    this->levelList[levelNum+1] = nextLevel;
    vector<Node>::iterator it = find(tmpLevel.elemSets.begin(),tmpLevel.elemSets.end(),tmpNode);
    tmpLevel.elemSets.erase(it);
    this->levelList[levelNum] = tmpLevel;
}
