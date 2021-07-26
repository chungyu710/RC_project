/*
* Sample code by Dejan Nedelkovski, www.HowToMechatronics.com
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

/*
 * ---------- WIRING ----------
 * ARDUINO UNO  -> nRF24L01 module
 * Vcc          -> 3V3
 * GND          -> GND
 * IO7          -> CE   (chip enable)
 * IO8          -> CSN  (SPI chip select) (active low?)
 * IO11         -> MOSI (SPI master out, slave in)
 * IO12         -> MISO (SPI master in, slave out)
 * IO13         -> SCK  (SPI clock)
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}
