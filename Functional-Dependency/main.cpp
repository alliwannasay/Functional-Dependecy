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
    
    Tane thistane("data.txt");
    thistane.taneMain();
    thistane.outputFile("output.txt");
    
    end = clock();
    cout << "Time " << double(end - begin) / CLOCKS_PER_SEC << endl;
    cout << "Total Dependencies  " << thistane.FD.size() << endl;
    return 0;
}
