/*
 * Mason Moore
 *
 *
 */
 
#include <Arduino.h>
#include <Servo.h>
#include "WHEELS.h"

//default offsets
#define DEFAULT_OFFSETLEFT 0
#define DEFAULT_OFFSETRIGHT 0

//constructor for wheels
 WHEELS::WHEELS(uint8_t left_wheel_pin, uint8_t right_wheel_pin){
  left_wheel = left_wheel_pin;
  right_wheel = right_wheel_pin;
  
  pinMode(left_wheel, OUTPUT);
  pinMode(right_wheel, OUTPUT);

  set_offset(DEFAULT_OFFSETRIGHT, DEFAULT_OFFSETLEFT);
  initialized = true;
 }

//int for wheels (doesnt like to attach in constructor?)
 void WHEELS::init(){
  right_servo.attach(right_wheel);
  left_servo.attach(left_wheel);
 }

//@param, set offset for wheels
 void WHEELS::set_offset(int new_offset_right, int new_offset_left){
  offset_right = new_offset_right;
  offset_left =  new_offset_left;
 }

 //go forward
 void WHEELS::forward(void){
   //forward
   left_servo.write(180 + offset_left);
   right_servo.write(0 + offset_right);
 }

 //go backwards
 void WHEELS::reverse(void){
   //backward
   left_servo.write(0 + offset_left);
   right_servo.write(180 + offset_right);
 }

 //turn right
 void WHEELS::turn_right(){
     //right turn
   left_servo.write(180 + offset_left);
   right_servo.write(85 + offset_right);
 }

 //turn left
 void WHEELS::turn_left(){
   //left turn
   left_servo.write(95 + offset_left);
   right_servo.write(0 + offset_right); 
 }

 //stop in place
 void WHEELS::stop_in_place(){
  //stops the robot in place
  
   left_servo.write(90 + offset_left);
   right_servo.write(90 + offset_right);
 }

  //turn right in place
  void WHEELS::right_in_place(){
  //turns the robot right in place
   left_servo.write(135 + offset_left);
   right_servo.write(135 + offset_right);
 }

  //turn left in place
  void WHEELS::left_in_place(){
  //turns the robot left in place
   left_servo.write(45 + offset_left);
   right_servo.write(45 + offset_right);
 }

