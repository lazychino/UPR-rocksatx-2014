#include <SdFat.h>
#include "RSX2014.h"

void setup() {
    analogReadResolution(12);
    Serial.begin(19200);
    Serial.println("UPR Payload alive");
    
    Serial1.begin(19200);
    payload2014 payload;
    Serial1.println("UPR Payload alive");

    /*
     *
     * UNCOMMENT FOR AUGUST!!!!!
     * this is to avoid waiting 4 mins while testing
     *
    unsigned long tenToLaunch = millis() + 230000;
    while( millis() < tenToLaunch){}

    payload.triggerCameras();
    Serial1.println("cameras on");
    */
    Serial1.println(analogRead(Launch));
    while(analogRead(Launch) < 2000 ){}
    Serial1.print(millis());
    Serial1.println(", Launch");

    //for testing only
    payload.triggerCameras();
    Serial1.print(millis());
    Serial1.println(", cameras on");
    //for testing only

    while(analogRead(SkirtOff) < 2000 ){}
    Serial1.print(millis());
    Serial1.println(", Skirt Off");

    while(analogRead(Proximity_sensor) > 100){}
    Serial1.print(millis());
    Serial1.println("rail deployment started");

    payload.openRail();
    Serial1.print(millis());
    Serial1.println("rail deployed");

    // this method have a loop inside
    // and will block while reading data
    payload.collectData();
    

    Serial1.print(millis());
    Serial1.println("rail retracting");
    payload.closeRail();

    Serial1.print(millis());
    Serial1.println("rail retracted");
    Serial1.println("box closed");

    payload.triggerCameras();
    Serial1.print(millis());
    Serial1.println("going back home");
}

void loop() {
}
