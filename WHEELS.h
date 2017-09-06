/*
 * Mason Moore
 *
 *
 */
 
#ifndef WHEELS_H_INCLUDED
#define WHEELS_H_INCLUDED
#include <Servo.h>

//class for wheels
class WHEELS {
  public:
    WHEELS( uint8_t left_wheel_pin, uint8_t right_wheel_pin);
    void init();
    void set_offset(int new_offset_right, int new_offset_left);
    void forward();
    void reverse();
    void turn_right();
    void turn_left();
    void stop_in_place();
    void right_in_place();
    void left_in_place();

  private:
    bool initialized;

    //pin configuration
    uint8_t left_wheel;
    uint8_t right_wheel;

    //offsets
    int offset_right;
    int offset_left;

    //Servos
    Servo right_servo;
    Servo left_servo;
  
};

#endif  // WHEELS_H_INCLUDED
