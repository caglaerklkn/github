#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 32
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi bağlandı");

  dht.begin();
}

void loop() {
  float sicaklik = dht.readTemperature();
  float nem = dht.readHumidity();

  if (sicaklik != NAN && nem != NAN) {
    Serial.println("Sıcaklık: " + String(sicaklik) + " °C");
    Serial.println("Nem: " + String(nem) + "%");
  } else {
    Serial.println("Veri okunamadı.");
  }

  delay(1000);
}
