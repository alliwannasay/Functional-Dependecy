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
#include <ctime>
using namespace std;

int main()
{
    time_t begin, end;
    begin = clock();
    
    Tane thistane("//Users//zzqmyos//Functional-Dependency//Functional-Dependency//test_data.txt");
    thistane.taneMain();
    thistane.outputFile("//Users//zzqmyos//Functional-Dependency//Functional-Dependency//my_test_output.txt");
    
    end = clock();
    cout << "Runtime : " << double(end - begin) / CLOCKS_PER_SEC << endl;
    cout << "============================================" << endl;
    
    cout << "Validation Runtime : " << double(thistane.tsum) / CLOCKS_PER_SEC << endl;
    cout << "============================================" << endl;
    return 0;
}
