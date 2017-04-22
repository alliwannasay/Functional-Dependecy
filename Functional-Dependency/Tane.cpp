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
#include <algorithm>
using namespace std;

void Tane::startClock()
{
    this->begin = clock();
}

void Tane::endClock()
{
    this->end = clock();
    this->tsum += this->end - this->begin;
}


Tane::Tane(string filename)
{
    this->table.readIn(filename);
    int attrNumInput = this->table.attrNum;
    this->attrNum = attrNumInput;
    this->all = (1 << attrNumInput);
    this->tsum = 0;
    this->pi = new vector<vector<int>>[this->all];
    this->piSum = new int[this->all];
    this->RHS = new int[this->all];
    memset(this->pi, 0, this->all * sizeof(vector<vector<int>>));
    memset(this->piSum, 0, this->all * sizeof(int));
    memset(this->RHS,0,this->all * sizeof(int));
    vector<vector<int>>ept;
    pi[0] = ept;;
}

void Tane::taneMain()
{
    vector<Level>levellist;
    this->RHS[0] = this->all - 1;
    for(int i = 0; i <= this->attrNum; i++)
    {
        Level newLevel(i, this->attrNum);
        if(i > 1)
        {
            newLevel.update(levellist[i-1]);
        }
        levellist.push_back(newLevel);
        computeDependencies(levellist[i]);
        if(i == 12)
        {
            int a = 0;
        }
    }
    
}

//void Tane::prune(int levelIndex)
//{
//    Level thisLevel = this->lat.levelList[levelIndex];
//    int thisSize = int(thisLevel.elemSets.size());
//    for(int i = 0; i < thisSize; i++)
//    {
//        Node tmpNode = thisLevel.elemSets[i];
//        set<int> tmpSet = tmpNode.nodeElem;
//        if(isRHSEmpty(tmpSet))
//        {
//            vector<Node>::iterator it = find(thisLevel.elemSets.begin(),thisLevel.elemSets.end(),tmpNode);
//            thisLevel.elemSets.erase(it);
//            this->lat.levelList[levelIndex] = thisLevel;
//        }
//    }
//}

void Tane::computeDependencies(Level& level)
{
    for(auto X : level.elemSets)
    {
        int C_X = this->all - 1;
        int tmpX = X;
        for(int a = 0; a < this->attrNum; a++)
        {
            if(tmpX % 2 != 0)
            {
                int A = (1 << a);
                int X_A = X & (~A);
                C_X = C_X & this->RHS[X_A];
            }
            tmpX >>= 1;
        }
        RHS[X] = C_X;
    }
    for(auto X : level.elemSets)
    {
        int inter = X & RHS[X];
        int tmpI = inter;
        for(int a = 0; a < this->attrNum; a++)
        {
            if(tmpI % 2 != 0)
            {
                int A = (1 << a);
                int X_A = X & (~A);
                if(!(X_A == 0 || X == 0))
                {
                    
                    int X_AS = piCalculator(X_A);
                    int XS = piProductCalculator(X_A,A);
                    if(piSum[X_A] - X_AS == piSum[X] - XS)
                    {
                        FD.insert(make_pair(X_A, A));
                        int C_X = RHS[X];
                        C_X = C_X & (~A);
                        int R_X = (this->all-1) & (~X);
                        C_X = C_X & (~R_X);
                        RHS[X] = C_X;
                    }
                }
            }
            tmpI >>= 1;
        }
    }
}

//void Tane::computeDependencies(Level& l) {
//    set<int>::iterator it, begin, end;
//    int x, tmpA, flag, shiftTmp, res, e, m, comple, tmpB, tmpE1, tmpE2;
//    
//    begin = l.elemSets.begin();
//    end = l.elemSets.end();
//    
//    it = begin;
//    while (it != end) {
//        // for each X in L
//        x = *it;
//        tmpA = 1;
//        
//        flag = 0;
//        shiftTmp = (1 << attrNum);
//        res = shiftTmp - 1;
//        
//        // RHS+(X) := InterRHS+(X\{E})
//        for (int i = 0; i < attrNum; ++i) {
//            if (x & tmpA) {
//                e = x - tmpA;
//                res = res & RHS[e];
//            }
//            tmpA <<= 1;
//        }
//        RHS[x] = res;
//        
//        // foreach E belongs to X intersect RHS+(X) do
//        tmpA = 1;
//        m = x & RHS[x];
//        for (int i = 0; i < attrNum; ++i) {
//            if (m & tmpA) {
//                // if X\{E} -> E is valid
//                piCalculator(x - tmpA);
//                piProductCalculator(x - tmpA, tmpA);
//                tmpE1 = pi[x - tmpA].size();
//                tmpE2 = pi[x].size();
//                if (piSum[x - tmpA] - tmpE1 == piSum[x] - tmpE2) {
//                    FD.insert(make_pair(x - tmpA, tmpA));
//                    // remove E for RHS+(X)
//                    RHS[x] -= tmpA;
//                    // remove all F belongs to R\X from RHS+(X)
//                    comple = (shiftTmp - 1) - x;
//                    tmpB = 1;
//                    for (int j = 0; j < attrNum; ++j) {
//                        if (comple & tmpB) {
//                            if (RHS[x] & tmpB) {
//                                RHS[x] -= tmpB;
//                            }
//                        }
//                        tmpB <<= 1;
//                    }
//                }
//            }
//            tmpA <<= 1;
//        }
//        
//        // if RHS+(X) == empty do
//        if (RHS[x] == 0) {
//            l.elemSets.erase(it++);
//        } else {
//            ++it;
//        }
//    }
//}


int Tane::piCalculator(int A)
{
    if(A == 0) return 0;
    if(pi[A].size() != 0) return pi[A].size();
    vector<vector<int>>tmpResVec;
    unordered_map<string, vector<int>>tmpHash;
    int tmpSum = 0;
    vector<vector<string>>tmpTable = this->table.table;
    int rowSize = int(tmpTable.size());
    int targetElem = 0;
    int tmpA = A;
    for(int i = 0; i < attrNum;i++)
    {
        if(tmpA % 2 != 0)
        {
            targetElem = i;
            break;
        }
        tmpA >>= 1;
    }
    
    for(int i = 0; i < rowSize; i++)
    {
        string elemData = tmpTable[i][targetElem];
        tmpHash[elemData].push_back(i);
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
    pi[A] = tmpResVec;
    piSum[A] = tmpSum;
    return pi[A].size();
}


int Tane::piProductCalculator(int A,int B)
{
    if(pi[A + B].size() != 0) return pi[A + B].size();
    if(A == 0 || B == 0) return 0;
    vector<vector<int>>tmpResVec;
    int sizeA = int(pi[A].size());
    int sizeB = int(pi[B].size());
    vector<int>T;
    T.assign(this->table.table.size(), -1);
    vector<vector<int>>S;
    vector<int>eptVec = vector<int>();
    int tmpSum = 0;
    for(int i = 0; i < sizeA; i++)
    {
        vector<int>c = pi[A][i];
        for(auto it : c)
        {
            int t = it;
            T[t] = i;
        }
        S.push_back(eptVec);
    }
    for(int i = 0; i < sizeB; i++)
    {
        vector<int>c = pi[B][i];
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
    int C = A + B;
    pi[C] = tmpResVec;
    piSum[C] = tmpSum;
    return pi[C].size();
}



Tane::~Tane()
{
    delete [] pi;
    delete [] piSum;
    delete [] RHS;
}

string int2str(int int_temp)
{
    string result;
    stringstream stream;
    stream<<int_temp;
    result=stream.str();
    return result;
}


void Tane::outputFile(string filename)
{
    ofstream fout(filename);
    vector<string>result;
    int sizeFD = int(this->FD.size());
    for(set<pair<int,int>>::iterator its = FD.begin(); its != FD.end(); its++)
    {
        string A = "";
        int left = (*its).first;
        vector<int>res;
        int2Vec(left,res);
        for(vector<int>::iterator itj = res.begin(); itj != res.end(); itj++)
        {
            A = A+int2str(*itj+1)+" ";
        }
        vector<int>res2;
        int2Vec((*its).second,res2);
        A = A+"-> "+int2str(res2[0]+1)+"\n";
        result.push_back(A);
    }
    sort(result.begin(),result.end());
    int resSize = int(result.size());
    for(int i = 0; i < resSize; i++)
    {
        fout<<result[i];
    }
}

void Tane::int2Vec(int x, vector<int>&res)
{
    int tmp;
    tmp = 1;
    for (int i = 0; i < attrNum; ++i) {
        if (x & tmp) {
            res.push_back(i);
        }
        tmp <<= 1;
    }
}
