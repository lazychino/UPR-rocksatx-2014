#include <Arduino.h>
#include "RSX2014.h"

payload2014::payload2014()
{
    // init pins

    // cameras
    pinMode(camera1_trig, OUTPUT);
    digitalWrite(camera1_trig, LOW);
    pinMode(camera2_trig, OUTPUT);
    digitalWrite(camera2_trig, LOW);

    // actuator 1 bottom
    pinMode(actuator1_dir, OUTPUT);
    digitalWrite(actuator1_dir, LOW);

    pinMode(actuator1_stp, OUTPUT);
    digitalWrite(actuator1_stp, LOW);

    pinMode(actuator1_ena, OUTPUT);
    digitalWrite(actuator1_ena, HIGH);
    pinMode(actuator1_limit, INPUT_PULLUP);

    // actuator 2 top
    pinMode(actuator2_dir, OUTPUT);
    digitalWrite(actuator2_dir, LOW);

    pinMode(actuator2_stp, OUTPUT);
    digitalWrite(actuator2_stp, LOW);

    pinMode(actuator2_ena, OUTPUT);
    digitalWrite(actuator2_ena, HIGH);

    // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
    // breadboards.  use SPI_FULL_SPEED for better performance.
    if (!sd.begin(chipSelect, SPI_FULL_SPEED)) Serial.println("ERROR: could not init SD card");
}

void payload2014::collectData()
{
    // create folder if not exists
    sd.mkdir("LOGS");

    // create or open a file for append
    ofstream sdlog("LOGS/DATA.TXT", ios::out | ios::app);

    sdlog << "started logging" << endl;

    unsigned long interval = 0;
    unsigned long minute = millis()+60000;
    while(analogRead(PowerOff) < 2000)
    {
        sdlog << micros()  << ","
              << analogRead(A5) << ","
              << analogRead(A6) << ","
              << analogRead(A7) << endl;
    }

    sdlog << "ended logging" << endl;

    sdlog.close();

    if (!sdlog) Serial.println("append failed");
}

void  payload2014::moveRail(bool dir)
{
    unsigned long steps = (railTravel/travelPerStep)*16;

    digitalWrite(actuator1_dir, dir);  // set direction outward
    digitalWrite(actuator2_dir, dir);

    int period = maxPeriod;                 // set initial speed

    digitalWrite(actuator1_ena, LOW);       // enable board
    digitalWrite(actuator2_ena, LOW);

    while(steps > 0)
    {
        digitalWrite(actuator1_stp, HIGH);
        digitalWrite(actuator2_stp, HIGH);
        delayMicroseconds(2);
        digitalWrite(actuator1_stp, LOW);
        digitalWrite(actuator2_stp, LOW);
        delayMicroseconds(period);

        if( steps >= 3200)
        {
            if(period > minPeriod && steps % 400 == 0)       // on the first revolutions
                period--;           // the period of the pulse is decrease to accelerate
        }
        else if( steps < 200)
        {
            period++;               // increase to decelerate
        }
        else{}
        steps--;
    }
    digitalWrite(actuator1_ena, HIGH);         // disable board
    digitalWrite(actuator2_ena, HIGH);         // disable board
}

void  payload2014::openRail()
{
    moveRail(1);
}

void  payload2014::closeRail()
{
    moveRail(0);
}

void payload2014::triggerCameras()
{
    digitalWrite(camera1_trig, HIGH);
    digitalWrite(camera2_trig, HIGH);
    delay(250);
    digitalWrite(camera1_trig, LOW);
    digitalWrite(camera2_trig, LOW);
}
