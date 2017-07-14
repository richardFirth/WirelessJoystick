


// serial stuff arrives in format "JXXXXXXX,1021,216,91.31"
//


void serialEvent (Serial myPort)
{
  serialInputString = myPort.readStringUntil('\n'); //Gets val
  processStrings(serialInputString);
}

/*
void testSerialEvent()
{
  processStrings("J0000000,1021,216,91.31");

}
*/
void processStrings(String theInput)
{
  if (theInput.charAt(0) == 'J') { 
  String theValues[] = split(theInput,",");

parseButtonValues(theValues[0]);
rawH = float(theValues[1]);
rawV = float(theValues[2]);
baTTval= float(theValues[3]);
}

}

void parseButtonValues(String buttonValues)
{
  if (buttonValues.charAt(1) == '1') {L_TRIG = true;} else {L_TRIG = false;}
  if (buttonValues.charAt(2) == '1') {R_TRIG = true;} else {R_TRIG = false;}
  if (buttonValues.charAt(3) == '1') {UP_BUTTON = true;} else {UP_BUTTON = false;}
  if (buttonValues.charAt(4) == '1') {DOWN_BUTTON = true;} else {DOWN_BUTTON = false;}
  if (buttonValues.charAt(5) == '1') {LEFT_BUTTON = true;} else {LEFT_BUTTON = false;}
  if (buttonValues.charAt(6) == '1') {RIGHT_BUTTON = true;} else {RIGHT_BUTTON = false;}
  if (buttonValues.charAt(7) == '1') {JOYSTICK_BUTTON = true;} else {JOYSTICK_BUTTON = false;}
}