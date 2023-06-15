#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "simpleTasks.h"

simpleTasks simpleT;
static TaskHandle_t receiverHandler = NULL;
bool LedState = false;

const int SENDER_1 = 10;
const int SENDER_2 = 20;


void sender1(void * param){
  while(true){
    LedState = !LedState;
    // Notificar al receiver
    xTaskNotify(receiverHandler, SENDER_1, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void sender2(void * param){
  while(true){
    // Notificar al receiver
    xTaskNotify(receiverHandler, SENDER_2, eSetValueWithOverwrite);
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}



void receiver(void *param){
  u_int sender;
  while(true){
    xTaskNotifyWait(0, 0, &sender, portMAX_DELAY);
    Serial.printf("Notificacion recibida de: %s\n", 
              sender == SENDER_1? "sender 1": "sender 2");
    if(sender == SENDER_1) simpleT.changePinState(LED_BUILTIN, LedState);

  }
}


void task1(void *params){
  while(true){
    simpleT.task1(rand());
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

}
void task2(void *params){
  while(true){
    simpleT.task2(rand());
    vTaskDelay(pdMS_TO_TICKS(4000));
  }

}


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LedState);
  Serial.printf("Compilation: %s, %s\n", __DATE__, __TIME__);
  xTaskCreatePinnedToCore(task1, "Tarea 1", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(task2, "Tarea 2", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(receiver, "Receptor", 2048, NULL, 2, &receiverHandler, 0);
  xTaskCreatePinnedToCore(sender1, "Enviador", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(sender2, "Enviador", 2048, NULL, 1, NULL, 1);

}

void loop() {
  
  

}

