//
//  Main.cpp
//  FD
//
//  Created by zzqmyos on 17/4/17.
//
//

#include "Lattice.hpp"
#include "Tane.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

int main()
{
    Tane thistane(4);
    int a[]= {40,20};
    int b[]= {};
    set<int>setA(a,a+2);
    set<int>setB(b,b);
    string result = thistane.set2Str(setA);
//    int a[]= {10,20};
//    int b[]= {};
//    set<int>setA(a,a+2);
//    set<int>setB(b,b);
//    set<int>result = thistane.getUnion(setA, setB);
    return 0;
}
