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
    this->index = indexInput;
    this->attrNum = attrNumInput;
}

Level Level::update(Level preLevel)
{
    this->index = preLevel.index + 1;
    int preElemNum = int(preLevel.elemSets.size());
    for(int i = 0; i < preElemNum; i++)
    {
        Node tmp = preLevel.elemSets[i];
        for(int j = 0; j < this->attrNum; j++)
        {
            set<int>::iterator it = tmp.nodeElem.find(j);
            if(it == tmp.nodeElem.end())
            {
                Node newTmp;
                newTmp.nodeElem = tmp.nodeElem;
                newTmp.nodeElem.insert(j);
                newTmp.upPnt.push_back(i);
                
                vector<Node>::iterator itv = find(this->elemSets.begin(),this->elemSets.end(),newTmp);
                if(itv == this->elemSets.end())
                {
                    this->elemSets.push_back(newTmp);
                    preLevel.elemSets[i].downPnt.push_back(int(this->elemSets.size()) - 1);
                }
                else
                {
                    this->elemSets[itv-(this->elemSets.begin())].upPnt.push_back(i);
                    preLevel.elemSets[i].downPnt.push_back(int(itv-(this->elemSets.begin())));
                }
                
            }
        }
    }
    return preLevel;
}

void Level::initRoot()
{
    this->index = 0;
    Node rootElem;
    this->elemSets.push_back(rootElem);
}
