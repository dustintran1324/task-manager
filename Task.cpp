
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Task.hpp"

using namespace std;

Task::Task(string t, int p, int h, int m) {
	tasknum = rand()%900+100;
	task = t;
	priority = p;
	hr = h;
	min = m;
}
Task::Task() {
	tasknum = 0;
	task="";
	priority = 3;
	hr = 0;
	min = 0;
}
void Task::printTask() {
	cout << "(" << tasknum << ") " << task << ", " << priority <<"................";
	cout << hr << ":" << setw(2) << setfill('0') << min;
	cout << endl;
}
