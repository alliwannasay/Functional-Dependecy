//
//  Node.hpp
//  FD
//
//  Created by zzqmyos on 17/4/16.
//
//

#ifndef Node_hpp
#define Node_hpp

#include <iostream>
#include <set>
#include <vector>
#include "Table.hpp"
using namespace std;

class Node{
public:
    int attrNum;
    int nodeElem;
    int rhs;
    bool isSingle;
    bool isPi;
    int piSum;
    vector<vector<int>>pi;
    
    Node();
    Node(int attrNumInput,int nodeElemInput);
    void getVec(vector<int>& result);
    int getSingle();
//    void getSubset(Node& targetA, Node&targetB, Node& source);
    bool operator == (Node& nodeInput);
    bool operator == (const Node& nodeInput);
    
};

#endif /* Node_hpp */
