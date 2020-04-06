
#include "MIDIUSB.h"
#include "Keyboard.h"

bool keyPressed[5] = {0,0,0,0,0};

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void pitchBend(byte channel, byte pitch, byte pitchPrecise) {
  midiEventPacket_t pitchBend = {0x0E, 0xE0 | channel, pitch, pitchPrecise};
  MidiUSB.sendMIDI(pitchBend);
}

void pitchBend(byte channel, int bit14Pitch) 
{
  midiEventPacket_t pitchBend = {0x0E, 0xE0 | channel, bit14Pitch % 128, bit14Pitch / 128};
  MidiUSB.sendMIDI(pitchBend);
}


void keyBoardTest () 
{
  if (digitalRead(2) == HIGH && keyPressed[0] != HIGH)
  { 
  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(KEY_UP_ARROW);
  keyPressed[0] = 1;
    }
  else if (digitalRead(2) == HIGH && keyPressed[0] == HIGH);
else
  Keyboard.releaseAll();
  keyPressed[0] = 0;
}

void keyBoard () 
{
  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(KEY_UP_ARROW);

  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(KEY_DOWN_ARROW);

  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(KEY_LEFT_ARROW);

  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(KEY_RIGHT_ARROW);

  Keyboard.press(KEY_RETURN);
  
  Keyboard.releaseAll();

}

void loop() { //usbmidi capable to go > 500 fps insane!!! 
  
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    // Type the next ASCII value from what you received:
    Keyboard.write(inChar + 1);
  }
  
  //Serial.println("Sending note on");
  pitchBend(0, 16383);   // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(200);
  //Serial.println("Sending note off");
  pitchBend(0, 0);  // Channel 0, middle C, normal velocity
  MidiUSB.flush();
  delay(500);

  // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
}

//try to implement kayboard, then join with multiplexer reader and sample 2 x8 - 8 faders + master encoder and optional stuff
//capture only these 2 groups, store in arrays, and in meanwhile do the computation of tangent and send data
//in version 2 implement receive port and implement leds for feedback
//in version 3 add 2 more midi cables and try full flex setup with other
