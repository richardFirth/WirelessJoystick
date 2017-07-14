/*
Generic response of arduino shield.

idea is that every arduino sketch doesn't always need the input from the joystick at the same rate 
as the joystuck is sending, so we just want to grab the latest joystick values from the xbee

*/
//Servo Potentiometer Control

#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX

#define delayAmount 1250

boolean UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON,L_TRIG,R_TRIG,JOYSTICK_BUTTON;
int verticalValue, horizontalValue;
float batteryPercentage;

void setup()
{

    Serial.begin(9600);
    XBee.begin(9600);
    Serial.println("GenericArduino_XBee");

}

void loop()
{

    delay(delayAmount);   // do whatever it is that we are doing
    getLatestData();
    outPutLatestData();
  
}

void outPutLatestData()
{
   (L_TRIG) ? Serial.print("X") : Serial.print("x");
   (R_TRIG) ? Serial.print("X") : Serial.print("x");
   (UP_BUTTON) ?  Serial.print("X") : Serial.print("x");
   (DOWN_BUTTON) ?  Serial.print("X") : Serial.print("x");
   (LEFT_BUTTON) ?  Serial.print("X") : Serial.print("x");
   (RIGHT_BUTTON) ? Serial.print("X") : Serial.print("x");
   (JOYSTICK_BUTTON) ?  Serial.println("X") : Serial.println("x");
  
  Serial.print("Horizontal: ");
  Serial.println(horizontalValue);
  Serial.print("Vertical: ");
  Serial.println(verticalValue);
  Serial.print("Battery Percentage: ");
  Serial.println(batteryPercentage);

  
}


