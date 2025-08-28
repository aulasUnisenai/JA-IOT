#define BLYNK_TEMPLATE_ID "id" // ID
#define BLYNK_TEMPLATE_NAME "nome" // Nome da aplicação
#define BLYNK_AUTH_TOKEN "token" // token

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "nome";     // nome do Wi-Fi -  usar roteador
char pass[] = "senha";   // senha do Wi-Fi - usar roteador

int ledExterno = 4;          // GPIO do LED externo
bool ledState = false;       // Estado atual do LED
BlynkTimer timer;

// --- Função que controla o LED pelo app (botão V0)
BLYNK_WRITE(V0) {
  ledState = param.asInt();
  digitalWrite(ledExterno, ledState);
  Serial.print("LED alterado pelo APP: ");
  Serial.println(ledState ? "LIGADO" : "DESLIGADO");
}

// --- Envia status do Wi-Fi para o Blynk
void sendWiFiStatus() {
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.virtualWrite(V1, "Wi-Fi: Conectado");
  } else {
    Blynk.virtualWrite(V1, "Wi-Fi: Desconectado");
  }
}

// --- Reconexão automática Wi-Fi + Blynk
void checkConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi caiu, tentando reconectar...");
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
  }
  if (!Blynk.connected()) {
    Serial.println("Blynk caiu, tentando reconectar...");
    Blynk.connect();
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledExterno, OUTPUT);
  digitalWrite(ledExterno, LOW);

  // Conexão inicial Wi-Fi
  WiFi.begin(ssid, pass);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());

  // Conexão inicial Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timers
  timer.setInterval(5000L, sendWiFiStatus); // Envia status Wi-Fi a cada 5s
  timer.setInterval(10000L, checkConnection); // Verifica reconexão a cada 10s
}

void loop() {
  Blynk.run();
  timer.run();
}
