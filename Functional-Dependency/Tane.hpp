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
    int* RHS;
    vector<vector<int>>* pi;
    int* piSum;
    set<pair<int,int>>FD;
    Table table;
    int all;
    bool* isPi;

    time_t tsum;
    time_t begin;
    time_t end;
    
    Tane(string filename);
    ~Tane();
    void taneMain();
    void computeDependencies(Level& level);
    int piCalculator(int A);
    int piProductCalculator(int A,int B);
    void outputFile(string filename);
    void int2Vec(int x, vector<int>&res);
    void startClock();
    void endClock();
};

#endif /* Tane_hpp */
