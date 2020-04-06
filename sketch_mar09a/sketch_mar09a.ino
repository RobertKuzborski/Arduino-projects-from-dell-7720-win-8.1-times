volatile int state = LOW;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (3, OUTPUT);
attachInterrupt(0, log, FALLING);
}

void loop() {
  
  if (state == LOW){
    analogWrite (3,LOW);
    Serial.print(millis());
    Serial.print( " " );
    Serial.println(analogRead(A0)); 
  }
  else {
    analogWrite (3,analogRead(A0));
  }
  // put your main code here, to run repeatedly:

}

void log (){
state = !state; //if state if high changes to low and oppositely
}
