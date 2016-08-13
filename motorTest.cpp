#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>

#define MOTOROUT1 14
#define MOTOROUT2 15
#define MOTORPWM 18
#define POWHIGH 1024
#define POWLOW 300

int main(void) {
    int i = 0;

    if ( wiringPiSetupGpio() == -1) {
        printf("setup error");
        return 1;
    }

    pinMode(MOTOROUT1, OUTPUT);
    pinMode(MOTOROUT2, OUTPUT);
    pinMode(MOTORPWM, PWM_OUTPUT);

    digitalWrite(MOTOROUT1, 0);
    digitalWrite(MOTOROUT2, 0);
    digitalWrite(MOTORPWM, 0);

    while(1) {
	//前進
        printf("forward\n");
        digitalWrite(MOTOROUT1, 1);
	//PWMで徐々にスピードを上げていく
	for(int pow = POWLOW; pow < POWHIGH; pow=pow+50){
		pwmWrite(MOTORPWM, pow);
		printf("speed:%d\n",pow);
	        sleep(1);
        }
	//PWMで徐々にスピードを下げていく
	for(int pow = POWHIGH; pow > POWLOW; pow=pow-50){
		pwmWrite(MOTORPWM, pow);
		printf("speed:%d\n",pow);
	        sleep(1);
        }
        digitalWrite(MOTOROUT1, 0);
        usleep(50000);
        
	//後退
        printf("back\n");
        digitalWrite(MOTOROUT2, 1);
	//PWMで徐々にスピードを上げていく
	for(int pow = POWLOW; pow < POWHIGH; pow=pow+100){
		pwmWrite(MOTORPWM, pow);
		printf("speed:%d\n",pow);
	        sleep(1);
        }
	//PWMで徐々にスピードを下げていく
	for(int pow = POWHIGH; pow > POWLOW; pow=pow-50){
		pwmWrite(MOTORPWM, pow);
		printf("speed:%d\n",pow);
	        sleep(1);
        }
        digitalWrite(MOTOROUT2, 0);
        usleep(50000);
    }

    return 0;
}