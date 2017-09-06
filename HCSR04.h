//Borrowed from class notes*
#ifndef HCSR04_H_INCLUDED
#define HCSR04_H_INCLUDED

class HCSR04 {
  public:
    HCSR04( uint8_t trigger_pin, uint8_t echo_pin );
    float measure( void );
    void set_calibration( float new_speed_of_sound, float new_offset );

  private:
    bool initialized;

    // pin configuration
    uint8_t trigger;
    uint8_t echo;

    // calibration
    float sound_speed; // cm/us
    float offset;      // cm
};

#endif  // HCSR04_H_INCLUDED

