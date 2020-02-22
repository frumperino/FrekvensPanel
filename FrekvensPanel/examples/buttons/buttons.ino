#include <FrekvensPanel.h>
// see readme.md for wiring instructions

#include "button.h"

#define buttonCOM_VCC // comment out this line if button COM is wired to GND.  

#define p_ena 5 
#define p_data 6
#define p_clock 9
#define p_latch 10

#define p_btn1 14 // A0 (Adafruit Feather M0) - RED button (black wire)
#define p_btn2 15 // A1 (Adafruit Feather M0) - YELLOW button (white wire)

FrekvensPanel panel(p_latch, p_clock, p_data);

char activeProgram = 1;
char activeBrightMode = 1;

#ifdef buttonCOM_VCC
// the red wire (COM) for the buttons is connected to (MCU board) VCC, 
// so the button signal is positive and the button input pins must be set to INPUT_PULLDOWN
SimpleButton button1(1,p_btn1,0,20);
SimpleButton button2(2,p_btn2,0,20);
#else
// the red wire (COM) for the buttons is connected to GND, so the button signal is inverted
SimpleButton button1(1,p_btn1,1,20);
SimpleButton button2(2,p_btn2,1,20);
#endif

void setBrightMode(int brightMode)
{
  activeBrightMode = brightMode % 4;
  switch(activeBrightMode)
  {
    case 0: { pinMode(p_ena, OUTPUT); digitalWrite(p_ena, 1); } break; // off
    case 1: analogWrite(p_ena, 254); break; // very dim
    case 2: analogWrite(p_ena, 240); break; // dim
    case 3: { pinMode(p_ena, OUTPUT); digitalWrite(p_ena, 0); } break; // on 100%
  }
}

void setProgram(int program)
{
  activeProgram = (program % 3);
}

void buttonHandler(int id, int state)
{
  if (state) // button pressed
  {
    switch(id)
    {
      case 1: setBrightMode(activeBrightMode+1); break;
      case 2: setProgram(activeProgram+1); break;
    }
  }  
}

void program0()
{
  for (int i=0;i<20;i++)
  {
    panel.drawPixel(random(16),random(16),random(10) == 0);
  }
}

int p1_i = 0;
void program1()
{
  float pi23 = PI*2/3;
  float p = 0.02 * p1_i++;
  int x0 = 7.98 + 7.98 * cos(p);
  int y0 = 7.98 + 7.98 * sin(p);
  p += pi23;
  int x1 = 7.98 + 7.98 * cos(p);
  int y1 = 7.98 + 7.98 * sin(p);
  p += pi23;
  int x2 = 7.98 + 7.98 * cos(p);
  int y2 = 7.98 + 7.98 * sin(p);
  panel.clear();
  panel.drawLine(x0,y0,x1,y1,1);  
  panel.drawLine(x1,y1,x2,y2,1);  
  panel.drawLine(x2,y2,x0,y0,1);  
}


void program2()
{
  int x = random(16);
  int y = random(16);
  panel.drawRect(x,y,random(16-x),random(16-y),random(6)==0);
}

void setup() 
{
#ifdef buttonCOM_VCC
  pinMode(p_btn1, INPUT_PULLDOWN); 
  pinMode(p_btn2, INPUT_PULLDOWN); 
#else
  pinMode(p_btn1, INPUT_PULLUP); 
  pinMode(p_btn2, INPUT_PULLUP); 
#endif
  panel.clear();
  pinMode(p_ena, OUTPUT); 
  analogWrite(p_ena, 0); // full brightness
  button1.attachHandler(buttonHandler);
  button2.attachHandler(buttonHandler);
  panel.scan();
}

void loop() 
{
  switch(activeProgram)
  {
    case 0: program0(); break;
    case 1: program1(); break;
    case 2: program2(); break;
  }
  panel.scan();
  button1.scan();
  button2.scan();
  delay(2);
}
