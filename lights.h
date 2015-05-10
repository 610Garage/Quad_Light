#ifndef lights_h
  #define lights_h
  
  #include <Adafruit_NeoPixel.h>
  
  #define ARM_LED_COUNT 13
  #define DOT_SIZE 3
 
  
  void LightsSetUp();
  void SetBckGrndC(uint8_t r, uint8_t b, uint8_t g);
  void LightsOff();
  void AirCraftFlashB();
  void RedGreenWhite();
  void setArm(int arm,int led, uint32_t color);
  void theaterChaseRainbow();
  uint32_t Wheel(byte WheelPos);
#endif
