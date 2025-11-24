// sign_glove.ino
// Multiple Flex Sensor Reader
// Flex sensors connected to A0 - A4
// Each sensor forms a voltage divider with a 10kΩ resistor to GND

#include "HC-05.h"

const int flexPins[5] = { A4, A3, A2, A1, A0 };  // analog input pins
int flexValues[5];                               // array to store readings

// Prevent sending duplicate letters
String lastLetter = "";

void setup() {
  Serial.begin(9600);

  //start bluetooth
  hc05_begin(9600);
  delay(500);

  Serial.println("ASL Glove and Bluetooth Ready.");
}

void loop() {
  // Read all 5 sensors
  for (int i = 0; i < 5; i++) {
    flexValues[i] = analogRead(flexPins[i]);
  }

  String letter = detectLetter();

  Serial.print("Detected: ");
  Serial.println(letter);

  // Only send when the letter changes
  if (letter != "None" && letter != lastLetter) {
    hc05_transmit(letter);
    lastLetter = letter;
  }
}

// // Print readings
// Serial.print("Flex values: ");
// for (int i = 0; i < 5; i++) {
//   Serial.print(flexValues[i]);
//   if (i < 4) Serial.print(" | ");
// }
// Serial.println();

String detectLetter() {
  //Aa
  if ((flexValues[0] < 400) && (flexValues[1] > 900) && (flexValues[2] > 900) && (flexValues[3] > 900) && (flexValues[4] > 900)) {
    Serial.println("A");
  }
  //Bb
  else if ((flexValues[0] > 800) && (flexValues[1] < 900) && (flexValues[2] < 900) && (flexValues[3] < 900) && (flexValues[4] < 900)) {
    Serial.println("B");
  }
  //Cc
  else if ((flexValues[0] < 400) && (flexValues[1] > 800) && (flexValues[2] > 800) && (flexValues[3] > 800) && (flexValues[4] > 600)) {
    Serial.println("C");
  }
  //Dd
  else if ((flexValues[0] < 400) && (flexValues[1] < 500) && (flexValues[2] < 500)) {
    Serial.println("D");
  }
  //Ee
  else if ((flexValues[0] < 900) && (flexValues[1] > 900) && (flexValues[2] > 900) && (flexValues[3] > 900) && (flexValues[4] > 900)) {
    Serial.println("E");
  }
  //Ff
  else if ((flexValues[0] < 600) && (flexValues[1] < 800) && (flexValues[2] < 800) && (flexValues[3] < 800) && (flexValues[4] < 800)) {
    Serial.println("F");
  }
  //Gg
  else if ((flexValues[0] < 400) && (flexValues[1] < 400) && (flexValues[2] > 900) && (flexValues[3] > 900) && (flexValues[4] > 900)) {
    Serial.println("G");
  }
  //Hh
  else if ((flexValues[0] > 700) && (flexValues[1] < 600) && (flexValues[2] < 600) && (flexValues[3] > 900) && (flexValues[4] > 900)) {
    Serial.println("H");
  }
  //Ii
  else if ((flexValues[0] > 700) && (flexValues[1] > 900) && (flexValues[2] > 900) && (flexValues[3] > 900) && (flexValues[4] < 600)) {
    Serial.println("I");
  }
  //Jj
  else if ((flexValues[0] < 400) && (flexValues[1] > 900) && (flexValues[2] > 900) && (flexValues[3] > 900) && (flexValues[4] < 600)) {
    Serial.println("J");
  }
  //Kk
  else if ((flexValues[0] < 600) && (flexValues[1] < 600) && (flexValues[2] < 600) && (flexValues[3] > 900) && (flexValues[4] > 900)) {
    Serial.println("K");
  }
  //Ll
  else if ((flexValues[0] < 700) && (flexValues[1] < 300) && (flexValues[2] > 900) && (flexValues[3] > 900) && (flexValues[4] > 900)) {
    Serial.println("L");
  }
  //Mm
  //Nn
  //Oo
  //Pp
  //Qq
  //Rr
  //Ss
  //Tt
  //Uu
  //Vv
  //Ww
  else if ((flexValues[0] > 600) && (flexValues[1] < 400) && (flexValues[2] < 400) && (flexValues[3] < 400) && (flexValues[4] > 800)) {
    Serial.println("W");
  }
  //Xx
  //Yy
  else if ((flexValues[0] > 500) && (flexValues[1] > 900) && (flexValues[2] > 900) && (flexValues[3] > 900) && (flexValues[4] > 500)) {
    Serial.println("Y");
  }
  //Zz
  else if ((flexValues[0] > 800) && (flexValues[1] < 500) && (flexValues[2] > 800) && (flexValues[3] > 800) && (flexValues[4] > 800)) {
    Serial.println("Z");
  } else {
    Serial.println("No Letter Detected");
  }

  delay(500);  // read twice per second
}
