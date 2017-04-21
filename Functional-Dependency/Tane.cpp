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
    this->lat = Lattice(attrNumInput,this->table);
    this->all = (1 << attrNumInput) - 1;
    this->tsum = 0;
}

void Tane::taneMain()
{
    this->lat.levelList[0].elemSets[0].nodeElem = this->all;
    for(int i = 1; i <= this->attrNum; i++)
    {
        
        this->lat.levelList[i].update(this->lat.levelList[i-1]);
        computeDependencies(i);
        prune(i);
        
    }
    
}

bool Tane::isRHSEmpty(set<int>&X)
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


set<int> Tane::str2Set(string s)
{
    
    vector<string>resVec = this->table.divideByChar(s,',');
    set<int>result;
    int vecSize = int(resVec.size());
    for(int i = 0; i < vecSize; i++)
    {
        int tmp = atoi(resVec[i].c_str());
        result.insert(tmp);
    }
    
    return result;
}

string Tane::set2Str(set<int>&A)
{
    
    if(A.size() == 0) return "";
    vector<int>tmp;
    string result;
    for(set<int>::iterator it = A.begin(); it != A.end(); it++)
    {
        tmp.push_back(*it);
    }
    result = int2str(tmp[0]);
    for(int i = 1; i < tmp.size();i++)
    {
        result = result + "," + int2str(tmp[i]);
    }
    
    return result;
}

void Tane::calculatePartition(set<int>&A)
{
    if(A.size() == 0) return;
    for(set<int>::iterator it = A.begin(); it != A.end(); it++)
    {
        singlePartition(*it);
        set<int>sin;
        sin.insert(*it);
        set<int>tmp = A;
        tmp.erase(*it);
        if(this->par[set2Str(tmp)].size() == 0)
        {
            calculatePartition(tmp);
        }
        productPartition(this->par[set2Str(tmp)], this->par[set2Str(sin)], tmp, sin);
    }
}

void Tane::prune(int levelIndex)
{
    Level thisLevel = this->lat.levelList[levelIndex];
    int thisSize = int(thisLevel.elemSets.size());
    for(int i = 0; i < thisSize; i++)
    {
        Node tmpNode = thisLevel.elemSets[i];
        set<int> tmpSet = tmpNode.nodeElem;
        if(isRHSEmpty(tmpSet))
        {
            vector<Node>::iterator it = find(thisLevel.elemSets.begin(),thisLevel.elemSets.end(),tmpNode);
            thisLevel.elemSets.erase(it);
            this->lat.levelList[levelIndex] = thisLevel;
        }
    }
}

set<int> Tane::getInter(set<int>&A,set<int>&B)
{
    startClock();
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_intersection(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    endClock();
    return result;
}

set<int> Tane::getComple(set<int>&A,set<int>&B)
{
    startClock();
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_difference(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    endClock();
    return result;
    
}

set<int> Tane::getUnion(set<int>&A,set<int>&B)
{
    startClock();
    vector<int>tmp;
    tmp.resize(A.size()+B.size());
    vector<int>::iterator it = set_union(A.begin(),A.end(),B.begin(),B.end(),tmp.begin());
    tmp.resize(it-tmp.begin());
    set<int>result(tmp.begin(),tmp.end());
    endClock();
    return result;
}

bool Tane::isValid(set<int>&A,int B)
{
    
    if(this->par[set2Str(A)].size() == 0)
    {
        calculatePartition(A);
    }
    vector<set<int>>piA = this->par[set2Str(A)];
    set<int>setB;
    setB.insert(B);
    if(this->par[set2Str(setB)].size() == 0)
    {
        calculatePartition(setB);
    }
    set<int>setAB = getUnion(A,setB);
    if(this->par[set2Str(setAB)].size() == 0)
    {
        productPartition(this->par[set2Str(A)], this->par[set2Str(setB)], A, setB);
    }
    vector<set<int>>piAB = this->par[set2Str(setAB)];
    
    if(this->parSum[set2Str(A)]-piA.size() == this->parSum[set2Str(setAB)]-piAB.size())
    {
        return true;
    }
    
    return false;
}


bool Tane::isSuperkey(set<int>&X)
{
    if(this->par[set2Str(X)].size() == 0)
    {
        calculatePartition(X);
    }
    vector<set<int>>piRes = this->par[set2Str(X)];
    if(piRes.size() == this->table.table.size())
    {
        return true;
    }
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
        set<int> tmpInter = this->R;
        for(set<int>::iterator it=tmpSet.begin(); it != tmpSet.end(); it++)
        {
            set<int>afterDelete = tmpSet;
            afterDelete.erase(*it);
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
            afterDelete.erase(*it2);
            if(afterDelete.size() == 0) continue;
            
            
            if(isValid(afterDelete,*it2))
            {
                this->FD.push_back(make_pair(set2Str(afterDelete), *it2));
                this->RHS[set2Str(tmpSet)].erase(*it2);
                set<int>RdTmpSet = getComple(this->R,tmpSet);
                tmpRHS = this->RHS[set2Str(tmpSet)];
                set<int>afterRemove = getComple(tmpRHS, RdTmpSet);
                this->RHS[set2Str(tmpSet)] = afterRemove;
            }
            
        }
    }
    
}

void Tane::singlePartition(int index)
{
    unordered_map<string, set<int>>pi;
    vector<vector<string>>tmpTable = this->table.table;
    int rowSize = int(tmpTable.size());
    int sum = 0;
    for(int i = 0; i < rowSize; i++)
    {
        string elemData = tmpTable[i][index];
        set<int> tmpSet = pi[elemData];
        tmpSet.insert(i);
        pi[elemData] = tmpSet;
    }
    vector<set<int>>piVec;
    
    for(unordered_map<string, set<int>>::iterator it = pi.begin(); it != pi.end(); it++)
    {
        if((*it).second.size() > 1)
        {
            piVec.push_back((*it).second);
            sum += (*it).second.size();
        }
    }
    set<int>indexSet;
    indexSet.insert(index);
    this->par[set2Str(indexSet)] = piVec;
    this->parSum[set2Str(indexSet)] = sum;
    return;
}

void Tane::productPartition(vector<set<int>>&A,vector<set<int>>&B,set<int>&setA,set<int>&setB)
{
    
    if(setA.size() == 0 || setB.size() == 0) return;
    vector<set<int>>result;
    int sizeA = int(A.size());
    int sizeB = int(B.size());
    vector<int>T;
    T.resize(this->table.table.size());
    T.assign(this->table.table.size(), -1);
    vector<set<int>>S;
    S.resize(this->table.table.size());
    int sum = 0;
    for(int i = 0; i < sizeA; i++)
    {
        set<int>c = A[i];
        for(set<int>::iterator it = c.begin(); it != c.end(); it++)
        {
            int t = *it;
            T[t] = i;
        }
        S[i] = this->emptySet;
    }
    for(int i = 0; i < sizeB; i++)
    {
        set<int>c = B[i];
        for(set<int>::iterator it = c.begin(); it != c.end(); it++)
        {
            int t = *it;
            set<int>tSet;
            tSet.insert(t);
            if(T[t] >= 0)
            {
                S[T[t]].insert(t);
            }
        }
        for(set<int>::iterator it = c.begin(); it != c.end(); it++)
        {
            int t = *it;
            if(T[t] < 0) continue;
            if(S[T[t]].size() >= 2)
            {
                result.push_back(S[T[t]]);
                sum += S[T[t]].size();
            }
            S[T[t]] = this->emptySet;
        }
    }
    set<int>C = getUnion(setA, setB);
    this->par[set2Str(C)] = result;
    this->parSum[set2Str(C)] = sum;
    
}

void Tane::outputFile(string filename)
{
    ofstream fout(filename);
    vector<string>result;
    int sizeFD = int(this->FD.size());
    for(int i = 0; i < sizeFD; i++)
    {
        string A = "";
        set<int>left = str2Set(FD[i].first);
        for(set<int>::iterator itj = left.begin(); itj != left.end(); itj++)
        {
            A = A+int2str(*itj+1)+" ";
        }
        A = A+"-> "+int2str(FD[i].second+1)+"\n";
        result.push_back(A);
    }
    sort(result.begin(),result.end());
    int resSize = int(result.size());
    for(int i = 0; i < resSize; i++)
    {
        fout<<result[i];
    }
}
