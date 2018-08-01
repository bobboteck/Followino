/******************************************************************************
 * Followino Test sensori di riga
 * 
 * Created 01/08/2018 - By Roberto D'Amico
 * 
 * Descrizione: Questo programma permette di effettuare un test sui 6 sensori 
 * di riga del Robot e di mostrarne i valori letti tramite il Serial Plotter
 * del IDE di Arduino. Il LED su Arduino Nano si accende e spenge tra una
 * conversione e l'altra (i tempi sono veloci per riuscire a vederlo bene), il
 * LED_STATUS_1 si accende per il tempo necessario alla lettura di tutti i 6
 * sensori di riga, il LED_STATUS_2 invece si accende il tempo necessario ad
 * inviare i dati tramite Seriale al PC.
 * 
 * Modalità di test: E' sufficiente collegare il Robot al PC tramite il cavo 
 * USB usato per la programmazione di Arduino, dopo averlo programmto avviare
 * il Serial Plotter per visualizzare graficamente lo stato dei sensori.
 * 
 * 
 * 
 * MIT License
 * 
 * Copyright (c) 2018 LinFA
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/ 
#define LED_STATUS_1  4
#define LED_STATUS_2  9

void setup() 
{
  // Digital output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_STATUS_1, OUTPUT);
  pinMode(LED_STATUS_2, OUTPUT);
  // Analog INPUT
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  // Init Serial
  Serial.begin(9600);
  while (!Serial);
}

void loop() 
{
  digitalWrite(LED_STATUS_1, HIGH);
  digitalWrite(LED_STATUS_2, LOW);
  
  // Read all line sensors
  digitalWrite(LED_BUILTIN, HIGH);
  int S0 = analogRead(A0);
  digitalWrite(LED_BUILTIN, LOW);
  int S1 = analogRead(A1);
  digitalWrite(LED_BUILTIN, HIGH);
  int S2 = analogRead(A2);
  digitalWrite(LED_BUILTIN, LOW);
  int S3 = analogRead(A3);
  digitalWrite(LED_BUILTIN, HIGH);
  int S4 = analogRead(A4);
  digitalWrite(LED_BUILTIN, LOW);
  int S5 = analogRead(A5);

  digitalWrite(LED_STATUS_1, LOW);
  digitalWrite(LED_STATUS_2, HIGH);

  // Send data to Arduino IDE - Serial Plotter
  Serial.print(S0);
  Serial.println(",");
  Serial.print(S1);
  Serial.println(",");
  Serial.print(S2);
  Serial.println(",");
  Serial.print(S3);
  Serial.println(",");
  Serial.print(S4);
  Serial.println(",");
  Serial.print(S5);

  digitalWrite(LED_STATUS_2, LOW);
  
  delay(500);
}