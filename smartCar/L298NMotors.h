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


class L298NMotors
{
  public:
    L298NMotors(uint8_t leftEnablePin, uint8_t leftSpeedPin, uint8_t rightEnablePin, uint8_t rightSpeedPin);

    forward(uint8_t speed);
    backward(uint8_t speed);
    stop();
    rotate(int16_t deg, int8_t speed = 50);
    turn(int16_t deg, int8_t rad, int8_t speed = 50);

    rideDistance(int16_t distance);
    rideRoute();

  private:
    uint8_t _leftEnablePin;
    uint8_t _leftSpeedPin;
    uint8_t _rightEnablePin;
    uint8_t _rightSpeedPin;
};
#endif