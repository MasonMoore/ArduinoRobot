/*
 * Mason Moore
 *
 *
 */
#ifndef RGB_H_INCLUDED
#define RGB_H_INCLUDED

//class for rgb
class RGB {
  public:
    RGB(uint8_t green_pin, uint8_t red_pin, uint8_t blue_pin);
   void red();
    void blue();
    void green();
    void yellow();
    void purple();
    void brown();
    void cyan();
    void custom(int red, int green, int blue);

  private:

    uint8_t led_green;
    uint8_t led_red;
    uint8_t led_blue;
  
};


#endif // RGB_H_INCLUDED
