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
#include <string>
#include <unordered_map>
using namespace std;

Level::Level(int indexInput,int attrNumInput,Table& tableIn)
{
    this->index = indexInput;
    this->attrNum = attrNumInput;
    this->table = tableIn;
}

void Level::update(Level& preLevel,Level& sndLevel)
{
    this->index = preLevel.index + 1;
    this->attrNum = preLevel.attrNum;
    set<Node>preElemSets = preLevel.elemSets;
    set<Node>sndElemSets = sndLevel.elemSets;
    for(auto t : preElemSets)
    {
        Node tmp = t;
        for(auto sndt : sndElemSets)
        {
            int newElem = tmp.nodeElem | sndt.nodeElem;
            Node newNode(this->attrNum,newElem);
            if(this->isNodeIn(newNode) == true)
            {
                continue;
            }
            if(preLevel.index == 0)
            {
                newNode.isSingle = true;
                getPi(newNode);
            }
            else
            {
                newNode.isSingle = false;
                getPiProduct(newNode,tmp,sndt);
            }
            this->elemSets.insert(newNode);
        }
    }
}

void Level::initRoot()
{
    this->index = 0;
    Node rootElem(this->attrNum,0);
    rootElem.isSingle = false;
    rootElem.isPi = true;
    rootElem.piSum = 0;
    this->elemSets.insert(rootElem);
}

void Level::initSnd()
{
    this->index = 1;
    for(int j = 0; j < this->attrNum; j++)
    {
        Node newNode(this->attrNum,j);
        newNode.isSingle = true;
        getPi(newNode);
        this->elemSets.insert(newNode);
    }
}

bool Level::isNodeIn(Node& source)
{
    int srcNodeElem = source.nodeElem;
    for(auto t : this->elemSets)
    {
        if(t.nodeElem == srcNodeElem)
        {
            return true;
        }
    }
    return false;
}

void Level::getPi(Node& target)
{
    if(target.isPi == true) return;
    vector<vector<int>>tmpResVec;
    unordered_map<string, vector<int>>tmpHash;
    int tmpSum = 0;
    vector<vector<string>>tmpTable = this->table.table;
    int rowSize = int(tmpTable.size());
    int targetElem = target.getSingle();
    for(int i = 0; i < rowSize; i++)
    {
        string elemData = tmpTable[i][targetElem];
        tmpHash[elemData].push_back(i);//注意这块不知道能否直接添加进map
    }
    for(auto it : tmpHash)
    {
        vector<int>itSec = it.second;
        if(itSec.size() > 1)
        {
            tmpResVec.push_back(itSec);
            tmpSum += itSec.size();
        }
    }
    target.isPi = true;
    target.pi = tmpResVec;
    target.piSum = tmpSum;
    return;
}

void Level::getPiProduct(Node& target, Node& A, Node& B)
{
    if(target.isPi == true) return;
    vector<vector<int>>tmpResVec;
    int sizeA = int(A.pi.size());
    int sizeB = int(B.pi.size());
    vector<int>T;
    T.assign(this->table.table.size(), -1);//不知道assign能否直接开空间
    vector<vector<int>>S;
    vector<int>eptVec = vector<int>();
    int tmpSum = 0;
    for(int i = 0; i < sizeA; i++)
    {
        vector<int>c = A.pi[i];
        for(auto it : c)
        {
            int t = it;
            T[t] = i;
        }
        S.push_back(eptVec);
    }
    for(int i = 0; i < sizeB; i++)
    {
        vector<int>c = B.pi[i];
        for(auto it : c)
        {
            int t = it;
            if(T[t] >= 0)
            {
                S[T[t]].push_back(t);
            }
        }
        for(auto it : c)
        {
            int t = it;
            if(T[t] < 0) continue;
            if(S[T[t]].size() >= 2)
            {
                tmpResVec.push_back(S[T[t]]);
                tmpSum += S[T[t]].size();
            }
            S[T[t]] = eptVec;
        }
    }
    target.pi = tmpResVec;
    target.piSum = tmpSum;
    target.isPi = true;
}
