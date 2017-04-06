#include "stdafx.h"
#include "elevator.h"
#include <vector>
#include <iostream>
#include <omp.h>

using namespace std;

elevator::elevator()
{
}
void elevator::addElevator(int pos)
{
	elevatorPos.push_back(pos);
	eDirection.push_back(NULL);
}

bool elevator::isRequests()
{
	if (!requestsDown.empty() || !requestsUp.empty() || !bttnPress.empty())
		return true;
	else
		return false;
}

vector<int> elevator::getElevatorPos()
{
	return elevatorPos;
}
//checks whether requests are on the same floor and removes them then triggers a button event.
void elevator::checkRequests(vector<int>& req, int target, int elevatorNum)
{
	for (int i = 0; i < req.size(); i++)
	{
		if (req[i] == target)
		{
			req.erase(req.begin() + i);
			i--;
			cout << "Person has entered the elevator.\n";
			addBttn(rand() % 5 + 1,elevatorNum);
		}
	}
}
// checks and removes requests from requests up or down depending on which way the elevator is going
void elevator::checkElevator(bool direction,int floor,int elevatorNum)
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
// moves the elevator based on where it needs to go and updates the direction the elevator is heading.
void elevator::moveElevator()
{
	if (!bttnPress.empty())
	{
		if (bttnPress[0][0] < elevatorPos[bttnPress[0][1]])
		{
			eDirection[bttnPress[0][1]] = false;
			moveDown(bttnPress[0][1]);
		}
		if (bttnPress[0][0] > elevatorPos[bttnPress[0][1]])
		{
			eDirection[bttnPress[0][1]] = true;
			moveUp(bttnPress[0][1]);	
		}
		if (bttnPress[0][0] == elevatorPos[bttnPress[0][1]])
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
			if (elevatorPos[elevatorNum] > requestsDown[0])
			{
				eDirection[elevatorNum] = false;
				moveDown(elevatorNum);
			}
			if (elevatorPos[elevatorNum] < requestsDown[0])
			{
				eDirection[elevatorNum] = true;
				moveUp(elevatorNum);
			}
			if (elevatorPos[elevatorNum] == requestsDown[0])
			{
				eDirection[elevatorNum] = NULL;
				requestsDown.erase(requestsDown.begin());
				cout << "person(s) got on the elevator.\n";
				addBttn(rand() % 5 + 1, elevatorNum);
			}
		}
		if (!requestsUp.empty())
		{
			int elevatorNum = bestElevator(requestsUp[0]);
			if (elevatorPos[elevatorNum] > requestsUp[0])
			{
				eDirection[elevatorNum] = false;
				moveDown(elevatorNum);
			}
			if (elevatorPos[elevatorNum] < requestsUp[0])
			{
				eDirection[elevatorNum] = true;
				moveUp(elevatorNum);
			}
			if (elevatorPos[elevatorNum] == requestsUp[0])
			{
				eDirection[elevatorNum] = NULL;
				requestsUp.erase(requestsUp.begin());
				cout << "person(s) got on the elevator.\n";
				addBttn(rand() % 5 + 1, elevatorNum);
			}
		}
	}
}
// chooses the closest elevator to send to the request.
int elevator::bestElevator(int request)
{
	if (elevatorPos.size() > 1)
	{
		// locks the variable to keep from bad information with multiple writes
		omp_lock_t writelock;
		omp_init_lock(&writelock);
		int best = 0;
		int floors = 999999;
		#pragma omp parallel shared(best,elevatorPos,request) for
		{
			for (int i = 0; i < elevatorPos.size(); i++)
			{
				if (abs(elevatorPos[i] - request) < floors)
				{
					omp_set_lock(&writelock);
					best = i;
					floors = abs(elevatorPos[i] - request);
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
//initializes the elevators in the system.
void elevator::runElevator()
{
	int elevatorNum;
	cout << "please enter in amount of elevators you would like to start with: ";
	cin >> elevatorNum;
	for (int i = 0; i < elevatorNum; i++)
	{
		int floor = 0;
		while (floor < 1 || floor > 5)
		{
			cout << "Please enter in a valid elevator start floor from 1 to 5: ";
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
void elevator::addBttn(int num, int elevatorNum)
{
	vector<int> bttn = {num, elevatorNum};
	bttnPress.push_back(bttn);
}
//wrapper function for addReq
void elevator::addRequest(int num, int direction)
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
void elevator::addReq(int num, vector<int>& req)
{
	req.push_back(num);
	sortReq(req);
}
//wrapper for the merge sort function
void elevator::sortReq(vector<int>& req)
{
	mergeSort(req);
}
//Kuhails merge sort program modified with parallelism
void elevator::merge(std::vector<int>& array, std::vector<int>& result, int lowPointer, int highPointer, int upperBound) {

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

void elevator::mergesort(std::vector<int>& array, std::vector<int>& result, int lowerBand, int upperBand) {
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

void elevator::mergeSort(std::vector<int>& array){
	std::vector<int> result = array;
	mergesort(array, result, 0, array.size() - 1);
}
//end of merge sort functions

// movement functions for elevator
void elevator::moveDown(int elevatorNum)
{
	cout << "Elevator " << elevatorNum << " moved down to " << elevatorPos[elevatorNum]-- << "\n";
}
void elevator::moveUp(int elevatorNum)
{
	cout << "Elevator " << elevatorNum << " moved up to " << elevatorPos[elevatorNum]++ << "\n";
}
