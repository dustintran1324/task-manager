/*
 * DNode.cpp
 *
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */
//Duy Duc Tran
#include <cstdlib>
#include <iostream>
#include "DNode.hpp"
using namespace std;
DNode::DNode() {
    task = new Task();
    prev = NULL;
    next = NULL;
}
DNode::DNode(string t, int p, int h, int m){
    task = new Task(t,p,h,m);
    prev = NULL;
    next = NULL;
}
DNode::~DNode(){
    delete task;
}
/* write your constructors here! */

