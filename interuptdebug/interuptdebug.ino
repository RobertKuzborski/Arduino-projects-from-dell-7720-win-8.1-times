
const byte interruptPin = 7;
const byte discardedPortPin[2] = {1,2};

byte debug = 0;
int debugi = 0;
int looptimer = 0;
byte keys = 0;
byte lastkeys = 0;

void setup() {
  Serial.begin(115200); // for Monitoring and Debugging
DDRD = DDRD | B11000000; // sets port D two last pins to output in order to ignore reading of these
  
 for(byte i = 0; i < sizeof(discardedPortPin); i++)  // Set unused port pins to low in order to skip reading useless bytes
 {
    //pinMode(discardedPortPin[i], OUTPUT);  
 }

  
 // pinMode(interruptPin, INPUT_PULLUP);  // Because by default it is high
 attachInterrupt(digitalPinToInterrupt(interruptPin), itpp, FALLING); //read which key is pressed and edit key mapping in USNkeyboard tab >>> function keyBoard
}
void itpp()
{
  Serial.println("X");
  
  //PORTD = B00000000;
  keys = PIND;
  keys &= ~(1<<5);
  //keys &= ~(1<<7);
  //keys &= ~(1<<8);
  looptimer = 0;
  
  Serial.println(keys,BIN);
  Serial.println(keys);
}
void loop() {
  if (looptimer > 20000)
  {
    looptimer = 0;
    keys = 0;
  }
  looptimer ++;
  //debug=digitalRead(12);
 //debugit();
 if (keys == lastkeys && keys == 0)
 {
  lastkeys = keys; // if all zero set zero
 }
 else if ( lastkeys == keys && lastkeys != 0)
 {
  lastkeys = keys; //keep keys same as they were
 }
 else if (lastkeys != keys && keys != 0)
 {
  Serial.print("YES!! : ");
  Serial.println(keys);
  Serial.println(looptimer);
  lastkeys = keys; // update keys since these changed
 }
 else if (lastkeys != keys && keys == 0)
 {
  lastkeys = 0;
 }
 else if ( lastkeys != keys && lastkeys == 0)
 {
  Serial.print("YES!! : ");
  Serial.println(keys);
  lastkeys = keys;
 }
}
