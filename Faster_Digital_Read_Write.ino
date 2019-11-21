#include "FastIO.h"

struct IO out13;
struct IO in7;

void setup() {

  Serial.begin(115200);

  out13 = set_IO(13, OUTPUT);
  in7 = set_IO(7, INPUT_PULLUP);

  Serial.println("READY");
}

void loop() {

  // blink pin 13, read pin 7
  //LED ON
  dig_write(out13, 1);
  delay(500);

  //LED OFF
  dig_write(out13, 0);
  delay(500);

  //print out pin7 state
  Serial.println(dig_read(in7), DEC);

}

