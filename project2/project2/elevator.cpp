#include "stdafx.h"
#include "elevator.h"
#include <vector>
#include <iostream>
#include <omp.h>

using namespace std;

Elevator::Elevator()
{
}
void Elevator::addElevator(int pos)
{
	ElevatorPos.push_back(pos);
	eDirection.push_back(NULL);
}

bool Elevator::isRequests()
{
	if (!requestsDown.empty() || !requestsUp.empty() || !bttnPress.empty())
		return true;
	else
		return false;
}

vector<int> Elevator::getElevatorPos()
{
	return ElevatorPos;
}

int Elevator::getFloorTime()
{
	return floorTime;
}
//checks whether requests are on the same floor and removes them then triggers a button event.
void Elevator::checkRequests(vector<int>& req, int target, int elevatorNum)
{
	for (int i = 0; i < req.size(); i++)
	{
		if (req[i] == target)
		{
			req.erase(req.begin() + i);
			i--;
			cout << "Person has entered the Elevator.\n";
			addBttn(rand() % 5 + 1,elevatorNum);
		}
	}
}
// checks and removes requests from requests up or down depending on which way the Elevator is going
void Elevator::checkElevator(bool direction,int floor,int elevatorNum)
{
	if (direction == true && !requestsUp.empty())
	{
		checkRequests(requestsUp, floor, elevatorNum);
	}
	else
	{
		if (direction == false && !requestsDown.empty())
		{
			checkRequests(requestsDown, floor, elevatorNum);
		}
	}
}
// moves the Elevator based on where it needs to go and updates the direction the Elevator is heading.
void Elevator::moveElevator()
{
	if (!bttnPress.empty())
	{
		if (bttnPress[0][0] < ElevatorPos[bttnPress[0][1]])
		{
			eDirection[bttnPress[0][1]] = false;
			moveDown(bttnPress[0][1]);
		}
		if (bttnPress[0][0] > ElevatorPos[bttnPress[0][1]])
		{
			eDirection[bttnPress[0][1]] = true;
			moveUp(bttnPress[0][1]);	
		}
		if (bttnPress[0][0] == ElevatorPos[bttnPress[0][1]])
		{
			eDirection[bttnPress[0][1]] = NULL;
			bttnPress.erase(bttnPress.begin());
			cout << "Person(s) got off/on at this floor.\n";
		}
	}
	else
	{
		if (!requestsDown.empty())
		{
			int elevatorNum = bestElevator(requestsDown[0]);
			if (ElevatorPos[elevatorNum] > requestsDown[0])
			{
				eDirection[elevatorNum] = false;
				moveDown(elevatorNum);
			}
			if (ElevatorPos[elevatorNum] < requestsDown[0])
			{
				eDirection[elevatorNum] = true;
				moveUp(elevatorNum);
			}
			if (ElevatorPos[elevatorNum] == requestsDown[0])
			{
				eDirection[elevatorNum] = NULL;
				requestsDown.erase(requestsDown.begin());
				cout << "person(s) got on the Elevator.\n";
				addBttn(rand() % 5 + 1, elevatorNum);
			}
		}
		if (!requestsUp.empty())
		{
			int elevatorNum = bestElevator(requestsUp[0]);
			if (ElevatorPos[elevatorNum] > requestsUp[0])
			{
				eDirection[elevatorNum] = false;
				moveDown(elevatorNum);
			}
			if (ElevatorPos[elevatorNum] < requestsUp[0])
			{
				eDirection[elevatorNum] = true;
				moveUp(elevatorNum);
			}
			if (ElevatorPos[elevatorNum] == requestsUp[0])
			{
				eDirection[elevatorNum] = NULL;
				requestsUp.erase(requestsUp.begin());
				cout << "person(s) got on the Elevator.\n";
				addBttn(rand() % 5 + 1, elevatorNum);
			}
		}
	}
}
// chooses the closest Elevator to send to the request.
int Elevator::bestElevator(int request)
{
	if (ElevatorPos.size() > 1)
	{
		// locks the variable to keep from bad information with multiple writes
		omp_lock_t writelock;
		omp_init_lock(&writelock);
		int best = 0;
		int floors = 999999;
		#pragma omp parallel shared(best,ElevatorPos,request) for
		{
			for (int i = 0; i < ElevatorPos.size(); i++)
			{
				if (abs(ElevatorPos[i] - request) < floors)
				{
					omp_set_lock(&writelock);
					best = i;
					floors = abs(ElevatorPos[i] - request);
					omp_unset_lock(&writelock);
				}
			}
		}
		return best;
	}
	else
	{
		return 0;
	}
}
//initializes the Elevators in the system.
void Elevator::runElevator()
{
	int elevatorNum;
	cout << "please enter in amount of Elevators you would like to start with: ";
	cin >> elevatorNum;
	for (int i = 0; i < elevatorNum; i++)
	{
		int floor = 0;
		while (floor < 1 || floor > 5)
		{
			cout << "Please enter in a valid Elevator start floor from 1 to 5: ";
			cin >> floor;

			if (floor < 1 || floor > 5)
			{
				cout << "invalid floor.\n";
				floor = 0;
			}
		}
		addElevator(floor);
	}
	
}
//adds a button press to bttnPress vector
void Elevator::addBttn(int num, int elevatorNum)
{
	vector<int> bttn = {num, elevatorNum};
	bttnPress.push_back(bttn);
}
//wrapper function for addReq
void Elevator::addRequest(int num, int direction)
{
	if (direction == 0)
		addReq(num, requestsDown);
	if (direction == 1)
		addReq(num, requestsUp);
	if (direction != 1 && direction != 0)
	{
		cout << "Invalid direction.";
	}

}
//automatically references the request vector so that the user doesn't have to
void Elevator::addReq(int num, vector<int>& req)
{
	req.push_back(num);
	sortReq(req);
}
//wrapper for the merge sort function
void Elevator::sortReq(vector<int>& req)
{
	mergeSort(req);
}
//Kuhails merge sort program modified with parallelism
void Elevator::merge(std::vector<int>& array, std::vector<int>& result, int lowPointer, int highPointer, int upperBound) {

	int j = 0;
	int lowerBound = lowPointer;
	int mid = highPointer - 1;
	int n = upperBound - lowerBound + 1; //number of items

	while (lowPointer <= mid && highPointer <= upperBound){

		if (array[lowPointer] < array[highPointer])
			result[j++] = array[lowPointer++];
		else
			result[j++] = array[highPointer++];
	}

	while (lowPointer <= mid)
		result[j++] = array[lowPointer++];


	while (highPointer <= upperBound)
		result[j++] = array[highPointer++];


	for (j = 0; j < n; j++) //copy the items from the temporary array to the original array
		array[lowerBound + j] = result[j];
}

void Elevator::mergesort(std::vector<int>& array, std::vector<int>& result, int lowerBand, int upperBand) {
	int midpoint;
	if (lowerBand < upperBand) {
		midpoint = (lowerBand + upperBand) / 2;
		//splits the 2 and sorts each side of the array using parallelism
		omp_set_num_threads(4);
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergesort(array, result, lowerBand, midpoint); //merge sort the left half
			}
			#pragma omp section
			{
				mergesort(array, result, midpoint + 1, upperBand); //merge sort the right half
			}
		}

		merge(array, result, lowerBand, midpoint + 1, upperBand);
	}
}

void Elevator::mergeSort(std::vector<int>& array){
	std::vector<int> result = array;
	mergesort(array, result, 0, array.size() - 1);
}
//end of merge sort functions

// movement functions for Elevator
void Elevator::moveDown(int elevatorNum)
{
	cout << "Elevator " << elevatorNum << " moved down to " << ElevatorPos[elevatorNum]-- << "\n";
	floorTime += 3;
}
void Elevator::moveUp(int elevatorNum)
{
	cout << "Elevator " << elevatorNum << " moved up to " << ElevatorPos[elevatorNum]++ << "\n";
	floorTime += 3;
}


