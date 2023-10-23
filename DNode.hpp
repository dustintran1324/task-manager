#ifndef DNODE_HPP_
#define DNODE_HPP_
#include <cstdlib>
using namespace std;

#include "Task.hpp"

class DNode {
	friend class DLL;
	Task *task;
	DNode *prev;
	DNode *next;
public:
	DNode(); // empty constructor, sets all variables to default NULL value
	DNode(string t, int p, int lenhr, int lenmin); // node containing a task with the given parameters, sets variables to appropriate values
    ~DNode();
};



#endif /* DNODE_HPP_ */
