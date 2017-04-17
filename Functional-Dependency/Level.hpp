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
#include "Node.hpp"
using namespace std;


class Level{
private:
    int index;
    int attrNum;
public:
    vector<Node>elemSets;
public:
    int getIndex(){return index;}
    int getAttrNum(){return attrNum;}
    Level(int indexInput,int attrNumInput);
    Level update(Level preLevel);
    void initRoot();
};

#endif /* Level_hpp */
