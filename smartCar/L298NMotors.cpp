/*
 * File:      L298NMotors.ccp
 * Authors:   Luke de Munk
 * Class:     L298NMotors
 * Version:   1.0
 *
 * Library for controlling two motors with L298N driver.
*/
#include "L298NMotors.h"

#define PWM_FREQ              5000
#define PWM_RES               8       //8-bits PWM resolution
#define LEFT_PWM_CHAN         0
#define RIGHT_PWM_CHAN        1

#define PULSES_PER_ROTATION   20
#define CM_PER_ROTATION       22

/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin      Pin for the data
  @param    numLeds         Number of leds
*/
/**************************************************************************/
L298NMotors::L298NMotors(uint8_t leftEnablePin, uint8_t leftSpeedPin, 
                          uint8_t rightEnablePin, uint8_t rightSpeedPin,
                          uint8_t leftTachoPin, uint8_t rightTachoPin) {
  _leftEnablePin = leftEnablePin;
  _leftSpeedPin = leftSpeedPin;
  _rightEnablePin = rightEnablePin;
  _rightSpeedPin = rightSpeedPin;
  _leftTachoPin = leftTachoPin;
  _rightTachoPin = rightTachoPin;

  _leftPulseCounter = 0;
  _rightPulseCounter = 0;

  pinMode(_leftEnablePin, OUTPUT);
  pinMode(_rightEnablePin, OUTPUT);
  
  ledcSetup(LEFT_PWM_CHAN, PWM_FREQ, PWM_RES);
  ledcSetup(RIGHT_PWM_CHAN, PWM_FREQ, PWM_RES);
  
  ledcAttachPin(_leftSpeedPin, _leftPWMchannel);      // attach the channel to the GPIO to be controlled
  ledcAttachPin(_rightSpeedPin, _rightPWMchannel);    // attach the channel to the GPIO to be controlled
}

/**************************************************************************/
/*!
  @brief    Drive forwards.
  @param    speed           Speed of movement (0-255)
*/
/**************************************************************************/
void L298NMotors::forward(uint8_t speed) {
  uint8_t dutyCycle = speed;
  ledcWrite(LEFT_PWM_CHAN, dutyCycle);
  ledcWrite(RIGHT_PWM_CHAN, dutyCycle);
  digitalWrite(_leftEnablePin, 1);
  digitalWrite(_righttEnablePin, 1);
}

/**************************************************************************/
/*!
  @brief    Drive backwards.
  @param    speed           Speed of movement (0-255)
*/
/**************************************************************************/
void L298NMotors::backward(uint8_t speed) {
  uint8_t dutyCycle = speed;
  ledcWrite(LEFT_PWM_CHAN, dutyCycle);
  ledcWrite(RIGHT_PWM_CHAN, dutyCycle);
  digitalWrite(_leftEnablePin, 1);
  digitalWrite(_rightEnablePin, 1);
}

/**************************************************************************/
/*!
  @brief    Stop car.
*/
/**************************************************************************/
void L298NMotors::stop(){
  digitalWrite(_leftEnablePin, 0);
  digitalWrite(_rightEnablePin, 0);
  ledcWrite(LEFT_PWM_CHAN, 0);
  ledcWrite(RIGHT_PWM_CHAN, 0);
}

/**************************************************************************/
/*!
  @brief    Rotate car.
  @param    deg             Degrees (-180 - 180)
  @param    speed           Speed of movement (0-255)
*/
/**************************************************************************/
void L298NMotors::rotate(int16_t deg, uint8_t speed) {
  uint8_t dutyCycleL = speed;
  uint8_t dutyCycleR = speed;
  
  if (deg > 0) {
    ledcWrite(LEFT_PWM_CHAN, dutyCycle);
    ledcWrite(RIGHT_PWM_CHAN, dutyCycle); //ride backwards
  } else {
    ledcWrite(LEFT_PWM_CHAN, dutyCycle);  //ride backwards
    ledcWrite(RIGHT_PWM_CHAN, dutyCycle);
  }
  digitalWrite(_leftEnablePin, 1);
  digitalWrite(_rightEnablePin, 1);
  
}

/**************************************************************************/
/*!
  @brief    Turn car.
  @param    deg             Degrees (-180 - 180)
  @param    rad             Radius (in cm)
*/
/**************************************************************************/
void L298NMotors::turn(int16_t deg, int8_t rad) {
  uint8_t dutyCycleL = speed;
  uint8_t dutyCycleR = speed;
  
  if (deg > 0) {
    ledcWrite(LEFT_PWM_CHAN, dutyCycle);
    ledcWrite(RIGHT_PWM_CHAN, dutyCycle);
  } else {
    digitalWrite(_rightEnablePin, 1);
  }
  digitalWrite(_leftEnablePin, 1);
  digitalWrite(_rightEnablePin, 1);
}


/**************************************************************************/
/*!
  @brief    Drive car for specified distance.
  @param    distance        Destance (in cm)
  @param    speed           Speed of movement (0-255)
*/
/**************************************************************************/
void L298NMotors::rideDistance(int16_t distance, int8_t speed) {
  uint32_t neededpulses = abs(distance/CM_PER_ROTATION*PULSES_PER_ROTATION);
  
  if (distance > 0) {
    forward(speed);
  } else {
    backward(speed);
  }

  startSpeedEncoder();
  
  while(_leftPulseCounter >= neededRotations) continue;
  stop();
}

/**************************************************************************/
/*!
  @brief    Initialise the L298N driven motors.
  @param    dataOutPin    Pin for the data
  @param    numLeds       Number of leds
*/
/**************************************************************************/
void L298NMotors::rideRoute() {

}

/**************************************************************************/
/*!
  @brief    Enables speed encoder, generates interrupts.
  @param    side          Side to enable (default both)
                          Left = 0, Right = 1, Both = 2
*/
/**************************************************************************/
void L298NMotors::startSpeedEncoder(uint8_t side) {
  if (side == 0) {
    _leftPulseCounter = 0;
    attachInterrupt(_leftTachoPin, _lSpeedEncoderISR, FALLING);
  } else if (side == 1) {
    _rightPulseCounter = 0;
    attachInterrupt(_rightTachoPin, _rSpeedEncoderISR, FALLING);
  } else {
    _leftPulseCounter = 0;
    _rightPulseCounter = 0;
    
    attachInterrupt(_leftTachoPin, _lSpeedEncoderISR, FALLING);
    attachInterrupt(_rightTachoPin, _rSpeedEncoderISR, FALLING);
  }
}

/**************************************************************************/
/*!
  @brief    Disables speed encoder.
*/
/**************************************************************************/
void L298NMotors::stopSpeedEncoder() {
  _currentSpeed = 0;
  detachInterrupt(_leftTachoPin);
  detachInterrupt(_rightTachoPin);
}

/**************************************************************************/
/*!
  @brief    Left speed encoder ISR, adds pulse to counter and calculates
            the speed in cm/s.
*/
/**************************************************************************/
void L298NMotors::_lSpeedEncoderISR() {
  _leftPulseCounter++;
  Serial.println(_leftPulseCounter);
}

/**************************************************************************/
/*!
  @brief    Right speed encoder ISR, adds pulse to counter and calculates
            the speed in cm/s.
*/
/**************************************************************************/
void L298NMotors::_rSpeedEncoderISR() {
  _rightPulseCounter++;
}
