/*
 * Mason Moore
 * 
 * 
 */


#include "HCSR04.h"
#include "WHEELS.h"
#include "RGB.h"
#include "pitches.h"
#include <Servo.h>

//declare possible states
enum {FORWARD, TURN, TURNINPLACE, REVERSE, STOP} state;
enum {RIGHT, LEFT} turn_state;

//declare rgb led (only digital writing)
RGB led_rgb(5,6,3);
//declare USR
HCSR04 ranger( 12, 13 );
//declare wheels
WHEELS wheels(11, 10);

#define SPEAKER_PIN 2
/*int notes[] = { NOTE_E6, NOTE_E6, NOTE_REST, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_G6, NOTE_REST, NOTE_G5, NOTE_REST, NOTE_C6, NOTE_REST, NOTE_G5, NOTE_REST, NOTE_E5, NOTE_REST, NOTE_A5, NOTE_B5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_E6, NOTE_G6, NOTE_A6, NOTE_F6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_D6, NOTE_B5, NOTE_REST, NOTE_C6, NOTE_REST, NOTE_G5, NOTE_REST, NOTE_E5, NOTE_REST, NOTE_A5, NOTE_B5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_E6, NOTE_G6, NOTE_A6, NOTE_F6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_D6, NOTE_B5, NOTE_REST, NOTE_G6, NOTE_FS6, NOTE_F6, NOTE_DS6, NOTE_REST, NOTE_E6, NOTE_REST, NOTE_GS5, NOTE_A5, NOTE_C6, NOTE_REST, NOTE_A5, NOTE_C6, NOTE_D6, NOTE_REST, NOTE_G6, NOTE_FS6, NOTE_F6, NOTE_DS6, NOTE_REST, NOTE_E6, NOTE_REST, NOTE_C7, NOTE_REST, NOTE_C7, NOTE_C7, NOTE_REST, NOTE_G6, NOTE_FS6, NOTE_F6, NOTE_DS6, NOTE_REST, NOTE_E6, NOTE_REST, NOTE_GS5, NOTE_A5, NOTE_C6, NOTE_REST, NOTE_A5, NOTE_C6, NOTE_D6, NOTE_REST, NOTE_DS6, NOTE_REST, NOTE_D6, NOTE_REST, NOTE_C6 };
int durations[] = { 2, 2, 1, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 2, 4, 2, 4, 4, 2, 4, 3, 2, 2, 4, 2, 4, 4, 2, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 4, 2, 4, 3, 2, 2, 4, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 4, 2, 4, 2 };
int song_length = sizeof( notes )/sizeof(int);

int tempo = 100; // beats per minutes
int note_delay = 60000/tempo/8; // milliseconds for a 32nd note
int pointer = 0;
*/

//declare distance variables
int distance = 0;
int newdistance =0;

//setup
void setup( void ) {
  //init wheels and offset
  wheels.set_offset(5, 5);
  wheels.init();
  //init states
  state = FORWARD; //start state
  turn_state = RIGHT;

  Serial.begin(9600);

}

void loop( void ) {

  //get distance from USR
  distance = ranger.measure();

  switch(state) {

    // -------------------------------------------------------------------------------------------------------
    // 
    case FORWARD:
    //go forward, else change state to turn
    if(distance >= 100){
      wheels.forward();
      led_rgb.green();
     /*tone( SPEAKER_PIN, notes[pointer], durations[pointer]*note_delay );
      delay( durations[pointer]*note_delay );
 pointer++;
      if(pointer > song_length){
        pointer = 0;
      }
      Serial.println(pointer);
     */
    }
    else{
      state = TURN;
    }

    break;
    
    // -------------------------------------------------------------------------------------------------------
    // TURN
    case TURN:
    //change to forward if threshold met
    if(distance >= 100){
      state = FORWARD;
    }
    //else chech substate to turn r or l
    else if(distance < 100 && distance >= 50){

      switch(turn_state){

        case RIGHT:
          wheels.turn_right(); 
         led_rgb.red();
         tone(SPEAKER_PIN, NOTE_D5, 100);
          delay(400);
          //check if new direction is closer or further
          newdistance = ranger.measure();
           if (newdistance < distance){
              turn_state = LEFT;
           }

        
        break;

        case LEFT:
          wheels.turn_left();
         led_rgb.blue();
         tone(SPEAKER_PIN, NOTE_D6, 100);
          delay(400);
          //check if new direction is closer or further
          newdistance = ranger.measure();
           if (newdistance < distance){
              turn_state = RIGHT;
           }


        break;
        
      }
    }
    else {
      //else if too close, change to turn in place
      state = TURNINPLACE;
    }
    break;
    
    // -------------------------------------------------------------------------------------------------------
    // TURNINPLACE
    case TURNINPLACE:
    //if threshold to high, change to turn
    if(distance >= 50){
      state = TURN;
    }
    else if(distance < 50 && distance >= 20){
        //else check direction and turn in place
        switch(turn_state){

        case RIGHT:
          wheels.right_in_place();
         led_rgb.red();
          tone(SPEAKER_PIN, NOTE_D5, 100);
          delay(100);
          //check if new direction is closer or further
          newdistance = ranger.measure();
           if (newdistance < distance){
              turn_state = LEFT;
           }
        
        break;

        case LEFT:
          wheels.left_in_place();
          led_rgb.blue();
           tone(SPEAKER_PIN, NOTE_D6, 100);
          delay(100);
          //check if new direction is closer or further
          newdistance = ranger.measure();
           if (newdistance < distance){
              turn_state = RIGHT;
           }

        break;
        
      }
    }
    else
    {
      //if threshold too close, reverse
      state = REVERSE;
    }
    break;

    // -------------------------------------------------------------------------------------------------------
    // REVERSE
    case REVERSE:
    //if threshold high enough, turn in place
    if(distance >= 20){
      state = TURNINPLACE;
    }
    else if(distance < 20){
      //else if too low, reverse
      wheels.reverse();
      led_rgb.purple();
       tone(SPEAKER_PIN, NOTE_A5, 500);
      delay(500);
      //check if new direction is closer or further, if stuck then stop
      newdistance = ranger.measure();
      if (newdistance < distance)
      {
        state = STOP;
      }
    }
    break;
    

    // -------------------------------------------------------------------------------------------------------
    // STOP
    case STOP:
    //if threshold high enough, reverse
    if(distance >= 10){
      state = REVERSE;
    }
    else{
    //else, stop in place and hope your programmer saves you
    wheels.stop_in_place();
      led_rgb.cyan();
         
      tone( SPEAKER_PIN, NOTE_C1, 500 );
      delay(100);
      tone( SPEAKER_PIN, NOTE_D2, 500 );
      delay(100);
      tone( SPEAKER_PIN, NOTE_E3, 500 );
      delay(100);
    }
    break;
    
  }

}

