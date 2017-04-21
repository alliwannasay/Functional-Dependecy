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
    this->attrNum = 0;
    this->nodeElem = 0;
    this->rhs = 0;
    this->isSingle = false;
    this->isPi = false;
    this->piSum = 0;
}

Node::Node(int attrNumInput,int nodeElemInput)
{
    this->attrNum = attrNumInput;
    this->nodeElem = nodeElemInput;
    this->rhs = 0;
    this->isSingle = false;
    this->isPi = false;
    this->piSum = 0;
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

void Node::getVec(vector<int>& result)
{
    result.clear();
    int tmp = this->nodeElem;
    for (int i = 0; i < this->attrNum; i++)
    {
        if (tmp % 2 != 0)
        {
            result.push_back(i);
        }
        tmp >>= 1;
    }
}

int Node::getSingle()
{
    if(this->isSingle == false)
    {
        return -1;
    }
    int result = -1;
    int tmp = this->nodeElem;
    for (int i = 0; i < this->attrNum; i++)
    {
        if (tmp % 2 != 0)
        {
            result = i;
            break;
        }
        tmp >>= 1;
    }
    return result;
}

//void Node::getSubset(Node& targetA, Node&targetB, Node& source)
//{
//    int srcElem = source.nodeElem;
//    int srcSin = source.getSingle();
//    int remElem = srcElem & (~srcSin);
//    targetA.nodeElem = 
//}
