/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 9;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(115200);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    //Serial.println(results.value, HEX);
    //Serial.write(results.value,sizeof(results.value));
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
