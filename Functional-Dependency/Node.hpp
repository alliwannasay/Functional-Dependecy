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
using namespace std;

class Node{
public:
    set<int>nodeElem;
    vector<int> downPnt;
    vector<int> upPnt;
    
    Node();
    bool operator == (Node& nodeInput);
    bool operator == (const Node& nodeInput);
    
};

#endif /* Node_hpp */
