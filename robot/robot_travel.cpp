#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include "robot_travel.h"

using namespace std;

#define MOTOR1_OUT1 14
#define MOTOR1_OUT2 15
#define MOTOR1_PWM 18
#define MOTOR2_OUT1 5
#define MOTOR2_OUT2 6
#define MOTOR2_PWM 13
#define POWHIGH 1024
#define POWLOW 300

robotTravel::robotTravel(){

	speed = 0;
	direction = 3;
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

bool robotTravel::setDirection( int direction ){

	if( direction < 1 || direction > 9 ) {
		cout << "Specified direction is not valid.(" << direction << ")" << endl;
		return false;
	}

	this->direction = direction;
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

int robotTravel::getDirection(){
	
	return direction;
}

int robotTravel::getTravelStatus(){
	
	return 	travelStatus;
}

bool robotTravel::init(){

    if ( wiringPiSetupGpio() == -1) {
        cout << "robotTravel intialization error." << endl;
        return false;
    }

    pinMode(MOTOR1_OUT1, OUTPUT);
    pinMode(MOTOR1_OUT2, OUTPUT);
    pinMode(MOTOR1_PWM, PWM_OUTPUT);
    pinMode(MOTOR2_OUT1, OUTPUT);
    pinMode(MOTOR2_OUT2, OUTPUT);
    pinMode(MOTOR2_PWM, PWM_OUTPUT);

    digitalWrite(MOTOR1_OUT1, 0);
    digitalWrite(MOTOR1_OUT2, 0);
    digitalWrite(MOTOR1_PWM, 0);
    digitalWrite(MOTOR2_OUT1, 0);
    digitalWrite(MOTOR2_OUT2, 0);
    digitalWrite(MOTOR2_PWM, 0);

	return true;
}

bool robotTravel::doTravel( int direction, int speed ){

	if(!setDirection(direction)) return false;

	if( getDirection() == 3 ) {
		setSpeed(0);
		setTravelStatus(0);
	}else{
		if(!setSpeed(speed)) return false;
		setTravelStatus(1);
	}

	sleep(1);

	switch(getDirection()){

		case 1:
	        digitalWrite(MOTOR1_OUT1, 1);
	        digitalWrite(MOTOR1_OUT2, 0);
	        digitalWrite(MOTOR2_OUT1, 1);
	        digitalWrite(MOTOR2_OUT2, 0);
			pwmWrite(MOTOR1_PWM, 1024*speed/100);
			pwmWrite(MOTOR2_PWM, 1024*speed/100);
			break;
		case 2:
	        digitalWrite(MOTOR1_OUT1, 0);
	        digitalWrite(MOTOR1_OUT2, 1);
	        digitalWrite(MOTOR2_OUT1, 0);
	        digitalWrite(MOTOR2_OUT2, 1);
			pwmWrite(MOTOR1_PWM, 1024*speed/100);
			pwmWrite(MOTOR2_PWM, 1024*speed/100);
			break;
		case 3:
	        digitalWrite(MOTOR1_OUT1, 0);
	        digitalWrite(MOTOR1_OUT2, 0);
	        digitalWrite(MOTOR2_OUT1, 0);
	        digitalWrite(MOTOR2_OUT2, 0);
			pwmWrite(MOTOR1_PWM, 0);
			pwmWrite(MOTOR2_PWM, 0);
			break;
		case 4:
	        digitalWrite(MOTOR1_OUT1, 1);
	        digitalWrite(MOTOR1_OUT2, 0);
	        digitalWrite(MOTOR2_OUT1, 1);
	        digitalWrite(MOTOR2_OUT2, 0);
			pwmWrite(MOTOR1_PWM, (1024*speed/100)*0.7);
			pwmWrite(MOTOR2_PWM, 1024*speed/100);
			break;
		case 5:
	        digitalWrite(MOTOR1_OUT1, 1);
	        digitalWrite(MOTOR1_OUT2, 0);
	        digitalWrite(MOTOR2_OUT1, 1);
	        digitalWrite(MOTOR2_OUT2, 0);
			pwmWrite(MOTOR1_PWM, 1024*speed/100);
			pwmWrite(MOTOR2_PWM, (1024*speed/100)*0.7);
			break;
		case 6:
	        digitalWrite(MOTOR1_OUT1, 0);
	        digitalWrite(MOTOR1_OUT2, 1);
	        digitalWrite(MOTOR2_OUT1, 0);
	        digitalWrite(MOTOR2_OUT2, 1);
			pwmWrite(MOTOR1_PWM, (1024*speed/100)*0.7);
			pwmWrite(MOTOR2_PWM, 1024*speed/100);
			break;
		case 7:
	        digitalWrite(MOTOR1_OUT1, 0);
	        digitalWrite(MOTOR1_OUT2, 1);
	        digitalWrite(MOTOR2_OUT1, 0);
	        digitalWrite(MOTOR2_OUT2, 1);
			pwmWrite(MOTOR1_PWM, 1024*speed/100);
			pwmWrite(MOTOR2_PWM, (1024*speed/100)*0.7);
			break;
		case 8:
	        digitalWrite(MOTOR1_OUT1, 0);
	        digitalWrite(MOTOR1_OUT2, 1);
	        digitalWrite(MOTOR2_OUT1, 1);
	        digitalWrite(MOTOR2_OUT2, 0);
			pwmWrite(MOTOR1_PWM, 1024*speed/100);
			pwmWrite(MOTOR2_PWM, 1024*speed/100);
			break;
		case 9:
	        digitalWrite(MOTOR1_OUT1, 1);
	        digitalWrite(MOTOR1_OUT2, 0);
	        digitalWrite(MOTOR2_OUT1, 0);
	        digitalWrite(MOTOR2_OUT2, 1);
			pwmWrite(MOTOR1_PWM, 1024*speed/100);
			pwmWrite(MOTOR2_PWM, 1024*speed/100);
			break;
	}
	cout << "travel direction(" << direction << ") speed ("<< speed << ")" << endl;
	return true;
}

