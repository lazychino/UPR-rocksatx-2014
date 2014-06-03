#include "RSX2014.h"

void setup() {
    Serial.begin(19200);
    payload2014 payload;
    Serial1.println("UPR Payload alive");
    
    unsigned long tenToLaunch = millis() + 240000;
    
    while( millis() > tenToLaunch){}
    digitalWrite(camera1_trig, HIGH);
    digitalWrite(camera2_trig, HIGH);
    Serial1.println("cameras on");
    
    while(analogRead(Launch) < 1000 ){}
    Serial1.println("Launch");
    
    while(analogRead(SkirtOff) < 1000 ){}
    Serial1.println("Skirt Off");
    
    while(analogRead(Proximity_sensor) > 100){}
    Serial1.println("rail deployment started");
    payload.openRail();
    Serial1.println("rail deployed");
    while(analogRead(PowerOff) < 1000 )
    {
        //payload.collectData();
    }
    Serial1.println("rail retracting");
    payload.closeRail();
    Serial1.println("rail retracted");
    Serial1.println("box closed");
    Serial1.println("going back home");
}

void loop() {
  
}
