//
//  Level.hpp
//  FD
//
//  Created by zzqmyos on 17/4/16.
//
//

#ifndef Level_hpp
#define Level_hpp

#include <iostream>
#include <set>
#include <vector>
#include "Table.hpp"
using namespace std;


class Level{
public:
    int index;
    int attrNum;
    int elemNum;
    set<int>elemSets;

    Level(int indexInput,int attrNumInput);
    void update(Level& preLevel);
    void initRoot();
    void initSnd();
};

#endif /* Level_hpp */
