#include <FrekvensPanel.h>
// see readme.md for wiring instructions

#define p_ena 5 
#define p_data 6
#define p_clock 9
#define p_latch 10

#define p_btn1 14 // A0 (Adafruit Feather M0) - RED button (black wire)
#define p_btn2 15 // A1 (Adafruit Feather M0) - YELLOW button (white wire)

FrekvensPanel panel(p_latch, p_clock, p_data);

void setup() 
{
  panel.clear();
  panel.scan();
  pinMode(p_ena, OUTPUT); 
  analogWrite(p_ena, 0); // full brightness
}

void loop() 
{
  for (int i=0;i<20;i++)
  {
    panel.drawPixel(random(16),random(16),random(10) == 0);
  }
  panel.scan(); // refreshes display
  delay(5);
}
