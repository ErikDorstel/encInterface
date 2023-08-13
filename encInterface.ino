bool debug=true;

#include "encoder.h"
#include "uart.h"

void setup() {
  Serial.begin(115200);
  initEncoder();
  initUART(); }

void loop() { uartWorker(); }
