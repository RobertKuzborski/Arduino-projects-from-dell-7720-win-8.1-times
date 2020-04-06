/////////////////////////////////////////////////////////////////////////////////////
// EDID fuzzer v1.0
// By Andy Davis, NGS Secure
// March 2012
//
// This is a very simple example of a fuzzer to iterate through the bytes within an
// EDID block and send the EDID data emulating the connection of a display device
//
// This code has been successfully tested on the Arduino Duemilanove microcontroller
//
// Note: Internal pull-up resistors should be disabled in twi.cpp:
// //sbi(PORTC, 4);
// //sbi(PORTC, 5);
//
// 4.7k external pull-up resistors should be used
//
/////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#define EDID_SLAVE 0x50
int hotplugpin = 4;
int i = 0;
int a = 0;
int count = 1;
int z = 0;
// EDID v1.3 block
//byte EDIDArray[128] = {
//  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x34, 0xA9, 0x01, 0xC3, 0x01, 0x01, 0x01, 0x01,
//  0x00, 0x14, 0x01, 0x03, 0x80, 0x00, 0x00, 0x78, 0x0A, 0xDA, 0xFF, 0xA3, 0x58, 0x4A, 0xA2, 0x29,
//  0x17, 0x49, 0x4B, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
//  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0xd0, 0x72, 0x38, 0x2d, 0x40, 0x10, 0x2c,
//  0x45, 0x80, 0xba, 0x88, 0x21, 0x00, 0x00, 0x1E, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40,
//  0x58, 0x2C, 0x45, 0x00, 0xBA, 0x88, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x50,
//  0x61, 0x6E, 0x61, 0x73, 0x6F, 0x6E, 0x69, 0x63, 0x2D, 0x54, 0x56, 0x0A, 0x00, 0x00, 0x00, 0xFD,
//  0x00, 0x17, 0x3D, 0x0F, 0x44, 0x0F, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x53
//};
// EDID v1.4 block

byte EDIDArray[128] = {
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, //EDID header
  0x04, 0x43, //Manufacturer’s Code Name
  0x08, 0xF2, //ID Product Code
  0x01, 0x00, 0x00, 0x00, //ID Serial Number
  0x10, //Week of Manufacture is 16
  0x11, //Year of Manufacture is 2007
  0x01, //“1” EDID Version Number
  0x04, //“4” EDID Revision Number
  0xA2, //Digital Video Input using HDMI-a, 8 Bits per Primary Colour
  0x79, //Aspect Ratio is 16 : 9 AR in Landscape
  0x44, //Aspect Ratio (Landscape) Flag
  0x78, //Display Gamma is 2.20
  0x1E, //Feature Support Byte
  0xEE, 0x91, 0xA3, 0x54, 0x4C, 0x99, 0x26, 0x0F, 0x50, 0x54, //Display x,y Chromaticity Coordinates
  0xFF, //Established Timings I
  0xEF, //Established Timings II
  0x80, //Manufacturer’s Timings
  0x81, 0x99, 0x81, 0x80, 0x81, 0x59, 0x81, 0x40, 0x61, 0x59, 0x4B, 0xC0, 0x45, 0x59, 0x31, 0x59, //Standard Timings
  //First 18 Byte Data Block
  0x66, 0x21, //Pixel Clock
  0x50, 0xB0, 0x51, //Horizontal Addressable Video
  0x00, 0x1B, 0x30, //Vertical Addressable Video
  0x40, 0x70, 0x36, 0x00, //Horizontal Front Porch
  0xBE, 0xAB, 0x42, //Horizontal Addressable Image Size
  0x00, 0x00, //Horizontal Border Size
  0x1E, //Timing is Non-Interlaced Video
  //Second 18 Byte Data Block
  0x01, 0x1D, //Pixel Clock
  0x00, 0x72, 0x51, //Horizontal Addressable Video
  0xD0, 0x1E, 0x20, //Vertical Addressable Video
  0x6E, 0x28, 0x55, 0x00, //Horizontal Front Porch
  0xBE, 0xAB, 0x42,
  0x00, 0x00, //Horizontal Border Size
  0x1E, //Timing is Non-Interlaced Video
  //Third 18 Byte Data Block
  0x00, 0x00, 0x00, //Established Timings III Descriptor
  0xF7, //Established Timings III Block Tag
  0x00, //padding
  0x0A, 0xF7, 0x0F, 0x03, 0x87, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //VESA DMT Standard Version #10
  //Fourth 18 Byte Data Block
  0x00, 0x00, 0x00, //Monitor Name ASCII Descriptor
  0xFC, //Monitor Name Tag
  0x00, //padding
  0x41, 0x42, 0x43, 0x20, 0x50, 0x4C, 0x41, 0x35, 0x35, 0x0A, 0x20, 0x20, 0x20,
  0x01, //Extension flag
  0x0A
}; //Checksum
//EIA/CEA-861 extension block
/*
  byte EDIDArray2[128]={
  0x02,0x03,0x22,0x72,0x50,0x9F,0x90,0x14,0x05,0x20,0x13,0x04,0x12,0x03,0x11,0x02,
  0x16,0x07,0x15,0x06,0x01,0x23,0x09,0x07,0x01,0x68,0x03,0x0C,0x00,0x30,0x00,0xB8,
  0x26,0x0F,0x01,0x1D,0x80,0xD0,0x72,0x1C,0x16,0x20,0x10,0x2C,0x25,0x80,0xBA,0x88,
  0x21,0x00,0x00,0x9E,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,0x25,0x00,
  0xBA,0x88,0x21,0x00,0x00,0x9E,0x01,0x1D,0x00,0xBC,0x52,0xD0,0x1E,0x20,0xB8,0x28,
  0x55,0x40,0xBA,0x88,0x21,0x00,0x00,0x1E,0x01,0x1D,0x00,0x72,0x51,0xD0,0x1E,0x20,
  0x6E,0x28,0x55,0x00,0xBA,0x88,0x21,0x00,0x00,0x1E,0x8C,0x0A,0xD0,0x90,0x20,0x40,
  0x31,0x20,0x0C,0x40,0x55,0x00,0xBA,0x88,0x21,0x00,0x00,0x18,0x00,0x00,0x00,0xEA
  };
*/
//Localised string extension block
byte EDIDArray2[128] = {
  0x50, //Extension ID
  0x01, //LS-Ext Version number
  0x00, //LS-Ext Revision number
  0x32, //Unicode Version – Major/Minor
  0x00, //Unicode Version – Update
  0x28, //String table size
  0x00, //String Table Header – UTF 8
  0x00, //Language ID structure – Default Neutral String Table
  0x00,
  0x00,
  0x00,
  0x0e, //Manufacturer name length
  0x44, 0x69, 0x73, 0x70, 0x6C, 0x61, 0x79, 0x73, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E,
  0x06, //Model Name String Length
  0x46, 0x43, 0x31, 0x39, 0x30, 0x31,
  0x0C, //Serial Number Data String Length
  0x30, 0x33, 0x32, 0x35, 0x2D, 0x4E, 0x43, 0x2D, 0x50, 0x52, 0x2D, 0x30,
  0x1B, //String Table Size
  0x01, //String Table Header - UTF 16BE
  0x00, //Language ID Structure – JPN/392
  0xC4,
  0x2A,
  0x0E,
  0x14, //Manufacturer ID Name Length
  //0x14, //Manufacturer ID Name Length
  0xC7, 0x30, 0xA3, 0x30, 0xB9, 0x30, 0xD7, 0x30, 0xEC, 0x30, 0xA4, 0x30, 0x2A, 0x68, 0x0F, 0x5F,
  0x1A, 0x4F, 0x3E, 0x79,
  0x00, //Model Name String Length
  0x00, //Serial Number String Length
  //Padding...
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x5A, //Checksum
};
// Display Information Extension DI-EXT block
/*
  byte EDIDArray2[128]={
  0x40 , //Block Header: Value must be “40h”.(See Section 3.1.1)
  0x01 , //DI-EXT Version Number: 1 (See Section 3.1.2)
  0x05 , //Digital Visual Interface (DVI) for Consumer Electronics
  0x80 , //EIA0xCEA 8610xA has a Letter Designation for the Version.
  0x41 , //ASCII Code indicates letter "A" is the Version. (See Section 3.2.2)
  0x00 , //There is no Revision Number. (See Section 3.2.2)
  0x00,
  0xDC , //‘11011100’ Digital Interface Data Format Description: (See Section 3.2.3)
  0x24 , //Digital interface uses the Standard Data Format: 24-Bit MSB-Aligned
  0x19 , //Minimum Pixel Clock Frequency is 25 MHz. (See Section 3.2.4)
  0x70 , //Maximum Pixel Clock Frequency is 112 MHz (0070h).
  0x00 , //(LSB first) (See Section 3.2.4)
  0x00 , //This is a Single Link DVI monitor. There is no Crossover Frequency.
  0x00 , //(LSB first) (See Section 3.2.4)
  0x00 , //Sub-Pixel Layout is not defined. Display is a CRT. (See Section 3.3.1)
  0x02 , //Sub-Pixel Configuration is “Stripe”. CRT is an Aperture Grill.
  0x00 , //Sub-Pixel Shape is not defined. Display is a CRT. (See Section 3.3.1)
  0x1F , //Horizontal Pixel Pitch is 0.31 mm. (See Section 3.3.2)
  0x00 , //Vertical Pixel Pitch is 0.0 mm CRT is an Aperture Grill(See Section 3.3.2)
  0x26 , //‘00100110’ Major Display Device Characteristics: (See Section 3.3.3)
  0x01 , //‘00000001’ Miscellaneous Display Capabilities: (See Section 3.4.1)
  0x00 , //‘00000000’ Frame Rate Conversion: (See Section 3.4.2)
  0x00 , //Vertical Frame Rate Conversion Frequency: (See Section 3.4.2)
  0x00 , //’0000h’ => Vertical Frame Rate Conversion Frequency is not available.
  0x00 , //Horizontal Frame Rate Conversion Frequency: (See Section 3.4.2)
  0x00 , //’0000h’ => Horizontal Frame Rate Conversion Frequency is not available.
  0x42 , //‘01000010’ Display0xScan Orientation: (See Section 3.4.3)
  0x01 , //‘01h’ => Default Color0xLuminance Decoding is BGR (additive colour).
  0x03 , //‘03h’ => Preferred Color0xLuminance Decoding is Yxx per (SMPTE
  0x8F , //'10001111' Color0xLuminance Decoding Capabilities include:
  0xE0 , //'11100000' • BGR (additive colour)
  0x00 , //‘00000000’ Monitor Colour Depth: (See Section 3.4.5)
  0x08 , //BGR Monitor Colour Depth is 8 bits for colour blue on Sub-Channel 0.
  0x08 , //BGR Monitor Colour Depth is 8 bits for colour green on Sub-Channel 1.
  0x08 , //BGR Monitor Colour Depth is 8 bits for colour red on Sub-Channel 2.
  0x08 , //YCrCb Monitor Colour Depth is 8 bits for Cb Sub-Channel 0.
  0x08 , //YCrCb Monitor Colour Depth is 8 bits for Y on Sub-Channel 1.
  0x08 , //YCrCb Monitor Colour Depth is 8 bits for Cr on Sub-Channel 2.
  0xF0 , //'11110000' Aspect Ratio Conversion: The display supports Full Mode , //Zoom Mode,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x53};
*/
void setup()
{
  pinMode(hotplugpin, OUTPUT); // initialize as output
  digitalWrite(hotplugpin, LOW); // unplug the cable

  Wire.begin(EDID_SLAVE); // join i2c bus, slave mode
  Wire.onReceive (receiveEvent); // interrupt handler for incoming messages
  Wire.onRequest (requestEvent); // interrupt handler for when data is wanted
  Serial.begin(9600); // start serial for output - the output is displayed via the  built - in Arduino serial interface

  digitalWrite(hotplugpin, HIGH); // plug in cable
}
void loop()
{
  byte y = 0;
  int x = 0;
  byte temp = 0;
  while (z < 128)
  {
    y = 0;
    while (y < 1)
    {
      temp = EDIDArray[z]; // save off current value
      EDIDArray[z] = 0xff; // modify each value in turn to be 0xff (use y to iterate through each value per byte)
      digitalWrite(hotplugpin, LOW); // unplug the cable
      delay (10);
      digitalWrite(hotplugpin, HIGH); // plug in cable
      delay (1500);
      Serial.print(z);
      Serial.print(":");
      x = y;
      Serial.print(x);
      Serial.print("\n");

      EDIDArray[z] = temp; // restore value to structure
      y = y + 1;
    }
    z = z + 1;
  }

}
void receiveEvent(int howMany)
{
  while (Wire.available()) // loop through all but the last
  {
    int x = Wire.read(); // receive byte as an integer
    Serial.println(x); // print the integer
  }
  int x = Wire.read(); // receive byte as an integer
}
void requestEvent()
{

  ////// fix up checksums /////

  int c = 0;
  int d = 0;
  byte csum = 0;
  for (int x = 0; x < 127; x++)
    csum += EDIDArray[x];
  c = csum;
  d = 256 - c;
  EDIDArray[127] = d;

  c = 0;
  d = 0;
  csum = 0;
  for (int x = 0; x < 127; x++)
    csum += EDIDArray2[x];
  c = csum;
  d = 256 - c;
  EDIDArray2[127] = d;

  if (count == 1)
  {
    Wire.write(EDIDArray, 128); // !!Need to change BUFFER_LENGTH to 128 in wire.h and TWI_BUFFER_LENGTH to 128 in twi.h
    count = 2;
  }
  else
  {
    Wire.write(EDIDArray2, 128);
    count = 1;
  }
}


