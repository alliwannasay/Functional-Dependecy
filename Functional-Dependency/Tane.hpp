//
//  Tane.hpp
//  FD
//
//  Created by zzqmyos on 17/4/16.
//
//

#ifndef Tane_hpp
#define Tane_hpp

#include "Level.hpp"
#include "Lattice.hpp"
#include "Table.hpp"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <ctime>
using namespace std;

class Tane{
public:
    int attrNum;
    Lattice lat;
    unordered_map<string,set<int>>RHS;
    vector<pair<string,int>>FD;
    unordered_map<string,vector<set<int>>>par;
    unordered_map<string, int>parSum;
    set<int>emptySet;
    set<int>R;
    Table table;
    time_t tsum;
    time_t begin;
    time_t end;
    
    Tane(string filename);
    void taneMain();
    void computeDependencies(int levelIndex);
    void prune(int levelIndex);
    bool isRHSEmpty(set<int>&X);
    bool isSuperkey(set<int>&X);
    bool isValid(set<int>&A,int B);
    set<int> getInter(set<int>&A,set<int>&B);
    set<int> getComple(set<int>&A,set<int>&B);
    set<int> getUnion(set<int>&A,set<int>&B);
    string set2Str(set<int>&A);
    set<int> str2Set(string s);
    void singlePartition(int index);
    void calculatePartition(set<int>&A);
    void productPartition(vector<set<int>>&A,vector<set<int>>&B,set<int>&setA,set<int>&setB);
    void outputFile(string filename);
    void startClock();
    void endClock();
};

#endif /* Tane_hpp */
