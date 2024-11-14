#include <Arduino.h>
#include "src/lib/TimerOne/TimerOne.h"
#include "src/lib/DMD/DMD.h"
#include "src/lib/DMD/Arial_Black_16.h"

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
#define MARQUEE_STEP_DELAY 30

String text("SPX Robots");
unsigned long last;

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void setup ()
{
  Serial.begin(9600);
  Serial.print("sign> ");
  Serial.flush();

  dmd.selectFont(Arial_Black_16);
  
  Timer1.initialize(3000);
  Timer1.attachInterrupt([]() { dmd.scanDisplayBySPI(); });
}

void loop ()
{
  if (Serial.available())
  {
    text = Serial.readStringUntil('\n');
    Serial.print("sign> ");
    Serial.flush();
    dmd.drawMarquee(text.c_str(), text.length(), 32 * DISPLAYS_ACROSS - 1, 0);
  }

  unsigned long now = millis();
  if (now - last > MARQUEE_STEP_DELAY)
  {
    bool done = dmd.stepMarquee(-1, 0);
    if (done)
    {
      dmd.drawMarquee(text.c_str(), text.length(), 32 * DISPLAYS_ACROSS - 1, 0);
    }
    last = now;
  }
}
