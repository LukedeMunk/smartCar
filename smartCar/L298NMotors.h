/*
 * File:      L298NMotors.h
 * Authors:   Luke de Munk
 * Class:     L298NMotors
 * Version:   1.0
 * 
 * Library for controlling two motors with L298N driver.
 */
#ifndef L298NMotors_H
#define L298NMotors_H
#include <stdint.h>

class L298NMotors
{
  public:
    L298NMotors(uint8_t leftEnablePin, uint8_t leftSpeedPin, 
                          uint8_t rightEnablePin, uint8_t rightSpeedPin,
                          uint8_t leftTachoPin, uint8_t rightTachoPin);
  
    void forward(uint8_t speed);
    void backward(uint8_t speed);
    void stop();
    void rotate(int16_t deg, int8_t speed = 50);
    void turn(int16_t deg, int8_t rad, int8_t speed = 50);
  
    void rideDistance(int16_t distance);
    void rideRoute();
  
    void startSpeedEncoder(uint8_t side = 2);
    void stopSpeedEncoder();

  private:
    void _lSpeedEncoderISR();
    void _rSpeedEncoderISR();
    
    uint8_t _leftEnablePin;
    uint8_t _leftSpeedPin;
    uint8_t _rightEnablePin;
    uint8_t _rightSpeedPin;

    uint8_t _leftTachoPin;
    uint8_t _rightTachoPin;

    uint64_t _leftPulseCounter;
    uint64_t _rightPulseCounter;
    int16_t _currentSpeed;
};
#endif
