/*
 * Software library to control UPR rocksat-x 2014 payload
 *
 * Author: Pedro A. Melendez <lazy.chino@gmail.com>
 *
 */

#ifndef RSX2014_H
#define RSX2014_H

#include <Arduino.h>
#include <SdFat.h>

// --------------- Arduino pins definitions ------------------

// Stepper driver 1
#define actuator1_dir 35
#define actuator1_ena 31
#define actuator1_stp 33
#define actuator1_limit 7

// Stepper driver 2
#define actuator2_dir 53
#define actuator2_ena 49
#define actuator2_stp 51


//analogs inputs
#define Proximity_sensor A3
#define Launch A0
#define SkirtOff A1
#define PowerOff A2
#define Piezo1 A8
#define Piezo2 A9
#define Piezo3 A10

//GoPro cameras
//side camera pins
#define camera1_trig 23

//bottom camera
#define camera2_trig 25

// constants
#define maxStepperSpeed 0.27 // inch/s
#define minStepperSpeed 150 // inch/s
#define travelPerStep 0.00015625 // @ full stepping
#define railTravel 3.93
#define maxPeriod 170
#define minPeriod 44

//sdcard
#define chipSelect 10

class payload2014
{
private:
    SdFat sd;
    void moveRail(bool);

public:
    payload2014();
    ~payload2014(){}
    void collectData();
    void openRail();
    void closeRail();
    void triggerCameras();
};

#endif
