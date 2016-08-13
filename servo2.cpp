// 2軸サーボ首ふりサンプル
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>

#define MOTORPWM_X 18
#define MOTORPWM_Y 13

#define SERVO_MIN 24
#define SERVO_MAX 115

int main()
{
	if (wiringPiSetupGpio() == -1) {
		std::cout << "cannot setup gpio." << std::endl;
		return 1;
	}

	pinMode(MOTORPWM_X, PWM_OUTPUT);
	pinMode(MOTORPWM_Y, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(400);
	pwmSetRange(1024);

	int x = SERVO_MIN;
	int y = SERVO_MIN;

	int x_sign = 1;
	int y_sign = 1;
	
	while (true) {
		
		x = x + 1 * x_sign;
		y = y + 3 * y_sign;
		if(x > SERVO_MAX || x < SERVO_MIN){
			x_sign = x_sign * (-1);
		}else{
			pwmWrite(MOTORPWM_X, x);
		}
		if(y > SERVO_MAX || y < SERVO_MIN){
			y_sign = y_sign * (-1);
		}else{
			pwmWrite(MOTORPWM_Y, y);
		}
		usleep(50000);
	}

	return 0;
}