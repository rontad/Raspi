#ifndef _ROBOT_STATUS_H_
#define _ROBOT_STATUS_H_

class robotStaus {

private:
	int runningStatus;
	int travelStatus;

public:
	robotStaus();
	~robotStaus();
	int getRunningStatus();
	int getTravelStatus();
	void doRunSystem();
	bool doStopSystem();

};

#endif // _ROBOT_STATUS_H_
