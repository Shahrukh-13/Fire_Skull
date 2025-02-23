#include <SPI.h>
#include <TFT_eSPI.h>
#include <AnimatedGIF.h>
#include "fire.h"    

#define NORMAL_SPEED  // Comment out for rame rate for render speed test
#define GIF_IMAGE fire

AnimatedGIF gif;

TFT_eSPI tft = TFT_eSPI();

void setup() 
{
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  gif.begin(BIG_ENDIAN_PIXELS);
}


void loop()
{
  // Put your main code here, to run repeatedly:
  if (gif.open((uint8_t *)GIF_IMAGE, sizeof(GIF_IMAGE), GIFDraw))
  {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
    tft.startWrite(); // The TFT chip slect is locked low
    while (gif.playFrame(true, NULL))
    {
      yield();
    }
    gif.close();
    tft.endWrite(); // Release TFT chip select for other SPI devices
  }
}
