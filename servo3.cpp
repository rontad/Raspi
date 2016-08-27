// SG90へのPWM信号を手作りしてみる。
// SG90:20000μs(50Hz),下限500μs 上限2400μs
// コマンドライン引数でサーボの振り先位置を0～100で指定(%)

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>

using namespace std;

#define MOTORPWM_X 12	//18,12

int main(int argc,char *argv[])
{
	if (argc != 2) {
		cout << "parameter error" << endl;
		return 1;
	}

	int per;
	sscanf(argv[1], "%d", &per);
	int on_usec;
	on_usec = (2400-500)*(per*0.01) + 500;
	cout << "on_usec " << on_usec << endl;

	if (wiringPiSetupGpio() == -1) {
		cout << "cannot setup gpio." << endl;
		return 1;
	}

	pinMode(MOTORPWM_X, OUTPUT);

	struct timeval oldTime;	
	struct timeval myTime;	

	gettimeofday(&oldTime, NULL);
	bool bOn = false;

	while (true) {

		gettimeofday(&myTime, NULL);

		if(bOn==false){
			if(myTime.tv_usec-oldTime.tv_usec>20000-on_usec){
				digitalWrite(MOTORPWM_X, 1);
				bOn = true;
				oldTime = myTime;
			}
		}else{
			if(myTime.tv_usec-oldTime.tv_usec>on_usec){
				digitalWrite(MOTORPWM_X, 0);
				bOn = false;
				oldTime = myTime;
			}
		}

	}

	return 0;
}