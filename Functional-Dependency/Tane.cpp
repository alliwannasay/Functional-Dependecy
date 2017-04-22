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
    this->isPi = new bool[this->all];
    memset(this->pi, 0, this->all * sizeof(vector<vector<int>>));
    memset(this->piSum, 0, this->all * sizeof(int));
    memset(this->RHS,0,this->all * sizeof(int));
    memset(isPi, 0, this->all * sizeof(bool));
    vector<vector<int>>ept;
    pi[0] = ept;
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
    }
    
}

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
                int CX_A = RHS[X_A];
                C_X &= CX_A;
            }
            tmpX >>= 1;
        }
        RHS[X] = C_X;
        
        int Inter = X & RHS[X];
        int tmpI = Inter;
        for(int a = 0; a < this->attrNum; a++)
        {
            if(tmpI % 2 != 0)
            {
                int A = (1 << a);
                int X_A = X & (~A);
                if(!(X_A == 0 || X == 0))
                {
                    int piX_A = piCalculator(X_A);
                    int piX = piProductCalculator(X_A, A);
                    if(piSum[X_A] - piX_A == piSum[X] - piX)
                    {
                        FD.insert(make_pair(X_A,A));
                        int C_X = RHS[X];
                        C_X = C_X & (~A);
                        int R_X = (this->all - 1) & (~X);
                        C_X = C_X & (~R_X);
                        RHS[X] = C_X;
                    }
                }
            }
            tmpI >>= 1;
        }
    }
    
}



int Tane::piCalculator(int A)
{
    if(A == 0) return 0;
    if(isPi[A]==true) return pi[A].size();
    unordered_map<string, vector<int>>resVec;
    vector<vector<int>>result;
    int tmpA = A;
    int res = 0;
    int sum = 0;
    for(int a = 0;  a < this->attrNum; a++)
    {
        if(tmpA % 2 != 0)
        {
            res = a;
            break;
        }
        tmpA >>= 1;
    }
    
    int tableSize = this->table.table.size();
    for(int i = 0; i < tableSize; i++)
    {
        string elemData = this->table.table[i][res];
        resVec[elemData].push_back(i);
    }
    int resSize = resVec.size();
    for(auto vec : resVec)
    {
        if(vec.second.size() > 1)
        {
            result.push_back(vec.second);
            sum += vec.second.size();
        }
    }
    pi[A] = result;
    piSum[A] = sum;
    isPi[A] = true;
    return pi[A].size();
}

int Tane::piProductCalculator(int A,int B)
{
    int C = A | B;
    if(A == 0 || B == 0) return 0;
    if(isPi[C]==true) return pi[C].size();
    vector<vector<int>>result;
    int sizeA = pi[A].size();
    int sizeB = pi[B].size();
    vector<int>T;
    vector<vector<int>>S;
    vector<int>ept;
    int sum = 0;
    T.assign(this->table.table.size(),-1);
    S.resize(sizeA+sizeB);
    for(int i = 0; i < sizeA;i++)
    {
        vector<int>c = pi[A][i];
        for(auto t : c)
        {
            T[t] = i;
        }
        S[i] = ept;
    }
    for(int i = 0; i < sizeB; i++)
    {
        vector<int>c = pi[B][i];
        for(auto t : c)
        {
            if(T[t] >= 0)
            {
                S[T[t]].push_back(t);
            }
        }
        for(auto t : c)
        {
            if(T[t] < 0) continue;
            if(S[T[t]].size() >= 2)
            {
                result.push_back(S[T[t]]);
                sum += S[T[t]].size();
            }
            S[T[t]] = ept;
        }

    }
    pi[C] = result;
    piSum[C] = sum;
    isPi[C]=true;
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
