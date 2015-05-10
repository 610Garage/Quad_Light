#include <Adafruit_NeoPixel.h>
#include "lights.h"

#define MAX_TYPES 3



int servo = 0;            //current servo timing
int oldServo = 0;         //last servo timing
int Type = 0;             //type of effect to play
int State = 0;            //wich position is the switch at
int count = 0;            //keep track of how many times we checked the servo timing
bool on = 1;              //led state

void setup()
{
   LightsSetUp();          //start up the leds
   //Serial.begin(9600);    //debug
   SetBckGrndC(255,255,255);//set the background to white
}

void loop()
{
  if(count = 10){          //should we check the servo timing
    
    noInterrupts();         //this is time sensitive, lets stop inturrupts so that we don't get distracted
    while(!digitalRead(2)); //weight for the rising edge
    while(digitalRead(2)){  //while the pulse is high
      servo++;              //incriment the servo counter
    }
    interrupts();           //start the inturpts back up
    count = 0;              //reset the counter
  }
  count++;                  //incriment the counter
  
  if(oldServo != servo){    //is it worth checking the servo states
      if(servo < 250 && State != 0){//if the servo is at the lower position and this isn't a repeat
        //Serial.println(Type);  //debug  
        State = 0;          //set the state so that we don't continusly enter this statement
        if(Type > MAX_TYPES){//have we reach the maximum amount of types  
           Type = 0;        //yes, lets og back to the first type
        }else{
          Type++;           //no, incriment the type position
        }
        on = 1;             //make sure the leds are on
      }else if(servo > 400 && State != 1){//if the state is at the higher position and this isn't a repeat
        State = 1;          //set the state so that we don't continusly enter this statement
        on = 1;             //make sure the leds are on
      }else if(State != 2 && servo < 350 && servo > 300){//check to see that the servo is at the medium position and its no a repeat
        State = 2;          //set the state so that we don't continusly enter this statement
        on = 0;             //turn on the leds
      }
    }
      oldServo = servo;     //the new servoe state is now the old servo state
      servo = 0;            //reset the servo counter

   
  
  if(on){                   //should the lights be on
    switch(Type){           //find out whate effect we should play  
      case 0:               //red and green flashing
         SetBckGrndC(255,255,255);//set the background color
         AirCraftFlashB();  //run the effect
      break;                //nothing else to check, sto the switch case
      case 1:               //red green white flashing, no background
        SetBckGrndC(0,0,0);  //set the background color
        AirCraftFlashB();   //run the effect
      break;                //nothing else to check, sto the switch case
      case 2:               //perdy rainbow effect
        theaterChaseRainbow();//start the effect
      break;                //confusion, all white
      case 3:               //stedy red green white
        RedGreenWhite();    //start the effect
      break;                //nothing else to check, sto the switch case
      default: 
        SetBckGrndC(255,255,255);//set the background
      break;                //nothing else to check, sto the switch case
    }
  }else{//on == off
    LightsOff();//turn off the leds
  }
   
}

