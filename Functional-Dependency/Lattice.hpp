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
#include <iostream>
#include <set>
#include <vector>
using namespace std;

class Lattice{
public:
    int attrNum;
    vector<Level>levelList;
    
    Lattice();
    Lattice(int attrNumInput);
};

#endif /* Lattice_hpp */
