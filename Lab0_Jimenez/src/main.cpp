#include <Arduino.h>
#include <avr/io.h>

int main(){
  Serial.begin(9600);
  Serial.flush();

  while (1){
    Serial.println("hello world");
    _delay_ms(1000);
  }
  return 0;
}
