#ifndef SIMPLETASKS_H
#define SIMPLETASKS_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>

class simpleTasks{
    public:
        void task1(int number);
        void task2(int number);
        void changePinState(int pinNumber, bool state);

};



#endif