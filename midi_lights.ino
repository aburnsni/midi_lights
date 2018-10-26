#include <MIDI.h>
#include <NeoPixelBus.h>
#include <SoftwareSerial.h>

const int DEBUG=0;

// SoftwareSerial mySerial(10,11);
// MIDI_CREATE_INSTANCE(SoftwareSerial, mySerial, MIDI);

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED LED_BUILTIN

//NeoPixel Setup
const uint16_t PixelCount = 12;
const uint8_t PixelPin = 3;
// #define brightness 0.7 // Between 0 and 1
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
// Set rgb colours
// RgbColor white(255 * brightness);
RgbColor black(0);

int note;
int notePlaying[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

void setup()  {
  pinMode(LED, OUTPUT);

  for (int i = 5; i <= 12; i++) {
    pinMode(i, INPUT_PULLUP);
    pinMode(i, OUTPUT); // defaults HIGH (relays off)
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  if (DEBUG) {
    Serial.begin(115200);
  }
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
//  note = pitch - 60;  //  C=0 D=2 E=4 F=5 G=7 A=9 B=11
  note = pitch % 12;
  notePlaying[note]++;
  if (notePlaying) {
    turnOnLED(note, velocity);
//  switch (note) {
//    case 0:
//      turnOnLED(0,velocity);
//      break;
//    case 2:
//      turnOnLED(1,velocity);
//      break;
//    case 4:
//      turnOnLED(2,velocity);
//      break;
//    case 5:
//      turnOnLED(3,velocity);
//      break;
//    case 7:
//      turnOnLED(4,velocity);
//      break;
//    case 9:
//      turnOnLED(5,velocity);
//      break;
//    case 11:
//      turnOnLED(6,velocity);
//      break;
//    case 12:
//      turnOnLED(7,velocity);
//  }
  }
}
void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  note = pitch % 12;  //  C=0 D=2 E=4 F=5 G=7 A=9 B=11
  // note = pitch - 60;
  if (notePlaying[note]>0) {
      notePlaying[note]--;
  }
  if (notePlaying[note]==0) {
    turnOffLED(note);
  }
//  switch (note) {
//    case 0:
//      turnOffLED(0);
//      break;
//    case 2:
//      turnOffLED(1);
//      break;
//    case 4:
//      turnOffLED(2);
//      break;
//    case 5:
//      turnOffLED(3);
//      break;
//    case 7:
//      turnOffLED(4);
//      break;
//    case 9:
//      turnOffLED(5);
//      break;
//    case 11:
//      turnOffLED(6);
//      break;
//    case 12:
//      turnOffLED(7);
//  }
}

void turnOnLED( int led, int brightness ) {
  // RgbColor updatecolor(brightness*2);

  float ledHue = (float)led/(float)PixelCount;
  float ledSat = 1;
  float ledLight = (float)brightness/254;
  if (DEBUG) {
    Serial.print(led);
    Serial.print("\t");
    Serial.print(ledHue);
    Serial.print("\t");
    Serial.print(ledSat);
    Serial.print("\t");
    Serial.println(ledLight);
  }
  HslColor updatecolor(ledHue, ledSat, ledLight);

  strip.SetPixelColor(led, updatecolor);
  strip.Show();
  delay(10);
  digitalWrite(led+5, LOW);
}
void turnOffLED( int led ) {
  strip.SetPixelColor(led, black);
  strip.Show();
  delay(10);
    digitalWrite(led+5, HIGH);
}

void BlinkLed(byte num) {
  for (byte i=0;i<num;i++) {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
}
