
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TaskManager.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	TaskManager *list = new TaskManager("/Users/dustintran13/CLionProjects/DLLTaskManager/ListofTasks.txt");
}

