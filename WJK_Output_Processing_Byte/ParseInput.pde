
// two different flavors of bytes are sent. 

// first kind starts has leftmost bit as zero, and 7 bits corresponding to buttons
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

// second kind has vertical and horizontal values in 3 bits each, and battery good/bad in one bit.
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


void serialEvent (Serial myPort)
{
  theInput = myPort.readBytes(); //Gets val
  processInputs(theInput[0]);

  // printByte(theInput[0]);
}

void processInputs(byte processInput)
{

  if (isClear(processInput, 7)) {
    JOYSTICK_BUTTON = isSet(processInput, 6);
    L_TRIG = isSet(processInput, 5);
    R_TRIG = isSet(processInput, 4);
    UP_BUTTON = isSet(processInput, 3);
    DOWN_BUTTON = isSet(processInput, 2);
    LEFT_BUTTON = isSet(processInput, 1);
    RIGHT_BUTTON = isSet(processInput, 0);
  }

  if (isSet(processInput, 7)) {

    byte H_val = customByte(false, false, false, false, false, isSet(processInput, 5), isSet(processInput, 4), isSet(processInput, 3));
    byte V_val = customByte(false, false, false, false, false, isSet(processInput, 2), isSet(processInput, 1), isSet(processInput, 0));
    rawH = unpackJoystick(H_val);
    rawV = unpackJoystick(V_val);
    batteryOK = isSet(processInput, 6);
  }
}


void parseButtonValues(String buttonValues)
{
  if (buttonValues.charAt(1) == '1') {
    L_TRIG = true;
  } else {
    L_TRIG = false;
  }
  if (buttonValues.charAt(2) == '1') {
    R_TRIG = true;
  } else {
    R_TRIG = false;
  }
  if (buttonValues.charAt(3) == '1') {
    UP_BUTTON = true;
  } else {
    UP_BUTTON = false;
  }
  if (buttonValues.charAt(4) == '1') {
    DOWN_BUTTON = true;
  } else {
    DOWN_BUTTON = false;
  }
  if (buttonValues.charAt(5) == '1') {
    LEFT_BUTTON = true;
  } else {
    LEFT_BUTTON = false;
  }
  if (buttonValues.charAt(6) == '1') {
    RIGHT_BUTTON = true;
  } else {
    RIGHT_BUTTON = false;
  }
  if (buttonValues.charAt(7) == '1') {
    JOYSTICK_BUTTON = true;
  } else {
    JOYSTICK_BUTTON = false;
  }
}

float unpackJoystick(byte JSVal)
{
  if (JSVal==1) return 0;
  if (JSVal==2) return 220;
  if (JSVal==3) return 365;
  if (JSVal==4)  return 512;
  if (JSVal==5) return 657;
  if (JSVal==6) return 803;
  //if (JSVal==7)
  return 1023;
}