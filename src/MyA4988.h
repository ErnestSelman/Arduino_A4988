/*
 * MyController.h - by Ernest Selman 
 *
 * Stepper library for 4 wire bipolar steppers, using A4988 stepper motor controller
 *
 */

// ensure this library description is only included once
#ifndef MyController_h
#define MyController_h

#define FULL_STEP 0
#define HALF_STEP 1
#define QUATER_STEP 2
#define EIGHTH_STEP 3
#define SIXTEENTH_STEP 4

#include "Arduino.h"

// library interface description
class MyController {
  public:
    // constructors:
    MyController(int number_of_steps, int step_pin, int dir_pin);
    MyController(int number_of_steps, int step_pin, int dir_pin,
                  int ms1, int ms2, int ms3, int mode);

    // speed setter method:
    void setRevPerMin(double whatSpeed);
    void setRevPerHour(double whatSpeed);
    void setStepPerMin(double whatSpeed);
    void setStepPerHour(double whatSpeed);
    void setPulseTime(unsigned long whatTime);
    void setStepMode(int mode);

    // mover method:
    void step(int number_of_steps);

    int version(void);

  private:

    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in us, based on speed
    unsigned long pulse_delay;// delay for the step signal pulse
    int number_of_steps;     // total number of steps this motor can take
    int step_mode;
    // motor pin numbers:
    int step_pin;
    int dir_pin;
    int ms1_pin;
    int ms2_pin;
    int ms3_pin;
};

#endif


