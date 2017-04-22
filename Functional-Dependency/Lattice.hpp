//
//  Lattice.hpp
//  FD
//
//  Created by zzqmyos on 17/4/17.
//
//

#ifndef Lattice_hpp
#define Lattice_hpp

#include "Level.hpp"
#include "Table.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <utility>
using namespace std;

class Lattice{
public:
    int attrNum;
    Table table;
    vector<Level>levelList;
    
    Lattice();
    Lattice(Table& tableIn);
    Lattice(int attrNumInput,Table& tableIn);
};

#endif /* Lattice_hpp */
