#include <string.h>
#include "uart.h"

bool stringComplete = false;

void uart_rx() {
  if (!Serial.available()){
    return;
  }

  char buff[20];
  int i = 0;
  while (Serial.available()) {
    buff[i] = Serial.read();
    i++;
  }

Serial.print(buff[i-3]);
  if (buff[i-3] == '+') {
    Serial.print(buff);
  }
  delay(3000);
}
  


