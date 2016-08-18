#include <iostream>
#include "robot_status.h"

using namespace std;

robotStaus::robotStaus(){

	runningStatus = 0;
	travelStatus = 0;
}

robotStaus::~robotStaus(){

}

int robotStaus::getRunningStatus(){

	return runningStatus;
	
}

int robotStaus::getTravelStatus(){
	
	return travelStatus;
}

void robotStaus::doStartSystem(){

	if( getRunningStatus() == 1 ) {

		cout << "I've been already started." << endl;
		return;
	}

	

}

bool robotStaus::doStopSystem(){
	return 0;
}
