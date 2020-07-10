
/*

Use this sketch to read software serial out of a Attiny 85
So just to clarify I have an ATTINY85 on a breaadboard connected to 5v, ground, reset and a wire from ATTINY TX to Arduino Uno board RX.
Ref      https://forum.arduino.cc/index.php?topic=404775.0
Run this sketch on Arduino chip:


*/
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    Serial.print((char) Serial.read());
    delay(10);
  }
}

