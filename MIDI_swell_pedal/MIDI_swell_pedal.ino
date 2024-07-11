#include <MIDIUSB.h>
#include <InterpolationLib.h>

// MIDI channel and CC number
const uint8_t channel = 0; // zero-based
const uint8_t swellCC = 11;

// Analog pin to read swell pedal position from
const uint8_t swellPin = A2;

// Values for cycle timing
const uint8_t cycleTime_ms = 20; // minimum time between sending control codes
unsigned long cycleEndTime_ms = 0;

// Swell pedal position, 0-127
uint8_t swellValue = 127;
uint8_t oldSwellValue = 127;

// Serial monitor for debugging
const uint16_t baudRate = 19200;

void setup()
{
  swellValue = getSwellValue_log();
  sendCC(channel, swellCC, swellValue);
  oldSwellValue = swellValue;
  
  Serial.begin(baudRate);
  Serial.println(swellValue);

  cycleEndTime_ms = millis() + cycleTime_ms;
}

void loop()
{
  swellValue = getSwellValue_log();
  if (swellValue != oldSwellValue) // send new CC only on change
  {
    sendCC(channel, swellCC, swellValue);
    Serial.println(swellValue);
    oldSwellValue = swellValue;
  }

  while (millis() < cycleEndTime_ms)
  {
    // wait
  }
  cycleEndTime_ms += cycleTime_ms;
}

uint8_t getSwellValue_log()
{
  /*
    This function "de-tapers" the input from a log/audio taper pot using
    a lookup table and linear interpolation
  */

  // Assumes a typical audio taper pot with 2-part piecewise linear curve.
  // Crossover point is 10% output at 50% position.
  static const double rawAnalogCounts[3]  = { 0,  102,  1023};
  static const double rawSwellValue[3]    = { 0,  63,   127};
  
  double floatSwellValue = Interpolation::Linear(rawAnalogCounts,rawSwellValue,3,analogRead(swellPin),false);
  uint8_t swellValue = int(round(floatSwellValue));

  return swellValue;
}

uint8_t getSwellValue_lin()
{
  /*
    Use this function if your pedal has a linear pot.
    
    This function simply scales the 10-bit analog input down to a 7-bit MIDI
    value by shifting right 3 bits.
  */

  uint8_t swellValue = analogRead(swellPin)>>3;

  return swellValue;
}

void sendCC(uint8_t channel, uint8_t ccNumber, uint8_t value)
{
  midiEventPacket_t midiPacket = {0x0B, 0xB0 | channel, ccNumber, value};
  MidiUSB.sendMIDI(midiPacket);
  MidiUSB.flush();
}
