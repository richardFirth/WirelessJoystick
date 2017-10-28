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

int battReportTimer;

int delayTimeForSend = 10;


void setup() {  
  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  delay(10);
  Serial1.print("W7001\r\n"); // Set the bit in enable register 0x70 to 0x01
  /*
  SerialUSB.begin(9600);  // Start hardware SerialUSB
  delay(5000);
  SerialUSB.println("Hello World");
*/

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
    battReportTimer++;
    // check battery voltage every 1000 loops (
    if (battReportTimer==1000) {
      batPercentage = percentMAX17043(); // we don't need to check the battery percentage constantly, so lets just do it every 8 seconds or so
      battReportTimer=0;
    }
   /*
    * intent is to use two bytes sent out in an alternate pattern to show the state of the buttons and
    * joystick at any given time
    * 
    * the recieving project should be able to parse the bytes to know the joystick values.
    * since this code just outputs the JS state, you won't need to change it for each project.
    * 
    */
   sendButtonValues();
   sendJSValues();
   
}


void sendButtonValues()
{
/* send byte of the form
 * (left to right 
 *  
 *  7: always 0
 *  6: Joystick button state
 *  5: Left Trigger State
 *  4: Right trigger state
 *  3: up button state
 *  2: down button state
 *  1: left button state
 *  0: right button state
 */
  byte toBeSent = customByte(false,(digitalRead(JOYSTICK_BUTTON)==0),(digitalRead(L_TRIG)==0),(digitalRead(R_TRIG)==0),(digitalRead(UP_BUTTON)==0),(digitalRead(DOWN_BUTTON)==0),(digitalRead(LEFT_BUTTON)==0),(digitalRead(RIGHT_BUTTON)==0) );
  Serial1.write(toBeSent);
  delay(delayTimeForSend);
}


void sendJSValues()
{
/* send byte of the form
 * (left to right 
 *  
 *  7: always 1
 *  6: battery state (1 for good, 0 for lower than 75%)
 *  5: Horizontal value
 *  4: Horizontal value
 *  3: Horizontal value
 *  2: Vertical Value
 *  1: Vertical Value
 *  0: Vertical Value
 */

  // mapped from 1 so that 4 will be in the middle. if i used 0 to 7 there would be 8 values and the 'at rest' would fall on the border of 3 and 4
  byte HVal = getJSByte(analogRead(H_JOYSTICK)); // (value from 1 to 7) 
  byte VVal = getJSByte(analogRead(V_JOYSTICK));

  byte toBeSent = customByte(true,(batPercentage > 75),isSet(HVal,2),isSet(HVal,1),isSet(HVal,0),isSet(VVal,2),isSet(VVal,1),isSet(VVal,0));
  Serial1.write(toBeSent);
  delay(delayTimeForSend);  
}

byte getJSByte(int theRawRead){
  if (theRawRead < 146) return 1;
  if (theRawRead < 292) return 2;
  if (theRawRead < 438) return 3;
  if (theRawRead < 584) return 4;
  if (theRawRead < 729) return 5;
  if (theRawRead < 876) return 6;
  return 7;
}





