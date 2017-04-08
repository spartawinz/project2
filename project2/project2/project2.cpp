/*

Elevator project 2 part C
Travis Pratt
This program takes an elevator scenario and divides up the work between several elevators or process it through 1 elevator.

*/

#include "stdafx.h"
#include <vector>
#include <iostream>
#include "Elevator.h"

using namespace std;

int main()
{
	Elevator El;
	El.runElevator();
	vector<int> elPos = El.getElevatorPos();
	for (int i = 0; i < 5; i++)
	{
		El.addRequest(rand() % 5 + 1, rand() % 2);
	}
	while (El.isRequests())
	{
		cout << "\nElevator Standings.\n";
		cout << "#1 " << elPos[0] << "  #2 " << elPos[1] << "  #3 " << elPos[2] << "  #4 " << elPos[3] << "  #5 " << elPos[4] << "\n\n";
		El.moveElevator();
		elPos = El.getElevatorPos();
	}

	El.addRequest(rand() % 5 + 1, rand() % 2);
	El.addRequest(rand() % 5 + 1, rand() % 2);
	El.addRequest(rand() % 5 + 1, rand() % 2);
	El.addRequest(rand() % 5 + 1, rand() % 2);

	El.moveElevator();
	El.moveElevator();
	El.moveElevator();

	elPos = El.getElevatorPos();

	cout << "\nElevator Standings.\n";
	cout << "#1 " << elPos[0] << "  #2 " << elPos[1] << "  #3 " << elPos[2] << "  #4 " << elPos[3] << "  #5 " << elPos[4] << "\n\n";

	El.moveElevator();
	El.addRequest(rand() % 5 + 1, rand() % 2);
	El.addRequest(rand() % 5 + 1, rand() % 2);
	El.moveElevator();

	elPos = El.getElevatorPos();

	cout << "\nElevator Standings.\n";
	cout << "#1 " << elPos[0] << "  #2 " << elPos[1] << "  #3 " << elPos[2] << "  #4 " << elPos[3] << "  #5 " << elPos[4] << "\n\n";
	
	El.moveElevator();

	elPos = El.getElevatorPos();

	while (El.isRequests())
	{
		cout << "\nElevator Standings.\n";
		cout << "#1 " << elPos[0] << "  #2 " << elPos[1] << "  #3 " << elPos[2] << "  #4 " << elPos[3] << "  #5 " << elPos[4] << "\n\n";
		El.moveElevator();
		elPos = El.getElevatorPos();
	}
	cout << "\nElevator Standings.\n";
	cout << "#1 " << elPos[0] << "  #2 " << elPos[1] << "  #3 " << elPos[2] << "  #4 " << elPos[3] << "  #5 " << elPos[4] << "\n\n";

	if (!El.isRequests())
	{
		cout << "\nThere is no requests remaining. \n\n";
		cout << "The time the elevator has spent on the move is: " << El.getFloorTime() << " Seconds\n\n";
	}
	// even though the heuristic for time spent with the elevator is kinda skewed since its not taking into account simultaneous running of each elevator
	// it still shows that time is reduced by using the least amount of movements of the elevators.

	system("pause");
	return 0;
}

