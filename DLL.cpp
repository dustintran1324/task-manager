//Duy Duc Tran
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;


DLL::DLL(){
    DNode *newNode = new DNode;
	first  = newNode;
    last = newNode;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

DLL::DLL(string t, int p, int h, int m){
	first = new DNode(t,p,h,m);
    last = NULL;
    numTasks = 1;
    tothrs = h;
    totmin = m;
}

DLL::~DLL(){
	DNode *tmp = first;
    while (tmp != NULL){
        first = tmp -> next;
        delete tmp;
        tmp = first;
    }
    last = NULL;
}
void DLL::push(string n, int p, int h, int m) {
    DNode *newNode = new DNode(n, p, h, m);
    DNode *current = last;

    if (numTasks == 0) {
        first = newNode;
        last = newNode;
    } else if (p == 3) {
        last->next = newNode;
        newNode->prev = last;
        newNode->next = NULL;
        last = newNode;

    } else {
        if (numTasks == 1) {
            if (first->task->priority > p) {
                last = first;
                first = newNode;
                last->prev = first;
                first->next = last;
            } else {
                last = newNode;
                last->prev = first;
                first->next = last;
            }
        } else {
            while ((current->task->priority > p) && current->prev != NULL) {
                current = current->prev;
            }
            if (current->task->priority == p) {
                if (current == last) {
                    current->next = newNode;
                    newNode->prev = current;
                    last = newNode;

                } else {
                    DNode *nextPrev = current->next;
                    current->next = newNode;
                    nextPrev->prev = newNode;
                    newNode->next = nextPrev;
                    newNode->prev = current;
                }
            } else if (current->task->priority > p) {
                first->prev = newNode;
                newNode->next = first;
                first = newNode;
            } else {
                if (current->next == NULL) {
                    current->next = newNode;
                    newNode->prev = current;
                    last = newNode;
                } else {
                    DNode *nextPrev = current->next;
                    current->next = newNode;
                    nextPrev->prev = newNode;
                    newNode->next = nextPrev;
                    newNode->prev = current;
                }

            }

        }
    }
    addTime(newNode->task->hr, newNode->task->min);
    numTasks++;
}
    Task *DLL::pop() {
        if (first != NULL) {
            first->prev = NULL;
        }
        Task *taskTmp = first->task;
        DNode *tmp;
        tmp = first->next;
        tmp->prev = NULL;
        first->next = NULL;
        first = tmp;
        //update the total time and numtask
        removeTime(taskTmp->hr, taskTmp->min);
        numTasks--;
        return taskTmp;
    }

int DLL::remove(int tn) {
        DNode *current = first;
        int taskNumtmp = -1;
        while (current != NULL) {
            if (current->task->tasknum == tn) {
                DNode *tmp = current;
                // if it is the first node
                if (current == first) {
                    first = current->next;
                    if (first != NULL) {
                        first->prev = NULL;
                    } else {
                        // If the list becomes empty after removal
                        last = NULL;
                    }
                } else {
                    // Task is not the first one, handle the removal
                    if (current->prev != NULL) {
                        current->prev->next = current->next;
                    }
                    if (current->next != NULL) {
                        current->next->prev = current->prev;
                    } else {
                        // If the task to be removed is the last one in the list
                        last = current->prev;
                    }
                }

                removeTime(current->task->hr, current->task->min);
                taskNumtmp = current->task->tasknum;
                delete tmp;

                numTasks -= 1;
                return taskNumtmp;
            }

            current = current->next;
        }

        return taskNumtmp;
    }


    void DLL::addTime(int h, int m) {
    tothrs += h;
    totmin += m;
    tothrs += totmin/60;
    totmin %= 60;
}

void DLL::removeTime(int h, int m) {
    tothrs -= h;
    if (m > totmin) {
        tothrs -= 1;
        totmin += 60;
    }
    totmin -= m;
}

void DLL::moveUp(int tn) {
    DNode* current = first;
    DNode* temp = nullptr;

    while (current != nullptr) {
        if (current->task->tasknum == tn) {
            if (current == first) {
                // Task is already at the beginning; move it to the end
                first = current->next;
                first->prev = nullptr;
                last->next = current;
                current->prev = last;
                last = current;
                current->next = nullptr;
                current->task->priority = current->prev->task->priority;
            }
            else if (current->prev->prev == nullptr) {
                // Task is moved up to the top of the list
                current->task->priority = current->prev->task->priority;
                temp = current->prev;
                current->prev = nullptr;
                temp->next = current->next;
                current->next->prev = temp;
                current->next = temp;
                temp->prev = current;
                first = current;
            }
            else if (current == last) {
                // Task is at the end of the list; move it to the beginning
                current->task->priority = current->prev->task->priority;
                temp = current->prev;
                temp->next = nullptr;
                current->prev = temp->prev;
                temp->prev->next = current;
                temp->prev = current;
                current->next = temp;
                last = temp;
            }
            else {
                // Task is moved up within the list
                current->task->priority = current->prev->task->priority;
                temp = current->prev;
                temp->prev->next = current;
                current->prev = temp->prev;
                temp->prev = current;
                temp->next = current->next;
                current->next->prev = temp;
                current->next = temp;
                if (temp->next != nullptr) {
                    temp->next->prev = temp;
                }
            }
        }
        current = current->next;
    }
}

void DLL::moveDown(int tn) {
    DNode* current = last;
    DNode* temp = NULL;

    while (current != NULL) {
        if (current->task->tasknum == tn) {
            if (current == last) {
                // Task is already at the end; move it to the beginning
                last = current->prev;
                last->next = NULL;
                first->prev = current;
                current->next = first;
                first = current;
                current->prev = NULL;
                current->task->priority = current->next->task->priority;
            }
            else if (current == first) {
                // Task is moved down to the beginning of the list
                current->task->priority = current->next->task->priority;
                temp = current->next;
                temp->prev = NULL;
                current->next = temp->next;
                temp->next->prev = current;
                temp->next = current;
                current->prev = temp;
                first = temp;
            }
            else if (current->next->next == NULL) {
                // Task is at 2nd to last move it to the end
                current->task->priority = current->prev->task->priority;
                temp = current->next;
                current->next = NULL;
                temp->prev = current->prev;
                current->prev->next = temp;
                current->prev = temp;
                temp->next = current;
                last = current;
            }
            else {
                // Task is moved down within the list
                current->task->priority = current->next->task->priority;
                temp = current->next;
                current->prev->next = temp;
                temp->prev = current->prev;
                current->prev = temp;
                current->next = temp->next;
                temp->next->prev = current;
                temp->next = current;
                if (temp->prev == NULL) {
                    first = temp;
                }
            }
        }
        current = current->prev;
    }
}

void DLL::changePriority(int tn, int newp) {
    DNode *current = first;

    while ((current != nullptr) && current->task->tasknum != newp) {

        if (current->task->tasknum == tn) {
            current->task->priority = newp;
            break;
        }
        current = current->next;
    }

    Task *temporary = new Task();
    temporary->task = current->task->task;
    temporary->priority = current->task->priority;
    temporary->hr = current->task->hr;
    temporary->min = current->task->min;
    tn = remove(current->task->tasknum);

    current = last;
    DNode *NewNode = new DNode(temporary->task, temporary->priority, temporary->hr, temporary->min);
    NewNode->task->tasknum = tn;
    int p = NewNode->task->priority;

    if (p == 3) {
        last->next = NewNode;
        NewNode->prev = last;
        last = NewNode;

    } else {
        if (numTasks == 1) {
            if (first->task->priority > p) {
                last = first;
                first = NewNode;
                last->prev = first;
                first->next = last;
            } else {
                last = NewNode;
                last->prev = first;
                first->next = last;
            }
        } else {
            while ((current->task->priority > p) && current->prev != nullptr) {
                current = current->prev;
            }
            if (current->task->priority == p) {
                if (current == last) {
                    current->next = NewNode;
                    NewNode->prev = current;
                    last = NewNode;

                } else {
                    DNode *nextPrev = current->next;
                    current->next = NewNode;
                    nextPrev->prev = NewNode;
                    NewNode->next = nextPrev;
                    NewNode->prev = current;
                }
            } else if (current->task->priority > p) {
                first->prev = NewNode;
                NewNode->next = first;
                first = NewNode;
            } else {
                if (current->next == nullptr) {
                    current->next = NewNode;
                    NewNode->prev = current;
                    last = NewNode;
                } else {
                    DNode *nextPrev = current->next;
                    current->next = NewNode;
                    nextPrev->prev = NewNode;
                    NewNode->next = nextPrev;
                    NewNode->prev = current;
                }

            }

        }
    }
    addTime(NewNode->task->hr, NewNode->task->min);
    numTasks++;
}


    void DLL::listDuration(int *th, int *tm,int tp) {
	DNode* current = first;
    while (current != NULL){
        if (current -> task -> priority == tp){
            *th += current ->task ->hr;
            *tm += current -> task -> min;
        }
        current = current -> next;
    }
    *th += *tm/60;
    *tm %= 60;
}

void DLL::printList() {
	DNode* current = first;
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    while (current != NULL){
         current -> task ->printTask();
         current = current -> next;
    }
    cout<<endl;
}

void DLL::printList(int p) {
    int ph = 0;
    int pm = 0;
    listDuration(&ph, &pm, p);
    DNode *current = first;
    cout << p << ": Total Time Required: " << ph << ":" << pm << endl;
    while (current != NULL) {
        if (current->task->priority == p) {
            current->task->printTask();
        }
        current = current -> next;
    }
    cout<<endl;
}
