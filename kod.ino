#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_MP3_TX = 2;
static const uint8_t PIN_MP3_RX = 3;
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

DFRobotDFPlayerMini player;
bool ilkSinyalAlindi = false;

void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT);

  softwareSerial.begin(9600);
  
  if (player.begin(softwareSerial)) {
   Serial.println("OK");

    player.volume(15);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");

  }
}

void loop() {
  if (Serial.available() > 0) {
    if (!ilkSinyalAlindi) {
      Serial.println("Sinyal Alındı");
      player.play(1);
      ilkSinyalAlindi = true;
    }
    Serial.read();
  }
}
