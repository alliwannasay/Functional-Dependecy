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
//    vector<Node>preElemSets = preLevel.elemSets;
//    vector<Node>sndElemSets = sndLevel.elemSets;
//    for(auto t : preElemSets)
//    {
//        Node tmp = t;
//        for(auto sndt : sndElemSets)
//        {
//            int newElem = tmp.nodeElem | sndt.nodeElem;
//            if(newElem == tmp.nodeElem) continue;
//            Node newNode(this->attrNum,newElem);
//            if(this->isNodeIn(newNode) == true)
//            {
//                continue;
//            }
//            newNode.isSingle = false;
////            getPiProduct(newNode,tmp,sndt);
//            this->elemSets.push_back(newNode);
//        }
//    }


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

//bool Level::isNodeIn(Node& source)
//{
//    int srcNodeElem = source.nodeElem;
//    for(auto t : this->elemSets)
//    {
//        if(t.nodeElem == srcNodeElem)
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//int Level::getNodeIndex(int nodeElemIn)
//{
//    int thisSize = int(this->elemSets.size());
//    for(int i = 0; i < thisSize; i++)
//    {
//        if(this->elemSets[i].nodeElem == nodeElemIn)
//        {
//            return i;
//        }
//    }
//    return -1;
//}
//
//void Level::getPi(Node& target)
//{
//    if(target.isPi == true) return;
//    vector<vector<int>>tmpResVec;
//    unordered_map<string, vector<int>>tmpHash;
//    int tmpSum = 0;
//    vector<vector<string>>tmpTable = this->table.table;
//    int rowSize = int(tmpTable.size());
//    int targetElem = target.getSingle();
//    for(int i = 0; i < rowSize; i++)
//    {
//        string elemData = tmpTable[i][targetElem];
//        tmpHash[elemData].push_back(i);//注意这块不知道能否直接添加进map
//    }
//    for(auto it : tmpHash)
//    {
//        vector<int>itSec = it.second;
//        if(itSec.size() > 1)
//        {
//            tmpResVec.push_back(itSec);
//            tmpSum += itSec.size();
//        }
//    }
//    target.isPi = true;
//    target.pi = tmpResVec;
//    target.piSum = tmpSum;
//    return;
//}
//
//void Level::getPiProduct(Node& target, Node& A, Node& B)
//{
//    if(target.isPi == true) return;
//    vector<vector<int>>tmpResVec;
//    int sizeA = int(A.pi.size());
//    int sizeB = int(B.pi.size());
//    vector<int>T;
//    T.assign(this->table.table.size(), -1);//不知道assign能否直接开空间
//    vector<vector<int>>S;
//    vector<int>eptVec = vector<int>();
//    int tmpSum = 0;
//    for(int i = 0; i < sizeA; i++)
//    {
//        vector<int>c = A.pi[i];
//        for(auto it : c)
//        {
//            int t = it;
//            T[t] = i;
//        }
//        S.push_back(eptVec);
//    }
//    for(int i = 0; i < sizeB; i++)
//    {
//        vector<int>c = B.pi[i];
//        for(auto it : c)
//        {
//            int t = it;
//            if(T[t] >= 0)
//            {
//                S[T[t]].push_back(t);
//            }
//        }
//        for(auto it : c)
//        {
//            int t = it;
//            if(T[t] < 0) continue;
//            if(S[T[t]].size() >= 2)
//            {
//                tmpResVec.push_back(S[T[t]]);
//                tmpSum += S[T[t]].size();
//            }
//            S[T[t]] = eptVec;
//        }
//    }
//    target.pi = tmpResVec;
//    target.piSum = tmpSum;
//    target.isPi = true;
//}
