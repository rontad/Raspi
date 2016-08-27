#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include "robot_travel.h"

using namespace std;

#define STR(var) #var

robotTravel::robotTravel(){

	speed = 0;
	edirection = STOP;
	travelStatus = 0;
}

robotTravel::~robotTravel(){

}

int robotTravel::getSpeed(){

	return speed;
	
}

bool robotTravel::setSpeed( int speed ){

	if( speed < 0 || speed > 100 ) {
		cout << "Specified speed is not valid.(" << speed << ")" << endl;
		return false;
	}

	this->speed = speed;
	return true;	
}

bool robotTravel::setDirection( eDirection edirection ){

	if( edirection < 1 || edirection > 9 ) {
		cout << "Specified direction is not valid.(" << edirection << ")" << endl;
		return false;
	}

	this->edirection = edirection;
	return true;	
}

bool robotTravel::setTravelStatus( int travelStatus ){

	if( travelStatus < 0 || travelStatus > 1 ) {
		cout << "Specified travelStatus is not valid.(" << travelStatus << ")" << endl;
		return false;
	}

	this->travelStatus = travelStatus;
	return true;	
}

eDirection robotTravel::getDirection(){
	
	return edirection;
}

int robotTravel::getTravelStatus(){
	
	return 	travelStatus;
}

bool robotTravel::init(){

    if ( wiringPiSetupGpio() == -1) {
        cout << "robotTravel intialization error." << endl;
        return false;
    }

    pinMode(MOTOR_RIGHT_OUT1, OUTPUT);
    pinMode(MOTOR_RIGHT_OUT2, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM, PWM_OUTPUT);
    pinMode(MOTOR_LEFT_OUT1, OUTPUT);
    pinMode(MOTOR_LEFT_OUT2, OUTPUT);
    pinMode(MOTOR_LEFT_PWM, PWM_OUTPUT);

    digitalWrite(MOTOR_RIGHT_OUT1, 0);
    digitalWrite(MOTOR_RIGHT_OUT2, 0);
    digitalWrite(MOTOR_RIGHT_PWM, 0);
    digitalWrite(MOTOR_LEFT_OUT1, 0);
    digitalWrite(MOTOR_LEFT_OUT2, 0);
    digitalWrite(MOTOR_LEFT_PWM, 0);

	return true;
}

bool robotTravel::doTravel( int direction, int speed ){

	eDirection edirection = static_cast<eDirection>(direction);

	if(!setDirection(edirection)) return false;

	if( edirection == STOP ) {
		setSpeed(0);
		setTravelStatus(0);
	}else{
		if(!setSpeed(speed)) return false;
		setTravelStatus(1);
	}

	usleep(50000);


	switch(edirection){

		case FORWARD:
	        digitalWrite(MOTOR_RIGHT_OUT1, 1);
	        digitalWrite(MOTOR_RIGHT_OUT2, 0);
	        digitalWrite(MOTOR_LEFT_OUT1, 1);
	        digitalWrite(MOTOR_LEFT_OUT2, 0);
			pwmWrite(MOTOR_RIGHT_PWM, POW_HIGH*speed/100);
			pwmWrite(MOTOR_LEFT_PWM, POW_HIGH*speed/100);
			break;
		case BACK:
	        digitalWrite(MOTOR_RIGHT_OUT1, 0);
	        digitalWrite(MOTOR_RIGHT_OUT2, 1);
	        digitalWrite(MOTOR_LEFT_OUT1, 0);
	        digitalWrite(MOTOR_LEFT_OUT2, 1);
			pwmWrite(MOTOR_RIGHT_PWM, POW_HIGH*speed/100);
			pwmWrite(MOTOR_LEFT_PWM, POW_HIGH*speed/100);
			break;
		case STOP:
	        digitalWrite(MOTOR_RIGHT_OUT1, 0);
	        digitalWrite(MOTOR_RIGHT_OUT2, 0);
	        digitalWrite(MOTOR_LEFT_OUT1, 0);
	        digitalWrite(MOTOR_LEFT_OUT2, 0);
			pwmWrite(MOTOR_RIGHT_PWM, 0);
			pwmWrite(MOTOR_LEFT_PWM, 0);
			break;
		case LEFT_FORWARD:
	        digitalWrite(MOTOR_RIGHT_OUT1, 1);
	        digitalWrite(MOTOR_RIGHT_OUT2, 0);
	        digitalWrite(MOTOR_LEFT_OUT1, 1);
	        digitalWrite(MOTOR_LEFT_OUT2, 0);
			pwmWrite(MOTOR_RIGHT_PWM, POW_HIGH*speed/100);
			pwmWrite(MOTOR_LEFT_PWM, (POW_HIGH*speed/100)*0.7);
			break;
		case RIGHT_FORWARD:
	        digitalWrite(MOTOR_RIGHT_OUT1, 1);
	        digitalWrite(MOTOR_RIGHT_OUT2, 0);
	        digitalWrite(MOTOR_LEFT_OUT1, 1);
	        digitalWrite(MOTOR_LEFT_OUT2, 0);
			pwmWrite(MOTOR_RIGHT_PWM, (POW_HIGH*speed/100)*0.7);
			pwmWrite(MOTOR_LEFT_PWM, POW_HIGH*speed/100);
			break;
		case LEFT_BACK:
	        digitalWrite(MOTOR_RIGHT_OUT1, 0);
	        digitalWrite(MOTOR_RIGHT_OUT2, 1);
	        digitalWrite(MOTOR_LEFT_OUT1, 0);
	        digitalWrite(MOTOR_LEFT_OUT2, 1);
			pwmWrite(MOTOR_RIGHT_PWM, POW_HIGH*speed/100);
			pwmWrite(MOTOR_LEFT_PWM, (POW_HIGH*speed/100)*0.7);
			break;
		case RIGHT_BACK:
	        digitalWrite(MOTOR_RIGHT_OUT1, 0);
	        digitalWrite(MOTOR_RIGHT_OUT2, 1);
	        digitalWrite(MOTOR_LEFT_OUT1, 0);
	        digitalWrite(MOTOR_LEFT_OUT2, 1);
			pwmWrite(MOTOR_RIGHT_PWM, (POW_HIGH*speed/100)*0.7);
			pwmWrite(MOTOR_LEFT_PWM, POW_HIGH*speed/100);
			break;
		case LEFT_TURN:
	        digitalWrite(MOTOR_RIGHT_OUT1, 0);
	        digitalWrite(MOTOR_RIGHT_OUT2, 1);
	        digitalWrite(MOTOR_LEFT_OUT1, 1);
	        digitalWrite(MOTOR_LEFT_OUT2, 0);
			pwmWrite(MOTOR_RIGHT_PWM, (POW_HIGH*speed/100)*0.5);
			pwmWrite(MOTOR_LEFT_PWM, (POW_HIGH*speed/100)*0.5);
			break;
		case RIGHT_TURN:
	        digitalWrite(MOTOR_RIGHT_OUT1, 1);
	        digitalWrite(MOTOR_RIGHT_OUT2, 0);
	        digitalWrite(MOTOR_LEFT_OUT1, 0);
	        digitalWrite(MOTOR_LEFT_OUT2, 1);
			pwmWrite(MOTOR_RIGHT_PWM, (POW_HIGH*speed/100)*0.5);
			pwmWrite(MOTOR_LEFT_PWM, (POW_HIGH*speed/100)*0.5);
			break;
	}
	cout << "travel direction(" << edirection << ") speed ("<< speed << ")" << endl;
	return true;
}

