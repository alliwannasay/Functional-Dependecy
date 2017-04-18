//
//  Table.cpp
//  Functional-Dependency
//
//  Created by zzqmyos on 17/4/18.
//  Copyright © 2017年 zzqmyos. All rights reserved.
//

#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

void Table::readIn(string filename)
{
    ifstream fs(filename);
    if (!fs)
    {
        cout<<"No file!"<<endl;
    }
    while(true)
    {
        string tmp;
        getline(fs,tmp);
        vector<string>vecTmp = divideByChar(tmp,',');
        if(this->attrNum == 0) this->attrNum = int(vecTmp.size());
        if(vecTmp.size() == 0)
        {
            break;
        }
        this->table.push_back(vecTmp);
    }
}

vector<string> Table::divideByChar(string s, char ch)
{
    vector<string>v;
    string::size_type pos1, pos2;
    pos2 = s.find(ch);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        
        pos1 = pos2 + 1;
        pos2 = s.find(ch, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}