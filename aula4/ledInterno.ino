// Definir o pino 2 como o led interno
#define LED_BUILTIN 2

// Definições - roda ao iniciar
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

// Repetição com o comportamento do led
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // Liga o led
  delay(1000);                       // Aguarda um segundo
  digitalWrite(LED_BUILTIN, LOW);    // Desliga o led
  delay(1000);                       // Aguarda um segundo
}
