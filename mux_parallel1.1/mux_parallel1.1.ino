byte muxNr = 0;

byte muxBank[6][8] = { 
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
};

void setup() {

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  //analogReadResolution(8); //'analogReadResolution' was not declared in this scope
  
  Serial.begin(250000);
}

void loop() {
  // put your main code here, to run repeatedly:
muxNr = PINB;
for (int i = 0; i < 6; i++)
//muxBank [muxNr] [i] = analogRead (i);
muxBank [i] [muxNr] = analogRead(i);

Serial.println(muxNr);


//if (muxNr == 7) printBank();
 //printcurrent();
printraw();

}

void printBank(){
  for( int x = 0; x < 6; x++)
  {
    for( int y = 0; y < 8; y++)
    {
      //Firmata.sendAnalog(x*8+y, x*8+y);
      Serial.print(x*8+y);
      Serial.print(" = ");
      Serial.print(muxBank[x][y]);
      Serial.print(" | ");
    }
    Serial.println(" ");
  }
  Serial.println("-----------------------------------");
}

void printcurrent(){
  for( int x = 0; x < 6; x++)
  {
    
      //Firmata.sendAnalog(x*8+y, x*8+y);
      Serial.print(x*8+muxNr);
      Serial.print(" = ");
      Serial.print(muxBank[x][muxNr]);
      Serial.print(" | ");
   
    Serial.println(" ");
  }
  Serial.println("-----------------------------------");
}
void printraw(){
  Serial.println("-----------------------------------");
  Serial.write(muxBank[1], 48);
}

