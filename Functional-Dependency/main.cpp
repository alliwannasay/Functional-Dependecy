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
    Tane thistane("//Users//zzqmyos//Functional-Dependency//Functional-Dependency//test_data.txt");
    thistane.taneMain();
    thistane.outputFile("//Users//zzqmyos//Functional-Dependency//Functional-Dependency//my_test_output.txt");
    return 0;
}
