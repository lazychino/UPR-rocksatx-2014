/*
 * Software library to control UPR rocksat-x 2014 payload 
 * 
 * Author: Pedro A. Melendez <lazy.chino@gmail.com>
 * 
 */
 
#ifndef RSX2014_H
#define RSX2014_H

#include <Arduino.h>
#include <easyLinearStepper.h>


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


// 16bit parallel pins
#define parallel_1  22
#define parallel_2  24
#define parallel_3  26
#define parallel_4  28
#define parallel_5  30
#define parallel_6  32
#define parallel_7  34
#define parallel_8  36
#define parallel_9  38
#define parallel_10 40
#define parallel_11 42
#define parallel_12 44
#define parallel_13 46
#define parallel_14 48
#define parallel_15 50
#define parallel_16 52
#define parallel_strobe 27


//analogs inputs
#define proximity A3
#define Launch A0
#define SkirtOff A1
#define PowerOff A2

//GoPro cameras
//side camera pins
#define camera1_trig 23

//bottom camera
#define camera2_trig 25

// constants
#define maxStepperSpeed 0.21875 // in/s
#define minStepperSpeed 0.03125 // in/s
#dedine travelPerStep 0.00015625 // @ full stepping

class payload2014 
{
private:
    
    
    
public:


};



#endif
