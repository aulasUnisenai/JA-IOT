int ledExterno = 4; // GPIO usado

void setup() {
  pinMode(ledExterno, OUTPUT);
  digitalWrite(ledExterno, LOW); // Led começa apagado
}

void loop() {
  digitalWrite(ledExterno, HIGH); // Acender o led
  delay(1000);
  digitalWrite(ledExterno, LOW);  // Apagar o led
  delay(1000);
}
