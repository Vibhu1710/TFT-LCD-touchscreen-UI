#include <UTFT.h> 
#include <URTouch.h>
//==== Creating Objects
UTFT    myGLCD(SSD1289,38,39,40,41); //Parameters should be adjusted to your Display/Schield model
URTouch  myTouch( 6, 5, 4, 3, 2);
//==== Defining Variables
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern unsigned int bird01[0x41A];
int x, y;
char currentPage, selectedUnit;
//Ultrasonic Sensor
const int VCC = 13;
const int trigPin = 11;
const int echoPin = 12;
long duration;
int distanceInch, distanceCm;
// RGB LEDs
const int redLed = 10;
const int greenLed = 9;
const int blueLed = 8;
int xR=176;
int xG=143;
int xB=176;
// Floppy Bird
int xP = 242;
int yP = 100;
int yB = 100;
int fallRateInt = 0;
float fallRate =0;
int score=0;
const int button = 14;
int buttonState = 0;
void setup() {
// Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  // Defining Pin Modes
  pinMode(VCC, OUTPUT); // VCC
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(button, INPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(VCC, HIGH); // +5V - Pin 13 as VCC
  currentPage = '0'; // Indicates that we are at Home Screen
  selectedUnit = '0'; // Indicates the selected unit for the first example, cms or inches
}
void loop() { 
 myGLCD.setBackColor(0,0,0); // Sets the background color of the area where the text will be printed to black
  //myGLCD.setColor(255, 255, 255); // Sets color to white
  //myGLCD.setFont(BigFont); // Sets font to big
  //myGLCD.print("Arduino TFT Tutorial", CENTER, 10); // Prints the string on the screen
  myGLCD.setColor(255,165, 0); // Sets color to yellow
  myGLCD.fillRoundRect (2,2,115, 40); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (2, 2, 115, 40); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(255,165, 0); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("RESET",20, 12); // Prints the string
  
  // Button - RGB LED Control
  myGLCD.setColor(16, 167, 103);
  myGLCD.fillRoundRect (204, 2, 317, 40);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (204, 2, 317, 40);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16, 167, 103);
  myGLCD.print("PICK",229, 12);

  touchPad();
  onlyRed();
  onlyGreen();
  onlyFrame();
  onlyLine();
  onlyBlue();
  onlyScroll();

  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect(10,53,26,228);
   
   if(myTouch.dataAvailable()) {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    if(x>=1&&x<=31&&y>=yB-9&&y<=yB+9)
    drawScroll();
    else if(x>=1&&x<=31&&y>=42&&y<=239)
    { if(y<54)
      y=54;
      if(y>227)
      y=227;
      quick(y);
    }
   }
 
   if (myTouch.dataAvailable()) {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();  
    if(x>=xP-13&&x<=xP+13&&y>=yP-13&&y<=yP+13)
    drawFrame(xP-13, yP-13, xP+13, yP+13);
    else if(x>=xP-7&&x<=xP+7&&y<=227&&y>=54)
    longitude(xP);
    else if(y>=yP-7&&y<=yP+7&&x>=45&&x<=307)
    latitude(yP);
   }
   
}
void longitude(int x1)
{
     
 while (myTouch.dataAvailable())
    {  
      myTouch.read();
      x1=myTouch.getX();
      if(x1<24)
      break;
      if(x1<45)
      x1=45;
      if(x1>307)
      x1=307;
      myGLCD.setColor(255,255,255);
      myGLCD.drawLine(x1,54,x1,227);
      xP=x1;
      onlyFrame();
      onlyRed();
      onlyyLine();
      touchPad();
      kala();
    } 
    myGLCD.setColor(0,0,0);
    myGLCD.drawLine(x1,54,x1,227);
 }
 void latitude(int y1)
 { int x1;
  while (myTouch.dataAvailable())
    {  
      myTouch.read();
      x1=myTouch.getX();
      y1=myTouch.getY();
      if(x1<26)
      break;
      if(y1<54)
      y1=54;
      if(y1>227)
      y1=227;
      myGLCD.setColor(255,255,255);
      myGLCD.drawLine(45,y1,307,y1);
      yP=y1;
      onlyFrame();
      onlyGreen();
      onlyxLine();
      touchPad();
      kala();
    } 
    myGLCD.setColor(0,0,0);
    myGLCD.drawLine(45,yP,307,yP);
 }
void drawFrame(int x1, int y1, int x2, int y2) {

 
  while (myTouch.dataAvailable())
    {  
      myTouch.read();
      x1=myTouch.getX();
      y1=myTouch.getY();
      if(x1<24)
      break;
       if(y1<54)
       y1=54;
       if(y1>227)
       y1=227;
       if(x1<45)
       x1=45;
       if(x1>307)
       x1=307;       
       xP=x1;
       yP=y1;
       myGLCD.setColor(255, 0, 0);
       myGLCD.drawRoundRect (x1-13, y1-13, x1+13,y1+13);
       onlyLine();
       touchPad();
       kala();
    }
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (xP-13, yP-13, xP+13,yP+13);

}
void drawScroll()
{ int x1,y1;
  while(myTouch.dataAvailable())
  {   myTouch.read();
      x1=myTouch.getX();
      y1=myTouch.getY();
      if(x1>43||y1<45)
      break;
      if(y1<54)
      y1=54;
      if(y1>227)
      y1=227;
      yB=y1;
      black();
      Pad();
      onlyScroll();
  }
}
void quick(int y1)
{  yB=y1;
   black();
   Pad();
   onlyScroll();
}
void touchPad()
{
   myGLCD.setColor(112,128,144);
   myGLCD.fillRoundRect (45,54, 307, 227);
   myGLCD.setColor(255, 255, 255);
   myGLCD.drawRoundRect (44, 53, 308, 228);


  // Maps the values of the X - Axis from 38 to 0 and 310 to 255, because we need values from 0 to 255 for turning on the led
  int xRC = map(xR,176,310,0,255);
  int xGC = map(xG,176,310,0,255);
  
  
  // Sends PWM signal to the pins of the led
  analogWrite(redLed, xRC);
  analogWrite(greenLed, xGC);
 
  
  // Draws the positioners
 // myGLCD.setColor(255, 255, 255);
  //myGLCD.fillRect(xR,139,(xR+4),147); // Positioner
  onlyRed();
  onlyGreen();
}
void Pad()
{ 
  int xBC = map(xB,176,310,0,255);
   analogWrite(blueLed, xBC);
   onlyBlue();
}
void onlyLine()
{
  myGLCD.setColor(0,0,0);
  myGLCD.drawLine(xP,54,xP,227);
  myGLCD.drawLine(45,yP,307,yP);
}
void onlyxLine()
{
  myGLCD.setColor(0,0,0);
  myGLCD.drawLine(xP,54,xP,227);
}
void onlyyLine()
{
  myGLCD.setColor(0,0,0);
  myGLCD.drawLine(45,yP,307,yP);
}
void onlyFrame()
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (xP-13, yP-13, xP+13, yP+13);
}
void onlyRed()
{
  myGLCD.setColor(255, 0, 0);
  if(xP>=176){
  myGLCD.fillRect(176, 135, xP, 151);
  myGLCD.setColor(0,0,0);
  myGLCD.drawRect(176, 135, xP, 151);
  myGLCD.setColor(112,128,144);
  myGLCD.fillRect(xP+1, 135, 306, 151);
  }
  else{
    myGLCD.fillRect(xP,135,176,151);
  myGLCD.setColor(0,0,0);
  myGLCD.drawRect(xP, 135, 176, 151);
  myGLCD.setColor(112,128,144);
  myGLCD.fillRect(47,135,xP-1,151);
  }
}
void onlyGreen()
{
  myGLCD.setColor(0, 255, 0);
  if(yP>=143){
  myGLCD.fillRect(168,143,184,yP);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRect(168,143,184,yP);
  myGLCD.setColor(112,128,144);
  myGLCD.fillRect(168,yP+1, 184,226);
  }
  else{
  myGLCD.fillRect(168,yP,184,143);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRect(168,yP,184,143);
  myGLCD.setColor(112,128,144);
  myGLCD.fillRect(168,55, 184,yP-1);
  }
}
void onlyBlue()
{
  myGLCD.setColor(0,0,255);
  if(yB>=143){
  myGLCD.fillRect(11,143,25,yB);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRect(11,143,25,yB);
  myGLCD.fillRect(11,yB+1,25,227);
  myGLCD.fillRect(11,55,25,143);
  }
  else{
  myGLCD.fillRect(11,yB,25,143);
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRect(11,yB,25,143);
  myGLCD.fillRect(11,54,25,yB-1);
  myGLCD.fillRect(11,143,25,227);
  }
}
void onlyScroll()
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, yB-9,31, yB+9);
}
void kala()
{
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(32,41,43,239);
  myGLCD.fillRect(44,229,319,239);
  myGLCD.fillRect(309,41,319,239);
  myGLCD.fillRect(44,41,309,52);
}
void black()
{   myGLCD.setColor(0,0,0);
   myGLCD.fillRect(5,41,9,239);
   myGLCD.fillRect(27,41,31,239);
   myGLCD.fillRect(5,41,31,52);
   myGLCD.fillRect(5,229,31,239);
}
