/*
  Multple Serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).

 This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc

 The circuit:
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:

 created 30 Dec. 2008
 modified 20 May 2012
 by Tom Igoe & Jed Roach
 modified 27 Nov 2015
 by Arturo Guadalupi

 This example code is in the public domain.

 */


byte bufer[9] = { 0,0,0,0,0,0,0,0,0};
unsigned int x = 0;
unsigned int y = 0;

void setup() {
  // initialize both serial ports:
 Serial.begin(115200);

  Serial1.begin(9600);
}

void loop() {
    
  // read from port 1, send to port 0:
  if (Serial1.available()>9) {
//    int inByte = Serial1.read();
//    Serial.write(inByte);
   Serial1.readBytes(bufer, 9);
//    Serial.print("yea ");
//    Serial.write(bufer,9);
//    Serial.println("end");

    
//---------------------------------------------------------------
//    x = bufer[1];//<<;// + bufer[2]<<2 + bufer[3]>>5;
//    x = x*256 + bufer[2]; //<<2 + bufer[3]>>5;
//
//    y = bufer[3];
//    bitClear(y,8);
//    bitClear(y,7);
//    bitClear(y,6);
//    bitClear(y,5);
//    //y = y <<12;
//    //y = y<<10;
//    y = y*256;
//    y = y + ((int)bufer[4])*8;
//    
//    y = y + (((int)bufer[5])>>4);
//    //Serial.print(((int)bufer[5])>>4);
//    Serial.print("x ");
//    Serial.print(x);
//    Serial.print("\t");
//    Serial.print("y ");
//    Serial.println(y);
//    ---------------------------------------------
//    
//    Serial.print(" ");
//    Serial.print(bufer[3]<<2,BIN);
//    Serial.print(" ");
//    Serial.print(bufer[4],BIN);
//    Serial.print(" ");
//    Serial.println(bufer[5],BIN);
    
    Serial.print("Packet: ");
    Serial.print(bufer[0],HEX);
    Serial.print(" ");
    Serial.print(bufer[1],HEX);
    Serial.print(" ");
    Serial.print(bufer[2],HEX);
    Serial.print(" ");
    Serial.print(bufer[3],HEX);
    Serial.print(" ");
    Serial.print(bufer[4],HEX);
    Serial.print(" ");
    Serial.print(bufer[5],HEX);
    Serial.print(" ");
    Serial.print(bufer[6],HEX);
    Serial.print(" ");
    Serial.print(bufer[7],HEX);
    Serial.print(" ");
    Serial.println(bufer[8],HEX);
  }

//  // read from port 0, send to port 1:
//  if (Serial.available()) {
//    int inByte = Serial.read();
//    Serial1.write(inByte);
//  }
}
