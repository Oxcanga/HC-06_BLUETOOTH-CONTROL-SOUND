#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_MP3_TX = 2; // DFPlayer modülünde RX  pinine
static const uint8_t PIN_MP3_RX = 3; // DFPlayer modülünde TX pinine
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Oynatıcı objemizi Player adında oluşturuyoruz.
DFRobotDFPlayerMini player;
bool ilkSinyalAlindi = false;

void setup() {
  // Seri iletişimi başlat
  Serial.begin(9600);
  // RX pinini tanımla (Genellikle 0 numaralı pin RX pinidir)
  pinMode(0, INPUT);

  softwareSerial.begin(9600);

  // Eğer arduino ile dfplayer arasında bağlantı kurulmuş ise OK yazıdırıyoruz
  if (player.begin(softwareSerial)) {
   Serial.println("OK");

    // Ses seviyesini belirliyoruz (0 to 30).
    player.volume(15);
    // sd karttaki ilk müziği oynatıyoruz.
  } else {
    // dfplayer ile bağlantının kurulamadığını yazdırıyoruz.
    Serial.println("Connecting to DFPlayer Mini failed!");

  }
}

void loop() {
  // Eğer RX pininden bir sinyal alınırsa
  if (Serial.available() > 0) {
    // Ve eğer bu alınan ilk sinyal ise
    if (!ilkSinyalAlindi) {
      // Seri monitöre "jsj" yaz
      Serial.println("jsj");
      player.play(1);
      // İlk sinyal alındı olarak işaretle
      ilkSinyalAlindi = true;
    }
    // Gelen sinyali oku ve bir sonraki sinyal için hazır ol
    Serial.read();
  }
}