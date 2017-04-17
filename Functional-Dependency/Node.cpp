//
//  Node.cpp
//  FD
//
//  Created by zzqmyos on 17/4/16.
//
//

#include "Node.hpp"
#include <iostream>
#include <set>
#include <vector>
using namespace std;

Node::Node()
{
    
}

bool Node::operator == (Node &nodeInput)
{
    if(this->nodeElem == nodeInput.nodeElem)
    {
        return true;
    }
    return false;
}

bool Node::operator == (const Node &nodeInput)
{
    if(this->nodeElem == nodeInput.nodeElem)
    {
        return true;
    }
    return false;
}
