/* Wireless Joystick Buttons
 *  
 *  use board SAMD DEV 21 Breakout
 *  
 *  THIS CODE GOES ON THE JOYSTICK
 *  
 * 2/4/17
 * license: Creative Commons Attribution-ShareAlike 4.0 (CC BY-SA 4.0)
 * Do whatever you'd like with this code, use it for any purpose.
 * Please attribute and keep this license. 
 * 
 * This is example code for the Sparkfun Wireless Joystick using XBee. 
 * Modified from the tank code found here https://learn.sparkfun.com/tutorials/wireless-joystick-hookup-guide
 * 
                                           X
                                         Y   A
                                           B
 */

#define UP_BUTTON 8 // X
#define DOWN_BUTTON 2 // B
#define LEFT_BUTTON 4 // Y
#define RIGHT_BUTTON 9 // A

#define L_TRIG 6        // Pin used for left trigger
#define R_TRIG 3        // Pin used for right trigger

#define JOYSTICK_BUTTON 5 // joystick button

#define V_JOYSTICK A3   // Pin used for vertical
#define H_JOYSTICK A2   // horizontal


// Battery Monitor

#include <Wire.h>
#define MAX17043_ADDRESS 0x36  // R/W =~ 0x6D/0x6C

// Pin definitions
int alertPin = 7;  // This is the alert interrupt pin, connected to pin 7 on the Wireless Joystick
// Global Variables
float batVoltage;
float batPercentage;
int alertStatus;

int n = 0; // start with high battery

void setup() {  
  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  delay(10);
  Serial1.print("W7001\r\n"); // Set the bit in enable register 0x70 to 0x01

  pinMode(L_TRIG,INPUT_PULLUP); // Enable pullup resistors
  pinMode(R_TRIG,INPUT_PULLUP); 
  pinMode(UP_BUTTON,INPUT_PULLUP);
  pinMode(DOWN_BUTTON,INPUT_PULLUP);
  pinMode(LEFT_BUTTON,INPUT_PULLUP);
  pinMode(RIGHT_BUTTON,INPUT_PULLUP);
  pinMode(JOYSTICK_BUTTON,INPUT_PULLUP);

// Battery Monitor
  Wire.begin();  // Start I2C
  configMAX17043(32);  // Configure the MAX17043's alert percentage
  qsMAX17043();  // restart fuel-gauge calculations

  batPercentage = percentMAX17043(); // start with correct battery
}

void loop() {
  
  int16_t horizontalJS, verticalJS; //   Store the the analog joystick values here
  char hor[10],vert[10]; // for the horizontal and vertical things
  char buttonStateBuf[9]; // for the button states
  
  buttonStateBuf[0] = 'J';
 (digitalRead(L_TRIG)==0) ? buttonStateBuf[1] = '1' : buttonStateBuf[1] = '0';
 (digitalRead(R_TRIG)==0) ? buttonStateBuf[2] = '1' : buttonStateBuf[2] = '0';
 (digitalRead(UP_BUTTON)==0) ? buttonStateBuf[3] = '1' : buttonStateBuf[3] = '0';
 (digitalRead(DOWN_BUTTON)==0) ? buttonStateBuf[4] = '1' : buttonStateBuf[4] = '0';
 (digitalRead(LEFT_BUTTON)==0) ? buttonStateBuf[5] = '1' : buttonStateBuf[5] = '0';
 (digitalRead(RIGHT_BUTTON)==0) ? buttonStateBuf[6] = '1' : buttonStateBuf[6] = '0';
 (digitalRead(JOYSTICK_BUTTON)==0) ? buttonStateBuf[7] = '1' : buttonStateBuf[7] = '0';
  buttonStateBuf[8]='\0'; // this is the null character. this tells other stuff the char array is at the end. (in case you didn't know.)
  
horizontalJS = analogRead(H_JOYSTICK);
verticalJS = analogRead(V_JOYSTICK);

sprintf(hor,",%d",horizontalJS);
sprintf(vert,",%d",verticalJS);

Serial1.print(buttonStateBuf);
Serial1.print(hor);
Serial1.print(vert);
Serial1.print(",");
Serial1.println(batPercentage);
 delay(8);
 n++;

 if (n==1000) {
  n=0;
  batPercentage = percentMAX17043(); // we don't need to check the battery percentage constantly, so lets just do it every 8 seconds or so
 }
}

