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
#include <sstream>
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
    this->RHS.insert(make_pair(set2Str(this->emptySet), this->R));
    for(int i = 1; i <= this->attrNum; i++)
    {
        computeDependencies(i);
        prune(i);
    }
}

bool Tane::isRHSEmpty(set<int>X)
{
    set<int> result = this->RHS[set2Str(X)];
    if(result.empty())
    {
        return true;
    }
    return false;
}


string int2str(int int_temp)
{
    string result;
    stringstream stream;
    stream<<int_temp;
    result=stream.str();
    return result;
}

string Tane::set2Str(set<int>A)
{
    vector<int>tmp;
    string result;
    for(set<int>::iterator it = A.begin(); it != A.end(); it++)
    {
        tmp.push_back(*it);
    }
    for(int i = 0; i < tmp.size();i++)
    {
        result = result + ";" + int2str(tmp[i]);
    }

    return result;
}


void Tane::prune(int levelIndex)
{
    Level thisLevel = this->lat.levelList[levelIndex];
    for(vector<Node>::iterator it = thisLevel.elemSets.begin(); it != thisLevel.elemSets.end();it++)
    {
        Node tmpNode = *it;
        set<int> tmpSet = tmpNode.nodeElem;
        if(isRHSEmpty(tmpSet))
        {
            thisLevel.elemSets.erase(it);
            this->lat.levelList[levelIndex] = thisLevel;
        }
        if(isSuperkey(tmpSet))
        {
            set<int>toCheck = getComple(this->RHS[set2Str(tmpSet)],tmpSet);
            for(set<int>::iterator it2 = toCheck.begin(); it2 != toCheck.end(); it2++)
            {
                int A = *it2;
                set<int>Aset;
                Aset.insert(A);
                set<int>toInter;
                for(set<int>::iterator it3 = tmpSet.begin(); it3 != tmpSet.end(); it3++)
                {
                    int B = *it3;
                    set<int>Bset;
                    Bset.insert(B);
                    set<int>XA = getUnion(tmpSet,Aset);
                    set<int>LHS = getComple(XA,Bset);
                    set<int>thisRHS = this->RHS[set2Str(LHS)];
                    toInter = getInter(toInter,thisRHS);
                }
                set<int>::iterator it4 = toInter.find(A);
                if(it4 != toInter.end())
                {
//                    this->FD[tmpSet] = A;
                    this->FD.insert(make_pair(set2Str(tmpSet), A));
                }
                thisLevel.elemSets.erase(it);
                this->lat.levelList[levelIndex] = thisLevel;
            }
        }
    }
}

set<int> Tane::getInter(set<int>A,set<int>B)
{
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_intersection(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    return result;
}

set<int> Tane::getComple(set<int>A,set<int>B)
{
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_difference(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    return result;
}

set<int> Tane::getUnion(set<int>A,set<int>B)
{
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_union(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    return result;
}

bool isValid(set<int>A,int B)
{
    return false;
}

bool Tane::isSuperkey(set<int>X)
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
            set<int>rhsResult = this->RHS[set2Str(afterDelete)];
            tmpInter = getInter(tmpInter,rhsResult);
        }
        this->RHS.insert(make_pair(set2Str(tmpSet), tmpInter));
    }
    for(int i = 0; i < thisLevelSize;i++)
    {
        Node tmpNode = thisLevel.elemSets[i];
        set<int> tmpSet = tmpNode.nodeElem;
        set<int> tmpRHS = this->RHS[set2Str(tmpSet)];
        set<int> toTraverse = getInter(tmpSet,tmpRHS);
        
        for(set<int>::iterator it2 = toTraverse.begin(); it2 != toTraverse.end(); it2++)
        {
            set<int>afterDelete = tmpSet;
            afterDelete.erase(it2);
            if(isValid(afterDelete,*it2))
            {
                this->FD.insert(make_pair(set2Str(afterDelete), *it2));
                this->RHS[set2Str(tmpSet)].erase(it2);
                set<int>RdTmpSet = getComple(this->R,tmpSet);
                tmpRHS = this->RHS[set2Str(tmpSet)];
                set<int>afterRemove = getComple(tmpRHS, RdTmpSet);
                this->RHS[set2Str(tmpSet)] = afterRemove;
            }
        }
    }
}

