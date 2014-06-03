#include <Arduino.h>
#include "RSX2014.h"

payload2014::payload2014()
{
    // init pins 
    
    // cameras
    pinMode(camera1_trig, OUTPUT);
    pinMode(camera2_trig, OUTPUT);
    
    // actuator 1 bottom
    pinMode(actuator1_dir, OUTPUT);
    pinMode(actuator1_stp, OUTPUT);
    pinMode(actuator1_ena, OUTPUT);
    digitalWrite(actuator1_ena, HIGH);
    pinMode(actuator1_limit, INPUT_PULLUP);

    // actuator 2 top
    pinMode(actuator2_dir, OUTPUT);
    pinMode(actuator2_stp, OUTPUT);
    pinMode(actuator2_ena, OUTPUT);
    digitalWrite(actuator2_ena, HIGH);
}

inline void  payload2014::collectData()
{
    //read analog and save to SD
}

void  payload2014::moveRail(bool dir)
{
    unsigned long steps1 = (3.393/travelPerStep)*16;
    unsigned long steps2 = (2.5/travelPerStep)*16;
    
    digitalWrite(actuator1_dir, dir);  // set direction outward
    digitalWrite(actuator2_dir, dir);  

    int period1 = 200;                        // set initial speed
    int period2 = 200;                        
    
    digitalWrite(actuator1_ena, LOW);       // enable board
    digitalWrite(actuator2_ena, LOW);       
    
    while(steps1 > 0 || steps2 > 0)
    {
        if(steps1 > 0)
        {
            digitalWrite(actuator1_stp, HIGH);
            digitalWrite(actuator2_stp, HIGH);
            delayMicroseconds(2);
            digitalWrite(actuator1_stp, LOW);
            digitalWrite(actuator2_stp, LOW);
            delayMicroseconds(period1);
            
            
            
            if( steps1 >= 3200)
            { 
                if(period1 > 44 && steps1%400 == 0)       // on the first revolutions
                    period1--;           // the period of the pulse is decrease to accelerate
            }
            else if( steps1 < 3200)
            { 
                if( steps1%20 == 0)      // on the last revolution period
                    period1++;               // increase to decelerate
            }
            else{}
            steps1--;
        }
        
        if(steps2 > 0)
        {
            digitalWrite(actuator2_stp, HIGH);
            delayMicroseconds(2);
            digitalWrite(actuator2_stp, LOW);
            delayMicroseconds(period2);
            
            if(steps2 >= 3200)
            { 
                if(period2 > 44 && steps2%400 == 0)       // on the first revolutions
                    period2--;           // the period of the pulse is decrease to accelerate
            }
            else if(steps2 < 3200)
            { 
                if( steps2%20 == 0)      // on the last revolution period
                    period2++;               // increase to decelerate
            }
            else{}
            steps2--;
        }
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
