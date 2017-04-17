//
//  Level.cpp
//  FD
//
//  Created by zzqmyos on 17/4/16.
//
//

#include "Level.hpp"
#include "Node.hpp"
#include <iostream>
#include <set>
#include <vector>
using namespace std;

Level::Level(int indexInput,int attrNumInput)
{
    this.index = indexInput;
    this.attrNum = attrNumInput;
}

void Level::update(Level preLevel)
{
    this.index = preLevel.index + 1;
    int preElemNum = int(preLevel.elemSets.size());
    for(int i = 0; i < preElemNum; i++)
    {
        Node = preLevel.elemSets[i];
        for(int j = 1; j <= this.attrNum; j++)
        {
            set<int>::iterator it = tmp.nodeElem.find(j);
            if(it != tmp.nodeElem.end())
            {
                Node newTmp(tmp);
                newTmp.nodeElem.insert(j);
                newTmp.upPnt = i;
                this.elemSets.insert(newTmp);
                tmp.downPnt = this.elemSets.size() - 1;
            }
        }
    }
}

void Level::initRoot()
{
    this.index = 0;
    Node rootElem;
    this.elemSets.insert(rootElem);
}
