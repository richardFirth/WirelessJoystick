

// input form J0000000,1023,1023,95.1
// http://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string


void getLatestData()
{
  
  if (XBee.available() > 0)
  {
    char theInput[30];
    
        while(XBee.available() > 0) { char c = XBee.read(); }   // clear everything in the XBee buffer   
        delay(20); // wait for more stuff to come in
        XBee.readStringUntil('\n'); //this clears out whatevers left over (return value goes nowhere)      
        int numCharsRecieved = XBee.readBytesUntil('\n', theInput, 29); // this reads the bytes and returns the number of them
        theInput[numCharsRecieved]='\0';  // http://forum.arduino.cc/index.php?topic=166959.0
      
              if(theInput[0] == 'J')
              {
              char * pch;
              //Serial.println(theInput);
              
              pch = strtok(theInput,","); // http://www.cplusplus.com/reference/cstring/strtok/
              // strtok is pretty weird. I don't really know how it works to be honest.
                parseButtonValues(pch);
              pch = strtok(NULL, ","); 
                horizontalValue= atoi(pch);
              pch = strtok(NULL, ",");
                verticalValue= atoi(pch);
              pch = strtok(NULL, ",");
                batteryPercentage = atof(pch);
              }
        /*
         while (pch != NULL)
          {
            Serial.println(pch);
            pch = strtok(NULL, ",");
          }     
        */
  }                     
}


// http://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string
// http://forum.arduino.cc/index.php?topic=166959.0 // null terminating the input


void parseButtonValues(char buttonValues[])
{
  
  (buttonValues[1] == '1') ? L_TRIG = true : L_TRIG = false;
  (buttonValues[2] == '1') ? R_TRIG = true : R_TRIG = false;
  (buttonValues[3] == '1') ? UP_BUTTON = true : UP_BUTTON = false;
  (buttonValues[4] == '1') ? DOWN_BUTTON = true : DOWN_BUTTON = false;
  (buttonValues[5] == '1') ? LEFT_BUTTON = true : LEFT_BUTTON = false;
  (buttonValues[6] == '1') ? RIGHT_BUTTON = true : RIGHT_BUTTON = false;
  (buttonValues[7] == '1') ? JOYSTICK_BUTTON = true : JOYSTICK_BUTTON = false;

}





