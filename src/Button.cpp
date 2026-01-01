#include "Button.h"

Button::Button(TFT_eSPI& tft_, int x_, int y_, int w_, int h_) : tft(tft_),  x(x_), y(y_), w(w_), h(h_), sprite(&tft)
{
    sprite.createSprite(w, h);
    sprite.fillSprite(TFT_RED); 
}

void Button::setState()
{
    stateBut = (!stateBut);
}

bool Button::isTouched(int tx, int ty)
{
    return(tx >= x && tx <= x + w && ty >= y && ty <= y +h);
}

void Button::drawBtn()
{
    sprite.fillSprite(stateBut ? TFT_RED : TFT_BLUE);
    sprite.pushSprite(x, y);
}