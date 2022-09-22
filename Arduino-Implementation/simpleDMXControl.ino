#include <dmxserial.h>
#include <Arduino.h>
#include <DMXSerial.h>

// Setup Control Pins
//------------------------------------------------------------------------------
//Fountain Pins
const unsigned int pump1 =   3;  // PWM output for pump1
const unsigned int pump2 =   5;  // PWM output for pump2
const unsigned int pump3 =   6;  // PWM output for pump3
const unsigned int pump4 =   9;  // PWM output for pump4
//------------------------------------------------------------------------------

// Setup DMX
//------------------------------------------------------------------------------
//DMX address
#define DMXSTART 1

// number of DMX channels used
#define DMXLENGTH (4)
//------------------------------------------------------------------------------


void setup () {
  // Start DMXSerial
  DMXSerial.init(DMXProbe);

  // enable pwm outputs
  pinMode(pump1,   OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3,  OUTPUT);
  pinMode(pump4,  OUTPUT);
  
  //Set Max DMX channel length
  DMXSerial.maxChannel(DMXLENGTH);

}

// get DMX data and update pumps with data
void loop() {
  // wait for an incomming DMX packet.
  if (DMXSerial.receive()) {
    analogWrite(pump1, DMXSerial.read((DMXSTART + 1));
    analogWrite(pump2, DMXSerial.read((DMXSTART + 2)));
    analogWrite(pump3, DMXSerial.read((DMXSTART + 3)));
    analogWrite(pump4, DMXSerial.read((DMXSTART + 4)));

  } else {
    // if no signal received, turn off pumps
    analogWrite(pump1, 0);
    analogWrite(pump2, 0);
    analogWrite(pump3, 0);
    analogWrite(pump4, 0);
  }
  
}
