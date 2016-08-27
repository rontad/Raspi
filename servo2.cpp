// 2軸サーボ首ふりサンプル
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>

#define MOTORPWM_X 12	//18,12
#define MOTORPWM_Y 19	//13,19

#define SERVO_MIN 25
#define SERVO_MAX 123

int main()
{
	if (wiringPiSetupGpio() == -1) {
		std::cout << "cannot setup gpio." << std::endl;
		return 1;
	}

	pinMode(MOTORPWM_X, PWM_OUTPUT);
	pinMode(MOTORPWM_Y, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
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
		usleep(5000);
	}

	return 0;
}