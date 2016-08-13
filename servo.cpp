//入力値でサーボ首ふりサンプル
#include <iostream>
#include <wiringPi.h>

#define MOTORPWM 18

int main()
{
  if (wiringPiSetupGpio() == -1) {
    std::cout << "cannot setup gpio." << std::endl;
    return 1;
  }

  pinMode(MOTORPWM, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(400);
  pwmSetRange(1024);

  while (true) {
    int num;
    std::cin >> num;

    if (num == -1) {
      break;
    }

    pwmWrite(MOTORPWM, num);
  }

  return 0;
}