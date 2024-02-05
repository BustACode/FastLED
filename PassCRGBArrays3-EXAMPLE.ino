/*
https://forum.makerforums.info/t/i-everyone-i-am-trying-to-pass-a-crgbset-to-a-function/62953/2
https://gist.github.com/chemdoc77/31632b540908b6788c9340989eeb8bfc
*/
#include "FastLED.h"

#define LEDTYPE WS2812B
#define DATAPIN 2
#define COLORORDER GRB
#define STRIPSETUP TypicalLEDStrip
#define VOLTS 5
#define MAXPOWER 500
#define BRIGHTNESS 50

#define STRIPNUMLEDS 300                  // Num. LEDs on target strip
#define GROUPNUMLEDS 300                  // Num. LEDs in all target Zones as a GROUP; May also set equal STRIPNUMLEDS

#define FRAMESPERSECOND  120
#define STARTUPDELAY 3000


CRGB RAWLEDS[STRIPNUMLEDS];               // Init. LED ARRAY on target strip
CRGBSet a_LEDs(RAWLEDS, STRIPNUMLEDS);    // Clone LED ARRAY of target strip to primary zone 
CRGBSet a_LEDZone1(a_LEDs(0,7));          // Init. LED Zone 1
CRGBSet a_LEDZone2(a_LEDs(8,15));         // Init. LED Zone 2
CRGBSet a_LEDZone3(a_LEDs(24,31));        // Init. LED Zone 3
CRGBSet a_LEDZone4(a_LEDs(292,299));      // Init. LED Zone 4

struct CRGB * a_LEDArray[] = {a_LEDZone1, a_LEDZone2, a_LEDZone3, a_LEDZone4}; // An array of the CRGBSet ARRAYs; Enbales the passing of SET/Zone ARRAYs
uint8_t b8_SizeZones[]= {8,8,8, 8}; // Size of the above arrays if needed in loops

void setup(){ 
  delay(STARTUPDELAY); // power-up safety delay
  f_AllLEDsOff();
  
  FastLED.addLeds<LEDTYPE, DATAPIN, COLORORDER>(a_LEDs, GROUPNUMLEDS).setCorrection(STRIPSETUP);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAXPOWER);

  FastLED.clear();
  FastLED.show();
}

void loop(){ 
  // fills the whole array
   f_ArrayFill(a_LEDArray[0], b8_SizeZones[0], CRGB::Red, 700);   // Light each zone in turn
   f_ArrayFill(a_LEDArray[1], b8_SizeZones[1], CRGB::Green, 700); // Light each zone in turn
   f_ArrayFill(a_LEDArray[2], b8_SizeZones[2], CRGB::Blue, 700);  // Light each zone in turn
   for(int i = 3; i == 3; i++){f_ArrayFill(a_LEDArray[i], b8_SizeZones[i], CRGB::Yellow, 700);}
}

//================ Basement =====================
 
void f_ArrayFill(CRGB a_LEDZone[], uint8_t b8_NumLEDs, CRGB color, uint16_t b16_Wait){
  // Fill solid each CRGB zone's LEDs with desired color
     fill_solid(a_LEDZone, b8_NumLEDs, color); // Target LED/ARRAY/Zone, Num. to fill
     FastLED.show();
     delay(b16_Wait);
     fill_solid(a_LEDZone, b8_NumLEDs, CRGB::Black);
     FastLED.show();
}

void f_AllLEDsOff(){
  FastLED.addLeds<LEDTYPE, DATAPIN, COLORORDER>(a_LEDs, STRIPNUMLEDS).setCorrection(STRIPSETUP);
  a_LEDs = CRGB::Black; // All LEDs of strip off
  FastLED.clear();
  FastLED.show();
}
