/*

Elevator project 2 part C
Travis Pratt
This program takes an elevator scenario and divides up the work between several elevators or process it through 1 elevator.

*/

#include "stdafx.h"
#include <vector>
#include <iostream>
#include "elevator.h"

using namespace std;

int main()
{
	elevator El;
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
	}

	system("pause");
	return 0;
}

