/*
 * this sample program moves motor in one direction using half step mode, then the other direction in eighth step mode.
 */
//please follow the wiring diagram found on polulu.com  (https://www.pololu.com/product/1182 by the time of this update.)
//also keep in  mind the minimum wiring diagram doesn't use MS pins; these can be connected straight to the arduino.
#define MS_1 2
#define MS_2 3
#define MS_3 4
#define STEP_PIN 5
#define DIR_PIN 6

#define STEPS_PER_REV 400     //step per 1 rev in full step (do not change if using half step)  
#define RPM 30                //start speed in rev/min

//number of steps to move every click. Remember, if you use different Step Mode 
//you have to use different step number to move the same amount. For example:
// 1 step in FULL_STEP = 2 steps in HALF_STEP = 4 steps in QUARTER_STEP etc.
#define MOVE 800              //just for testing, motor moves one rev in HALF_STEP

#include "MyController.h"

//you can choose from FULL_STEP, HALF_STEP, QUARTER_STEP, EIGHTH_STEP, SIXTEENTH_STEP. 
//NOTE: For some motors FULL_STEP doesn't move acuratelly some times, specially at speeds lower than 20 RPM

MyController myController(STEPS_PER_REV, STEP_PIN, DIR_PIN,
                          MS_1, MS_2, MS_3, HALF_STEP);

void setup() {

  //Stepper set up
  myController.setRevPerMin(RPM);
  
}

void loop() {

  //this function removes controll from the user until finish. 
  myController.step(MOVE);
  setStepMode(EIGHTH_STEP);
  delay(500);
  myController.step(-4*MOVE);
  
}


