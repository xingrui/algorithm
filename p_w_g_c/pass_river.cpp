//============================================================================
// Name        : pass_river.cpp
// Author      : jason
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <map>
#include <queue>
using namespace std;
// Person Wolf Goat Cabbage use 0x8, 0x4, 0x2, 0x1 bit to repsents.
int safeStates[] = {0xF, 0x0, 0xE, 0x1, 0xD, 0x2, 0xB, 0x4, 0xA, 0x5};
int safeStateCount = sizeof(safeStates) / sizeof(int);
int shiftStates[] = {0xC, 0xA, 0x9, 0x8};
int shiftStateCount = sizeof(shiftStates) / sizeof(int);

void printState(int state)
{
	printf("(");
	if(state & 0x8) {
		printf("Person ");
	}
	if(state & 0x4) {
		printf("Wolf ");
	}
	if(state & 0x2) {
		printf("Goat ");
	}
	if(state & 0x1) {
		printf("Cabbage ");
	}
	printf(")");
}

int main() {
	int startState = 0xF;
	int destState = 0x0;
	set<int> safe_set(safeStates, safeStates + safeStateCount);
	for(set<int>::iterator it = safe_set.begin(); it != safe_set.end(); ++it)
	{
		// printState(*it);
	}
	map<int, int> searchedStateMap;
	queue<int> stateQueue;
	stateQueue.push(startState);
	while(!stateQueue.empty())
	{
		int state = stateQueue.front();
		stateQueue.pop();
		for(int i = 0; i < shiftStateCount; ++i)
		{
			int currentState = state ^ shiftStates[i];
			if(currentState == destState){
				printf("solution found\n");
				printState(currentState);
				printf("<=");
				int tmp = state;
				while(tmp != startState)
				{
					printState(tmp);
					printf("<=");
					tmp = searchedStateMap[tmp];
				}
				printState(startState);
				exit(0);
			}
			if(searchedStateMap.find(currentState) != searchedStateMap.end())
			{
				// printf("state has been searched, %X\n", currentState);
				continue;
			}
			if(safe_set.find(currentState) != safe_set.end()) {
				stateQueue.push(currentState);
				searchedStateMap[currentState] = state;
			}
		}
	}
	return 0;
}
