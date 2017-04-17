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
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Tane{
public:
    int attrNum;
    Lattice lat;
    unordered_map<string,set<int>>RHS;
    unordered_map<string,int>FD;
    set<int>emptySet;
    set<int>R;
    
    Tane(int attrNumInput);
    void taneMain();
    void computeDependencies(int levelIndex);
    void prune(int levelIndex);
    bool isRHSEmpty(set<int>X);
    bool isSuperkey(set<int>X);
    set<int> getInter(set<int>A,set<int>B);
    set<int> getComple(set<int>A,set<int>B);
    set<int> getUnion(set<int>A,set<int>B);
    string set2Str(set<int>A);
    
};

#endif /* Tane_hpp */
