#pragma once
#include <SPI.h>
#include <TFT_eSPI.h>

class Button
{
   private:
      int x, y, w, h;
      bool stateBut = false;
      TFT_eSPI& tft;
      TFT_eSprite sprite;

   public:
      Button(TFT_eSPI &tft, int x, int y, int w, int h);

      void setState();
      bool isTouched(int tx, int ty);
      void drawBtn();
};