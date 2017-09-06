//Borrowed from class notes*
#include <Arduino.h>
#include "HCSR04.h"

#define HCSR04_TIMEOUT 1000000  // us (= 1 s)

#define HCSR04_DEFAULT_SOUND_SPEED 0.0347932  // cm/us (= 347.932 m/s)
#define HCSR04_DEFAULT_OFFSET 0.7             // cm (= 0.007 m)

/* float HCSR04::measure( void );
 *
 * Returns:
 *   if obstacle detected, distance in cm
 *   if no obstacle, 0.0
 */
float HCSR04::measure( void ) {
  if( !initialized ) {
    return 0.0;
  }

  unsigned long duration = 0;

  // make sure we have a nice clean rising edge
  digitalWrite( trigger, LOW );
  delayMicroseconds( 2 );  // let it settle

  // the trigger pulse must last 10 us
  digitalWrite( trigger, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( trigger, LOW );

  duration = pulseIn( echo, HIGH, HCSR04_TIMEOUT );

  return duration*sound_speed/2.0 + offset;
}


/* HCSR04::HCSR04( uint8_t trigger_pin, uint8_t echo_pin );
 *
 * Parameters:
 *   uint8_t trigger_pin        trigger pin number
 *   uint8_t echo_pin           echo pin number
 */
HCSR04::HCSR04( uint8_t trigger_pin, uint8_t echo_pin ) {
  trigger = trigger_pin;
  echo = echo_pin;

  sound_speed = HCSR04_DEFAULT_SOUND_SPEED;
  offset = HCSR04_DEFAULT_OFFSET;

  pinMode( trigger, OUTPUT );
  pinMode( echo, INPUT );

  set_calibration( HCSR04_DEFAULT_SOUND_SPEED, HCSR04_DEFAULT_OFFSET );

  initialized = true;
}


/* void HCSR04::set_calibration( float new_sound_speed, float new_offset );
 *
 * Parameters:
 *   float new_sound_speed        speed of sound in cm/us
 *   float new_offset             offset in cm
 */
void HCSR04::set_calibration( float new_sound_speed, float new_offset ) {
  sound_speed = new_sound_speed;
  offset = new_offset;
}

