#include "RSX2014.h"

void setup() {
    analogReadResolution(12);
    Serial.begin(19200);
    payload2014 payload;
    Serial.println("UPR Payload alive");
    
    //para launch
    //unsigned long tenToLaunch = millis() + 240000;
    //while( millis() < tenToLaunch){}
    
    //for testing only
    payload.triggerCameras();
    Serial.println("cameras on");
    delay(10000); 
    //for testing only
    
    while(analogRead(Launch) < 2000 ){}
    Serial.println("Launch");
    
    while(analogRead(SkirtOff) < 2000 ){}
    Serial.println("Skirt Off");
    
    while(analogRead(Proximity_sensor) > 100){}
    Serial.println("rail deployment started");
    payload.openRail();
    Serial.println("rail deployed");
    while(analogRead(PowerOff) < 2000 )
    {
        //payload.collectData();
    }
    Serial.println("rail retracting");
    payload.closeRail();
    Serial.println("rail retracted");
    Serial.println("box closed");
    
    payload.triggerCameras();
    Serial.println("going back home");
}

void loop() {
}
