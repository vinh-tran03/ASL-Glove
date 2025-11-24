// =============================================================================
// HC-05 Bluetooth Module, HC-05.h
//
// Description: Provides a setup and transmit function for wireless Bluetooth
//    communication. Version 1 uses digital pins 0 (RX) and 1 (TX) that connect
//    to the HC-05's TXD and RXD pins, respectively, meaning the RX pin connects
//    to the TXD pin and the TX pin connects to the RXD pin. Version 2 utilizes
//    SoftwareSerial to allow alternative digital pins to be used for RX and TX.
// 
// Author: Braden Tillema
// =============================================================================

#ifndef HC_05_H
#define HC_05_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define RX_PIN 2 // Used for Version 2
#define TX_PIN 3 // Used for Version 2

/**
 * Initializes HC-05 wireless Bluetooth communication
 * \param baud_rate Specify the transmission speed (defaults to 9600)
 */
void hc05_begin(long baud_rate = 9600);

/**
 * Transmits a string message using the HC-05 module
 * \param message The string to transmit
 * \param nl Should a new line message be sent (defaults to false)
 */
void hc05_transmit(String message, bool nl = false);

#endif