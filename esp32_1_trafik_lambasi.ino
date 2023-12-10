// SKY LAB SKYSIS GÖMÜLÜ SİSTEMLER EKİBİ
// ESP CHALLENGE
// WiFi İle Durum Bildiren Trafik Lambası Dizisi
// Çağla ERKALKAN 
// Bu projede 1 adet ESP32, 3 adet LED, 3 adet direnç kullanılmıştır

#include <WiFi.h> // Wifi kütüphanesini ekledik

// LED pinlerini tanımladık
#define LED_KIRMIZI 27
#define LED_SARI 26
#define LED_YESIL 25

// LED ışıklarının yanıp sönme sürelerini ayarladık
#define DELAY_KIRMIZI 2000
#define DELAY_SARI 1000
#define DELAY_YESIL 2000

// Server adresi ve portunu belirledik
const char* SERVER_IP = "192.168.1.100";
const int SERVER_PORT = 8080;

// Trafik lambasının durumunu belirledik, kodun devamında kullanılacak
int durum = 0; // Yeşil

void setup() {
  // LED pinlerini çıkış olarak ayarla
  pinMode(LED_KIRMIZI, OUTPUT);
  pinMode(LED_SARI, OUTPUT);
  pinMode(LED_YESIL, OUTPUT);

  // Wifi'ye bağlan 
  // SSID için Wokwi-GUEST i kullandık, şifresiz ağ
  //SSID yerine WİFİ adı, PASSWORD yerine şifresi gelecek
  WiFi.begin("Wokwi-GUEST", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Serial monitöre bağlantıyı kurduğumuzu bildirdik
  Serial.println("");
  Serial.println("Wifi'ye bağlanıldı");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Trafik lambasının durumunu için koşul belirledik
  durum++;
  if (durum > 3) {
    durum = 0;
  }

  // LED'leri uygun şekilde ayarla
  // Trafik lambasını önce kırmızı, 
  // sonra yanıp sönen sarı 
  // ve en son yeşil yanacak şekilde ayarladık
  switch (durum) {
    case 1:
      digitalWrite(LED_KIRMIZI, HIGH);
      digitalWrite(LED_SARI, LOW);
      digitalWrite(LED_YESIL, LOW);
      break;
    case 2:
      digitalWrite(LED_KIRMIZI, LOW);
      digitalWrite(LED_SARI, HIGH);
      delay(500);
      digitalWrite(LED_SARI, LOW);
      delay(500);
      digitalWrite(LED_SARI, HIGH);
      digitalWrite(LED_YESIL, LOW);
      break;
    case 3:
      digitalWrite(LED_KIRMIZI, LOW);
      digitalWrite(LED_SARI, LOW);
      digitalWrite(LED_YESIL, HIGH);
      break;
  }

  // Trafik lambasının durumunu bir mesaj olarak server'a gönderdik
  String mesaj = "";
  if (digitalRead(LED_KIRMIZI) == HIGH) {
    mesaj = "Kırmızı";
  } else if (digitalRead(LED_SARI) == HIGH) {
    mesaj = "Sarı";
  } else {
    mesaj = "Yeşil";
  }

  WiFiClient client;
  if (client.connect(SERVER_IP, SERVER_PORT)) {
    client.write(mesaj.c_str());
    client.flush();
    client.stop();
  }

  // 5 saniye bekle
  delay(5000);
}
