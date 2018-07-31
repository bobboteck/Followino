/*
  test-led

  Semplice script di prova dei led di status collegati ai pin D4 (Status 1, red) e D9 (Status 2, green).

  Created 01 08 2018
  By Mauro Esposito / Roberto D'Amico

*/

int led_status_1 = 4;
int led_status_2 = 9;

void setup() {
  pinMode(led_status_1, OUTPUT);
  pinMode(led_status_2, OUTPUT);
}

void loop() {
  digitalWrite(led_status_1, HIGH);   // status 1 acceso
  digitalWrite(led_status_2, LOW);    // status 2 spento
  delay(1000);                        // pausa di un secondo
  digitalWrite(led_status_1, LOW);    // status 1 spento
  digitalWrite(led_status_2, HIGH);   // status 2 acceso
  delay(1000);                        // pausa di un secondo
}
