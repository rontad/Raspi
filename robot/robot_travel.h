#ifndef _ROBOT_TRAVEL_H_
#define _ROBOT_TRAVEL_H_

#define MOTOR_RIGHT_OUT1 14
#define MOTOR_RIGHT_OUT2 15
#define MOTOR_RIGHT_PWM 18
#define MOTOR_LEFT_OUT1 5
#define MOTOR_LEFT_OUT2 6
#define MOTOR_LEFT_PWM 13
#define POW_HIGH 1024
#define POW_LOW 300

enum eDirection
{
    FORWARD        = 1,
    BACK           = 2,
    STOP           = 3,
    LEFT_FORWARD   = 4,
    RIGHT_FORWARD  = 5,
    LEFT_BACK      = 6,
    RIGHT_BACK     = 7,
    LEFT_TURN      = 8,
    RIGHT_TURN     = 9,
};

class robotTravel {

private:
	int speed;
	eDirection edirection;
	int travelStatus;

	bool setSpeed( int speed );
	bool setDirection( eDirection edirection );
	bool setTravelStatus(int travelStatus);

public:
	robotTravel();
	~robotTravel();
	int getSpeed();
	eDirection getDirection();
	int getTravelStatus();
	bool init();
	bool doTravel( int direction, int speed );

};

#endif // _ROBOT_TRAVEL_H_
