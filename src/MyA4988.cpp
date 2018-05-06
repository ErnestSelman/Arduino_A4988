/*
 * MyController.cpp - by Ernest Selman
 * modified from Arduino Stepper Library
 *
 * Stepper library for 4 wire bipolar steppers, using A4988 stepper motor controller
 *
 */

#include "MyController.h"

/*
 *   constructor for four-pin version without stop signals
 */
MyController::MyController(int number_of_steps, int step_pin, int dir_pin){
  this->direction = 0;      // motor direction
  this->number_of_steps = number_of_steps; // total number of steps for this motor
  this->step_delay = 10000;
  this->pulse_delay = 500;
  this->step_mode = 0;
  // Arduino pins for the motor control connection:
  this->step_pin = step_pin;
  this->dir_pin = dir_pin;
  this->ms1_pin = 0;
  this->ms2_pin = 0;
  this->ms3_pin = 0;

  // setup the pins on the microcontroller:
  pinMode(this->step_pin, OUTPUT);
  pinMode(this->dir_pin, OUTPUT);

  digitalWrite(this->step_pin, LOW);
  digitalWrite(this->dir_pin, LOW);
}

MyController::MyController(int number_of_steps, int step_pin, int dir_pin,
                  int ms1, int ms2, int ms3, int mode){
  this->direction = 0;      // motor direction
  this->number_of_steps = number_of_steps; // total number of steps for this motor
  this->step_delay = 10000;
  this->pulse_delay = 500;
  this->step_mode = 0;
  // Arduino pins for the motor control connection:
  this->step_pin = step_pin;
  this->dir_pin = dir_pin;
  this->ms1_pin = ms1;
  this->ms2_pin = ms2;
  this->ms3_pin = ms3;

  // setup the pins on the microcontroller:
  pinMode(this->step_pin, OUTPUT);
  pinMode(this->dir_pin, OUTPUT);
  pinMode(this->ms1_pin, OUTPUT);
  pinMode(this->ms2_pin, OUTPUT);
  pinMode(this->ms3_pin, OUTPUT);

  digitalWrite(this->step_pin, LOW);
  digitalWrite(this->dir_pin, LOW);
  setStepMode(mode);
}

/*
 * Sets the speed in revs per minute
 */
void MyController::setRevPerMin(double whatSpeed){

	switch(this->step_mode){
    case HALF_STEP:
      this->step_delay = (long)(60L * 1000L * 1000L / (this->number_of_steps*2) / whatSpeed);
      break;
    case QUATER_STEP:
      this->step_delay = (long)(60L * 1000L * 1000L / (this->number_of_steps*4) / whatSpeed);
      break;
    case EIGHTH_STEP:
      this->step_delay = (long)(60L * 1000L * 1000L / (this->number_of_steps*8) / whatSpeed);
      break;
    case SIXTEENTH_STEP:
      this->step_delay = (long)(60L * 1000L * 1000L / (this->number_of_steps*16) / whatSpeed);
      break;
    default:
      this->step_delay = (long)(60L * 1000L * 1000L / this->number_of_steps / whatSpeed);
      break;
  }
}

void MyController::setRevPerHour(double whatSpeed){

  switch(this->step_mode){
    case HALF_STEP:
      this->step_delay = (long)(60L * 60L * 1000L * 1000L / (this->number_of_steps*2) / whatSpeed);
      break;
    case QUATER_STEP:
      this->step_delay = (long)(60L * 60L * 1000L * 1000L / (this->number_of_steps*4) / whatSpeed);
      break;
    case EIGHTH_STEP:
      this->step_delay = (long)(60L * 60L * 1000L * 1000L / (this->number_of_steps*8) / whatSpeed);
      break;
    case SIXTEENTH_STEP:
      this->step_delay = (long)(60L * 60L * 1000L * 1000L / (this->number_of_steps*16) / whatSpeed);
      break;
    default:
      this->step_delay = (long)(60L * 60L * 1000L * 1000L / this->number_of_steps / whatSpeed);
      break;
  }
}

void MyController::setStepPerMin(double whatSpeed){

	this->step_delay = (long)(60L * 1000L * 1000L / whatSpeed);
}

void MyController::setStepPerHour(double whatSpeed){

	this->step_delay = (long)(60L * 60L * 1000L * 1000L / whatSpeed);
}

void MyController::setPulseTime(unsigned long whatTime){

	this->pulse_delay = whatTime;
}

void MyController::setStepMode(int new_mode){

  this->step_mode = new_mode;
  switch(this->step_mode){
    case HALF_STEP:
      digitalWrite(this->ms1_pin, HIGH);
      digitalWrite(this->ms2_pin, LOW);
      digitalWrite(this->ms3_pin, LOW);
      break;
    case QUATER_STEP:
      digitalWrite(this->ms1_pin, LOW);
      digitalWrite(this->ms2_pin, HIGH);
      digitalWrite(this->ms3_pin, LOW);
      break;
    case EIGHTH_STEP:
      digitalWrite(this->ms1_pin, HIGH);
      digitalWrite(this->ms2_pin, HIGH);
      digitalWrite(this->ms3_pin, LOW);
      break;
    case SIXTEENTH_STEP:
      digitalWrite(this->ms1_pin, HIGH);
      digitalWrite(this->ms2_pin, HIGH);
      digitalWrite(this->ms3_pin, HIGH);
      break;
    default:
      digitalWrite(this->ms1_pin, LOW);
      digitalWrite(this->ms2_pin, LOW);
      digitalWrite(this->ms3_pin, LOW);
      break;
  }
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void MyController::step(int steps_to_move)
{
  
  int steps_left;  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { digitalWrite(this->dir_pin, HIGH); }
  if (steps_to_move < 0) { digitalWrite(this->dir_pin, LOW); }

  bool Stopped = 0;

  // decrement the number of steps, moving one step each time:
  for(steps_left = abs(steps_to_move); steps_left > 0; steps_left--){
  	digitalWrite(this->step_pin, HIGH);
  	delayMicroseconds(this->pulse_delay);
  	digitalWrite(this->step_pin, LOW);
    if(this->step_delay - this->pulse_delay > 0){
      delayMicroseconds(this->step_delay - this->pulse_delay);
    }
  }
}

/*
  version() returns the version of the library:
*/
int MyController::version(void)
{
  return 1;
}

