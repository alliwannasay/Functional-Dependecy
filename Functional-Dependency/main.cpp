//
//  Main.cpp
//  FD
//
//  Created by zzqmyos on 17/4/17.
//
//

#include "Lattice.hpp"
#include "Tane.hpp"
#include "Table.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

int main()
{
    Tane thistane;
//    thistane.singlePartition(0);
    int a[]= {20,10,30};
    int b[]= {};
    set<int>setA(a,a+3);
    set<int>setB(b,b);
    string result = thistane.set2Str(setA);
    set<int>res = thistane.str2Set(result);
    thistane.singlePartition(0);
//    thistane.singlePartition(0);
    
    
//    int a[]= {10,20};
//    int b[]= {};
//    set<int>setA(a,a+2);
//    set<int>setB(b,b);
//    set<int>result = thistane.getUnion(setA, setB);
//    Table testtable;
//    testtable.readIn("//Users//zzqmyos//Functional-Dependency//Functional-Dependency//test_data.txt");
    return 0;
}
