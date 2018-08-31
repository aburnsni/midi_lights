#include <MIDI.h>
#include <NeoPixelBus.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED LED_BUILTIN

//NeoPixel Setup
const uint16_t PixelCount = 8;
const uint8_t PixelPin = 3;
// #define brightness 0.7 // Between 0 and 1
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
// Set rgb colours
// RgbColor white(255 * brightness);
RgbColor black(0);

int note;

void setup()  {
  pinMode(LED, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  // By default, the MIDI library sends everything THRU. We do NOT want that! 
  MIDI.turnThruOff();

  // Connect MIDI status changes involving a channel to handlers
  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);

  strip.Begin();
  strip.Show();
}

void loop() {
  MIDI.read();
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  note = pitch - 60;  //  C=0 D=2 E=4 F=5 G=7 A=9 B=11
  switch (note) {
    case 0:
      turnOnLED(0,velocity);
      break;
    case 2:
      turnOnLED(1,velocity);
      break;
    case 4:
      turnOnLED(2,velocity);
      break;
    case 5:
      turnOnLED(3,velocity);
      break;
    case 7:
      turnOnLED(4,velocity);
      break;
    case 9:
      turnOnLED(5,velocity);
      break;
    case 11:
      turnOnLED(6,velocity);
      break;
    case 12:
      turnOnLED(7,velocity);
  }
}
void HandleNoteOff(byte channel, byte pitch, byte velocity) {
//   note = pitch % 12;  //  C=0 D=2 E=4 F=5 G=7 A=9 B=11
  note = pitch - 60;
  switch (note) {
    case 0:
      turnOffLED(0);
      break;
    case 2:
      turnOffLED(1);
      break;
    case 4:
      turnOffLED(2);
      break;
    case 5:
      turnOffLED(3);
      break;
    case 7:
      turnOffLED(4);
      break;
    case 9:
      turnOffLED(5);
      break;
    case 11:
      turnOffLED(6);
      break;
    case 12:
      turnOffLED(7);
  }
}

void turnOnLED( int led, int brightness ) {
  RgbColor updatecolor(brightness*2);
  strip.SetPixelColor(led, updatecolor);
  strip.Show();
  delay(10);
}
void turnOffLED( int led ) {
  strip.SetPixelColor(led, black);
  strip.Show();
  delay(10);
}

void BlinkLed(byte num) {
  for (byte i=0;i<num;i++) {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
}