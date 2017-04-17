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
#include <set>
#include <vector>
#include <unordered_map>
using namespace std;

class Tane{
public:
    int attrNum;
    Lattice lat;
    unordered_map<set<int>,set<int>>RHS;
    unordered_map<set<int>,int>FD;
    set<int>emptySet;
    set<int>R;
    
    Tane(int attrNumInput);
    void taneMain();
    void computeDependencies(int levelIndex);
    void prune(int levelIndex);
    
};

#endif /* Tane_hpp */
