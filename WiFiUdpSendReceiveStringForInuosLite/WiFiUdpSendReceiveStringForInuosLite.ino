
/*
  WiFi UDP Send and Receive String

 This sketch wait an UDP packet on localPort using a WiFi shield.
 When a packet is received an Acknowledge packet is sent to the client on port remotePort

 Circuit:
 * WiFi shield attached

 created 30 December 2012
 by dlf (Metodo2 srl)

 */



#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

int status = WL_IDLE_STATUS;
//char ssid[] = "Pretty Fly WiFi"; //  your network SSID (name)
//char password[] = "2444666668888888";    // your network password (use for WPA, or use as key for WEP)

const char* ssid = "MeltingSpace";
const char* password = "01234567890";

IPAddress remoteIp(255,255,255,255);
byte bufer[9] = { 0,0,0,0,0,0,0,0,0};

int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back

unsigned int loopcounter = 0;

WiFiUDP Udp;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

//    Serial.println();
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  
//  Serial.println("Connected to wifi");
//  printWifiStatus();
//
//  Serial.println("\nStarting connection to server...");
//  // if you get a connection, report back via serial:
  
  Udp.begin(localPort);
}

void loop() {

if (Serial.available()>9) {
    Serial.readBytes(bufer, 9);

    //Serial.print(loopcounter);
    //Serial.println("serial received...");
    //bufer[0] = Serial.read();
    Udp.beginPacket(remoteIp, 5999);
    Udp.write((char*)bufer);
    Udp.endPacket();
   // loopcounter = 0;
  }
//  if ( loopcounter > 200000) // if there is idle and there is serial trash left, clear it
//  {
//    while (Serial.available()<9 && Serial.available()>0)
//    {
//      Serial.read();
//      //Serial.println("serial clearing...");
//    }
//    loopcounter = 0;
//  }
//
//  loopcounter++;

  
  // if there's data available, read a packet
//  int packetSize = Udp.parsePacket();
//  if (packetSize) {
//    Serial.print("Received packet of size ");
//    Serial.println(packetSize);
//    Serial.print("From ");
//    remoteIp = Udp.remoteIP();
//    Serial.print(remoteIp);
//    Serial.print(", port ");
//    Serial.println(Udp.remotePort());
//
//    // read the packet into packetBufffer
//    int len = Udp.read(packetBuffer, 255);
//    if (len > 0) {
//      packetBuffer[len] = 0;
//    }
//    Serial.println("Contents:");
//    Serial.println(packetBuffer);
//
//    // send a reply, to the IP address and port that sent us the packet we received
//    Udp.beginPacket(Udp.remoteIP(), 5999);
//    Udp.write(ReplyBuffer);
//    Udp.endPacket();
//  }

}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}




