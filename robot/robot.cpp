#include <iostream>
#include "robot_travel.h"

int main(void) {

robotTravel * objTravel = new robotTravel();
objTravel->init();

int i;

while( std::cin >> i ) {

        objTravel->doTravel(i,100);

}

delete objTravel;
return 0;
}