#pragma once
#include <vector>
class elevator
{
public:
	elevator();
	//wrapper function for addReq.
	void addRequest(int num, int direction);
	void addBttn(int num, int elevatorNum);
	void runElevator();
	void addElevator(int pos);
	std::vector<int> getElevatorPos();
	void moveElevator();
	// checks to see if there are still requests
	bool isRequests();
private:
	//adds the request to the right vector based on direction.
	void addReq(int num, std::vector<int>& req);
	//code needed to sort vectors for ease of use.
	void sortReq(std::vector<int>& req);
	void mergeSort(std::vector<int>& array);
	void mergesort(std::vector<int>& array, std::vector<int>& result, int lowerBand, int upperBand);
	void merge(std::vector<int>& array, std::vector<int>& result, int lowPointer, int highPointer, int upperBound);
	//private functions that hold the requests of the elevator
	std::vector<std::vector<int>> bttnPress;
	std::vector<int> requestsUp;
	std::vector<int> requestsDown;
	// elevator attributes
	std::vector<int> elevatorPos;
	void moveDown(int elevatorNum);
	void moveUp(int elevatorNum);
	int bestElevator(int request);
	void checkElevator(bool direction, int floor, int elevatorNum);
	// contains headings of every elevator in the scenario where true equals up and false equals down and null equals stationary
	std::vector<bool> eDirection;
	// checks the requests for the current floor.
	void checkRequests(std::vector<int>& req, int target,int elevatorNum);

};

