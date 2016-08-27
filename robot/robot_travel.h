#ifndef _ROBOT_TRAVEL_H_
#define _ROBOT_TRAVEL_H_

class robotTravel {

private:
	int speed;
	int direction;
	int travelStatus;

	bool setSpeed( int speed );
	bool setDirection( int direction );
	bool setTravelStatus(int travelStatus);

public:
	robotTravel();
	~robotTravel();
	int getSpeed();
	int getDirection();
	int getTravelStatus();
	bool init();
	bool doTravel( int direction, int speed );

};

#endif // _ROBOT_TRAVEL_H_
