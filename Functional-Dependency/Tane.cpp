//
//  Tane.cpp
//  FD
//
//  Created by zzqmyos on 17/4/16.
//
//

#include "Tane.hpp"
#include "Level.hpp"
#include "Lattice.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

Tane::Tane(int attrNumInput)
{
    this->attrNum = attrNumInput;
    this->lat = Lattice(attrNumInput);
    for(int i = 0; i < attrNumInput; i++)
    {
        this->R.insert(i);
    }
}

void Tane::taneMain()
{
    this->RHS.insert(make_pair(this->emptySet, this->R));
    for(int i = 1; i <= this->attrNum; i++)
    {
        computeDependencies(i);
        prune(i);
    }
}

void Tane::prune(int levelIndex)
{
    
}

set<int> getInter(set<int>A,set<int>B)
{
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_intersection(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    return result;
}

set<int> getComple(set<int>A,set<int>B)
{
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_difference(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    return result;
}

bool isValid(set<int>A,int B)
{
    return false;
}

void Tane::computeDependencies(int levelIndex)
{
    Level thisLevel = this->lat.levelList[levelIndex];
    int thisLevelSize = int(thisLevel.elemSets.size());
    for(int i = 0; i < thisLevelSize; i++)
    {
        Node tmpNode = thisLevel.elemSets[i];
        set<int> tmpSet = tmpNode.nodeElem;
        set<int> tmpInter;
        for(set<int>::iterator it=tmpSet.begin(); it != tmpSet.end(); it++)
        {
            set<int>afterDelete = tmpSet;
            afterDelete.erase(it);
            set<int>rhsResult = this->RHS[afterDelete];
            tmpInter = getInter(tmpInter,rhsResult);
        }
        this->RHS.insert(make_pair(tmpSet, tmpInter))
    }
    for(int i = 0; i < thisLevelSize;i++)
    {
        Node tmpNode = thisLevel.elemSets[i];
        set<int> tmpSet = tmpNode.nodeElem;
        set<int> tmpRHS = this->RHS[tmpSet];
        set<int> toTraverse = getInter(tmpSet,tmpRHS);
        
        for(set<int>::iterator it2 = toTraverse.begin(); it2 != toTraverse.end(); it2++)
        {
            set<int>afterDelete = tmpSet;
            afterDelete.erase(it2);
            if(isValid(afterDelete,*it2))
            {
                this->FD.insert(make_pair(afterDelete, *it2));
                this->RHS[tmpSet].erase(it2);
                set<int>RdTmpSet = getComple(this->R,tmpSet);
                tmpRHS = this->RHS[tmpSet];
                set<int>afterRemove = getComple(tmpRHS, RdTmpSet);
                this->RHS[tmpSet] = afterRemove;
            }
        }
    }
}
