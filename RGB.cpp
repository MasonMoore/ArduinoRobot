/*
 * Mason Moore
 *
 *
 */

#include <Arduino.h>
#include "RGB.h"

//constructor, @param get pins for rgb led, set pinmodes to output
RGB::RGB(uint8_t green_pin, uint8_t red_pin, uint8_t blue_pin){
  led_green = green_pin;
  led_red = red_pin;
  led_blue = blue_pin;
  
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
}

//output red
void RGB::red(){
  digitalWrite(led_green, LOW);
  digitalWrite(led_red, HIGH);
  digitalWrite(led_blue, LOW);
}
//output blue
void RGB::blue(){
  digitalWrite(led_green, LOW);
  digitalWrite(led_red, LOW);
  digitalWrite(led_blue, HIGH);
}
//output green
void RGB::green(){
  digitalWrite(led_green, HIGH);
  digitalWrite(led_red, LOW);
  digitalWrite(led_blue, LOW);
}
//output yellow
void RGB::yellow(){
  digitalWrite(led_green, HIGH);
  digitalWrite(led_red, LOW);
  digitalWrite(led_blue, HIGH);
}

//output purple
void RGB::purple(){
  digitalWrite(led_green, LOW);
  digitalWrite(led_red, HIGH);
  digitalWrite(led_blue, HIGH);
}

//output purple
void RGB::brown(){
  digitalWrite(led_green, HIGH);
  digitalWrite(led_red, HIGH);
  digitalWrite(led_blue, LOW);
}

//output cyan
void RGB::cyan(){
    digitalWrite(led_green, HIGH);
  digitalWrite(led_red, HIGH);
  digitalWrite(led_blue, HIGH);
}

void RGB::custom(int red, int green, int blue){
  red = constrain(red, 0, 255);
  blue = constrain(blue, 0, 255);
  green = constrain(green, 0, 255);
  
  analogWrite(led_red, red);
  analogWrite(led_green, green);
  analogWrite(led_blue, blue);
}
