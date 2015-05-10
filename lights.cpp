#include <Adafruit_NeoPixel.h>
#include "lights.h"

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, 6, NEO_GRB + NEO_KHZ800);//start the led strip


uint32_t BColor;                //the nackground color

int pos = 0;                    //posintion of the flashing
int j=0;                        //needed for rainbow
int q=0;                        //needed for rainbow




void LightsSetUp(){              //function to start led string
  strip.begin();                 //start the strip
  strip.show();                  // Initialize all pixels to 'off'
}

void SetBckGrndC(uint8_t r, uint8_t b, uint8_t g){//function to change the background color
  BColor = strip.Color(r,b,g);   //get the color as a single  uint32_t    
  for(int i=0;i < strip.numPixels();i++){//change all the leds to reflect the new color
     strip.setPixelColor(i,BColor);//set the led
  }
  strip.show();                  //show the change
  
}

void LightsOff(){                //turn off the led strip
  for(int i=0;i < strip.numPixels();i++){//run threw each led
     strip.setPixelColor(i,0);//and trun them off
    }
    strip.show();                //show the change
}

void AirCraftFlashB(){          //function to run the red green white chasing
  if(pos <= ARM_LED_COUNT+4){   //have we gone past the number of leds on the arm of the quad + the legnth of the dot
                                //no
    for(int i=0;i<DOT_SIZE;i++){       //lets tun 4 led for the green dot
      if(pos+i >=0){            //make sure that we arn't tunring a led on before the start of the strand
        //eraseing the last pixle for the colered dot
        setArm(0,pos-DOT_SIZE+i,BColor);
        setArm(1,pos-DOT_SIZE+i,BColor);
        setArm(2,pos-DOT_SIZE+i,BColor);
        setArm(3,pos-DOT_SIZE+i,BColor);
        //strip.setPixelColor(pos-DOT_SIZE+i,BColor);//erase the last green led
        if(pos+i < ARM_LED_COUNT){//position will go past the number of leds on the arm so that 
                                      //we can gently erase the dot. So we need to check to make sure we are still within the arm
          //setting the next pixe for the colored dot
          setArm(0,pos+i+1,strip.Color(0,255,0));    //for arm 1
          setArm(1,pos+i+1,strip.Color(255,0,0));    //arm 2
          setArm(2,pos+i+1,strip.Color(255,255,255));//arm 3
          setArm(2,pos+i+1,strip.Color(255,255,255));//arm 4
        }
      }
    }
     pos++;//incriment the postion counter
  }else{                      //we are at the end of the arm, we need to remove the last stuburn led
    
    pos = -DOT_SIZE;// set the position counter to before the arm for a gracfull entrence
  }
  strip.show();              //show the prettiness
  delay(40);//give it a puase
}

void RedGreenWhite(){
  for(int i=0;i < ARM_LED_COUNT;i++){//change all the leds to reflect the new color
      setArm(0,pos+i+1,strip.Color(0,255,0));    //for arm 1
      setArm(1,pos+i+1,strip.Color(255,0,0));    //arm 2
      setArm(2,pos+i+1,strip.Color(255,255,255));//arm 3
      setArm(2,pos+i+1,strip.Color(255,255,255));//arm 4
  }
  strip.show();
}

void setArm(int arm,int led, uint32_t color){
  int p = arm * (ARM_LED_COUNT*2) + led;
  strip.setPixelColor(p,color);//set the led
  p += ARM_LED_COUNT;
  strip.setPixelColor(p,color);//set the led
}

//Theatre-style crawling lights with rainbow effect
//stolen from Adafruits example code. I modified it so that it is non blocking
void theaterChaseRainbow() {
  if(j < 256){  // cycle all 256 colors in the wheel
    j++;
    if(q<3){
      q++;
         for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(80);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }else{
     q=0; 
    }
  }else{
    j=0;
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
