// =============================================================================
// HC-05 Bluetooth Module, HC-05.cpp
//
// Description: Provides a setup and transmit function for wireless Bluetooth
//    communication. Version 1 uses digital pins 0 (RX) and 1 (TX) that connect
//    to the HC-05's TXD and RXD pins, respectively, meaning the RX pin connects
//    to the TXD pin and the TX pin connects to the RXD pin. Version 2 utilizes
//    SoftwareSerial to allow alternative digital pins to be used for RX and TX.
// 
// Author: Braden Tillema
// =============================================================================

#include "HC-05.h"

// Version 2: SoftwareSerial
SoftwareSerial bluetooth(RX_PIN, TX_PIN);

/**
 * Initializes HC-05 wireless Bluetooth communication
 * \param baud_rate Specify the transmission speed (defaults to 9600)
 */
void hc05_begin(long baud_rate = 9600) {

  // Version 1: Serial
  // Serial.begin(baud_rate);

  // Version 2: SoftwareSerial
  bluetooth.begin(baud_rate);

};

/**
 * Transmits a string message using the HC-05 module
 * \param message The string to transmit
 * \param nl Should a new line message be sent (defaults to false)
 */
void hc05_transmit(String message, bool nl = false) {

  // Version 1: Serial
  // Serial.print(message);
  // if (nl == true) Serial.println("");

  // Version 2: SoftwareSerial
  bluetooth.print(message);
  if (nl == true) bluetooth.println("");

};