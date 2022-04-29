#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

extern "C" {
#include "CLI_Impl.h"
} 

extern bool RepeatCommand;

void setup() {
    // put your setup code here, to run once:
  strncpy(cliAppVersion, "FreeRTOS_Cli V0.3", VERSION_MAX) ;
  Serial.begin(115200);
  // create the RTOS CLI task
  xCreateCLITask(); 
}
uint32_t lastTime=0;
uint32_t periodTime = 3000;

void loop() {

    uint32_t currentTime = millis();

    if (currentTime - lastTime > periodTime)
    {   
        lastTime = currentTime;
        if (RepeatCommand == true)
        {
            uint32_t mallocSize = 2000;
            uint32_t* mPtr = (uint32_t*)  pvPortMalloc(mallocSize);
            
            Serial.printf("this is a test. Ptr=0x%1x\r\n", mPtr);
        }
    }

  // put your main code here, to run repeatedly:
}

