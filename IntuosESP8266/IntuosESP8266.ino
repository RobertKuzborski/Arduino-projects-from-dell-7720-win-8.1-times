#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

byte bufer[9] = { 0,0,0,0,0,0,0,0,0};
unsigned int loopcounter = 0;
const char* ssid = "MeltingSpace";
const char* password = "01234567890";
unsigned int localPort = 2390;

WiFiUDP Udp;

void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);
 delay(10);

// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
 

  // Print the IP address
  Serial.println(WiFi.localIP());

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
  
}

void loop() {
  // put your main code here, to run repeatedly:

if (Serial.available()>9) {
   Serial.readBytes(bufer, 9);

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write((char*)bufer);
    Udp.endPacket();

   loopcounter = 0;
}

loopcounter++;
}
