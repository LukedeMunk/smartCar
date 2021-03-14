/*
   File:      L298NMotors.ccp
   Authors:   Luke de Munk
   Class:     L298NMotors
   Version:   1.0

   Library for controlling two motors with L298N driver.
*/
#include "L298NMotors.h"

/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin    Pin for the data
  @param    numLeds       Number of leds
*/
/**************************************************************************/
L298NMotors::L298NMotors(uint8_t leftEnablePin, uint8_t leftSpeedPin, 
                            uint8_t rightEnablePin, uint8_t rightSpeedPin) {
    _leftEnablePin = leftEnablePin;
    _leftSpeedPin = leftSpeedPin;
    _rightEnablePin = rightEnablePin;
    _rightSpeedPin = rightSpeedPin;
}

/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin    Pin for the data
  @param    numLeds       Number of leds
*/
/**************************************************************************/
L298NMotors::forward(uint8_t speed) {

}

/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin    Pin for the data
  @param    numLeds       Number of leds
*/
/**************************************************************************/
L298NMotors::backward(uint8_t speed) {

}

/**************************************************************************/
/*!
  @brief    Stop car.
*/
/**************************************************************************/
L298NMotors::stop(){
    digitalWrite(_leftEnablePin, 0);
    digitalWrite(_rightEnablePin, 0);
}

/**************************************************************************/
/*!
  @brief    Rotate car.
  @param    deg             Degrees (-180 - 180)
*/
/**************************************************************************/
L298NMotors::rotate(int16_t deg, uint8_t speed) {
    if (deg > 0) {
        digitalWrite(_leftSpeedPin, speed);
        digitalWrite(_rightSpeedPin, speed);
    } else {
        digitalWrite(_rightEnablePin, 1);
    }
    digitalWrite(_leftEnablePin, 1);
    digitalWrite(_rightEnablePin, 1);
}

/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin    Pin for the data
  @param    numLeds       Number of leds
*/
/**************************************************************************/
L298NMotors::turn(int16_t deg, int8_t rad) {

}


/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin    Pin for the data
  @param    numLeds       Number of leds
*/
/**************************************************************************/
L298NMotors::rideDistance(int16_t distance) {

}

/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin    Pin for the data
  @param    numLeds       Number of leds
*/
/**************************************************************************/
L298NMotors::rideRoute() {

}