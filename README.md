# bouton
debounce bouton for Arduino with memo state 

exemple code
#include <Arduino.h> 
#include "bouton.h"

#define LED_13 13
#define LED_12 12
#define LED_4 4

Bouton b = Bouton(Bouton::D10, 5);

void setup() {
  pinMode(LED_13, OUTPUT);
  pinMode(LED_12, OUTPUT);
  pinMode(LED_4, OUTPUT);
  digitalWrite(LED_13, LOW);
  digitalWrite(LED_12, LOW);
}

void loop() {
  digitalWrite(LED_13, LOW);
  digitalWrite(LED_12, LOW);
  digitalWrite(LED_4, LOW);
  b.update();
      
  if (b.state()) {
      digitalWrite(LED_12, HIGH);
  }
  else {
      digitalWrite(LED_12, LOW);
  }  
  if (b.oldState() ) {
      digitalWrite(LED_13, HIGH);
  } 
   else {
      digitalWrite(LED_13, LOW);
  }   
  if (b.memoState() == Bouton::UN) {
      digitalWrite(LED_4, HIGH);
  }
  else {
      digitalWrite(LED_4, LOW);
  }    
  
}
