



// @@@@@@ #include statements to bring in libraries @@@@@@
   #include <SoftwareSerial.h> // for communicating with the XBee


// @@@@@@ #define statements for Pin values @@@@@@
   #define XBEE_RX 2   //RX Pin For Software Serial
   #define XBEE_TX 3   //TX Pin For Software Serial


SoftwareSerial XBee(XBEE_RX,XBEE_TX); // RX, TX
boolean UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON,L_TRIG,R_TRIG,JOYSTICK_BUTTON;
int verticalValue = 512, horizontalValue=512;
boolean JoystickBatteryGood;




void setup() {

   Serial.begin(9600);
   Serial.println(F("WJK_Reciever_Generic"));
   Serial.println(F("Last Modified 28Oct2017"));
   XBee.begin(9600);
// @@@@@@ set mode of input pins @@@@@@
// @@@@@@ set mode of output pins @@@@@@
delay(500);
}



void loop() {
   getLatestXBeeData();
   if (UP_BUTTON) {}
   if (DOWN_BUTTON) {}
   if (LEFT_BUTTON) {}
   if (RIGHT_BUTTON) {}
   if (JOYSTICK_BUTTON) {}
   if (L_TRIG) {}
   if (R_TRIG) {}
}
