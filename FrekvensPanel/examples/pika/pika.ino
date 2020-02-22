#include <FrekvensPanel.h>
// see readme.md for wiring instructions

#include "bm_pika.h"

#define p_ena 5 
#define p_data 6
#define p_clock 9
#define p_latch 10

#define p_btn1 14 // A0 (Adafruit Feather M0) - RED button (black wire)
#define p_btn2 15 // A1 (Adafruit Feather M0) - YELLOW button (white wire)

FrekvensPanel panel(p_latch, p_clock, p_data);

int i = 0;

void setup() 
{
  panel.clear();
  panel.scan();
  pinMode(p_ena, OUTPUT); 
  analogWrite(p_ena, 0); // full brightness
}

void loop() 
{
  panel.fillScreen(1);
  int pw = panel.width();
  int ph = panel.height();
  int bw = bm_pika_width;
  int bh = bm_pika_height;

  float p = (0.002 * i++);
  float bw2 = (float) (bw - pw) / 2;
  float bh2 = (float) (bh - ph) / 2;
  int x = (int) (bw2 + bw2 * cos(p * 3)) - bw + pw;
  int y = (int) (bh2 + bh2 * sin(p * 4)) - bh + ph;
  panel.drawBitmap(x,y,&bm_pika[0],bw,bh,0);
  panel.scan();
}
