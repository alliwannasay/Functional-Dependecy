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
#include "Table.hpp"
using namespace std;


class Level{
public:
    int index;
    int attrNum;
    Table table;
    set<Node>elemSets;

    Level(int indexInput,int attrNumInput,Table& tableIn);
    void update(Level& preLevel,Level&sndLevel);
    void initRoot();
    void initSnd();
    void getPi(Node& target);
    void getPiProduct(Node& target, Node& A, Node& B);
    void isInLevel(Node& source);
    bool isNodeIn(Node& source);
};

#endif /* Level_hpp */
