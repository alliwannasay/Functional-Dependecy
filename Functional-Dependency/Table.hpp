//
//  Table.hpp
//  Functional-Dependency
//
//  Created by zzqmyos on 17/4/18.
//  Copyright © 2017年 zzqmyos. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Table{
public:
    vector<vector<string>>table;
    int attrNum;
    
    void readIn(string filename);
    vector<string> divideByChar(string s, char ch);
};

#endif /* Table_hpp */
