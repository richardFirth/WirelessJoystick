
 // 11/8/17
 /*
 code 
 part of series
 
 // use sparkfun wireless joystick kit with my code, and have an XBee explorer hooked your computer
 
 https://www.sparkfun.com/products/14051 <- joystick
 https://www.sparkfun.com/products/11812 <- explorer
 
 */
 
 
import processing.serial.*;
Serial myPort;
SerialConnector sc;





byte theInput[];

boolean UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON,L_TRIG,R_TRIG,JOYSTICK_BUTTON;
boolean batteryOK;


float rawH = 512,rawV = 512;

float baTTval = 100;

float HOffSet,VOffSet = 0;
float controllerWidth = 516;
float controllerHeight = 258; //280;


void setup() {
  
  size(640, 640);
  sc = new SerialConnector(this,myPort);
  sc.listPorts();  
    //Set up serial - modify COM to your com
  // myPort.bufferUntil('\n');                // DONT buffer until newline
  

  
  
}


void draw() {
 
  
  if (sc.isConnected){
   background(50,60,50); 
  } else {
   background(60,50,50);  
   sc.isConnected = false;
  }

  drawController();
  drawButtons();
  drawLeftJoystick(); 
  //drawRightJoystick(); 
  drawBattery();
  
  sc.drawToScreen();
  
  delay(5);

}


void drawController()
{
  rectMode(CENTER);
  fill(200,100,100);
  rect(width/2,height/2, controllerWidth, controllerHeight, 7);
}

void drawButtons()
{

 if (UP_BUTTON) {  fill(10,10,250); } else { fill(250,250,250); }
  rect(width/2+controllerWidth/4,height/2-50, 35, 35, 3);
 if (DOWN_BUTTON) {  fill(250,250,10); } else { fill(250,250,250); }
  rect(width/2+controllerWidth/4,height/2+50, 35, 35, 3);
  
 if (LEFT_BUTTON) {  fill(10,250,10); } else { fill(250,250,250); }
  rect(width/2+controllerWidth/4-50,height/2, 35, 35, 3);
 if (RIGHT_BUTTON) {  fill(250,10,10); } else { fill(250,250,250); }
  rect(width/2+controllerWidth/4+50,height/2, 35, 35, 3);

 if (L_TRIG) {  fill(10,250,250); } else { fill(250,250,250); }
  rect(width/2-105,(height-controllerHeight)/2, 55, 15, 3);
 if (R_TRIG) {  fill(10,250,250); } else { fill(250,250,250); }
  rect(width/2+105,(height-controllerHeight)/2, 55, 15, 3);
 
}


void drawLeftJoystick()
{
  if (JOYSTICK_BUTTON) {  fill(10,250,10); } else { fill(250,250,250); }
  ellipse(width/2-controllerWidth/4,height/2, 135, 135);
  
  HOffSet = map(rawH, 0, 1023,40, -40);
  VOffSet = map(rawV,0, 1023, 40, -40);
  
  fill(10,10,10);
  ellipse(width/2-controllerWidth/4+HOffSet,height/2+VOffSet, 35, 35);
}


void drawRightJoystick()
{
  if (JOYSTICK_BUTTON) {  fill(10,250,10); } else { fill(250,250,250); }
  ellipse(width/2+controllerWidth/4,height/2, 135, 135);
  
  HOffSet = map(rawH, 0, 1023,40, -40);
  VOffSet = map(rawV, 0, 1023, 40, -40);
  
  fill(10,10,10);
  ellipse(width/2+controllerWidth/4+HOffSet,height/2+VOffSet, 35, 35);
}


void drawBattery()
{
  if (batteryOK) { baTTval = 100;} else {  baTTval = 50; }
  
  rectMode(CORNER);
  fill(250,250,250);
  rect(width/2-25,75,50,25);
  fill(250,20,20); 
  if (baTTval > 50) { fill(250,250,20); }
  if (baTTval > 75) { fill(20,250,20); }
  rect(width/2-25,75,baTTval/2,25);
  
}



void keyPressed() {
 
  sc.KeyInputforConnection(key);
}
  
  
  
  