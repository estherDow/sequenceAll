#include "keybrd.h"
#include "pinStrapping.h"
#include "sequenceAll.h"
#include "network.h"
TaskHandle_t Task1;
TaskHandle_t Task2;
wlan WLAN;
//Holy Grail

void setup() {
  Serial.begin(115200);
  WLAN.begin();
  Serial.println("Testing Lamps:");
  setPads();
  setLampPins();
  setKeyboardMatrix();
  circleRoll(5);
  //Serial.println(play);


  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */


  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */

}

//Task1code: Inputs keyboard
void Task1code( void * pvParameters ){
  for(;;){
    //Serial.println("Task1");
    scanMatrix();
    stateMachine();
    potRead();
    vTaskDelay(5); //very important to give the Tasks something to do while developing
  }
}

//Task2code: outputs osc
void Task2code( void * pvParameters ){
  for(;;){
    //Serial.print(play);

    if (isPlayed()) {
      //Serial.println("iamhere");
      sequenceAll();
      lightBringer();
      loopWorker();
    }
    momento();

    //toggleLamp;
    //vTaskDelay(5);//very important to give the Tasks something to do while developing
  }
}

void loop() {

}
