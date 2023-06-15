#include "simpleTasks.h"



void simpleTasks::task1(int number){
   Serial.printf("Reading temperature: %d from core %d\n", number, xPortGetCoreID());
}


void simpleTasks::task2(int number){
    Serial.printf("Reading humidity: %d from core %d\n", number, xPortGetCoreID());
}

void simpleTasks::changePinState(int pinNumber, bool state){
    digitalWrite(pinNumber, state);
}
