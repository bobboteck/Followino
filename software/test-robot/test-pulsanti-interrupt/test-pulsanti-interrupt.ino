/******************************************************************************
 * Followino Test pulsanti con interrupt.
 * 
 * Created 20/08/2018 - By Mauro Esposito
 * 
 * Descrizione: Questo programma permette di effettuare un test sui 2 pulsanti 
 * presenti sul Robot. Premendo il pulsante si START si accende il LED_STATUS_1
 * premendo il pulsante STOP si accende il LED_STATUS_2.
 * Quando si preme uno dei due pulsanti viene anche inviata una stringa tramite
 * seriale che possono essere visualizzate tramite il Serial Monitor di Arduino
 * IDE.
 * 
 * Nota: per i pulsanti accade che bisogna gestire via software il "bounce" che 
 * può essere causato dall'azione meccanica del pulsante. Un riferimento in cui 
 * viene spiegato di cosa parlo è descritto bene quì:
 * - https://www.allaboutcircuits.com/textbook/digital/chpt-4/contact-bounce/
 * per risolvere questa problematica, viene inserito un piccolo artificio software:
 * viene calcolato un piccolo delta tra due interrupt, così da filtrare i casi di 
 * bounce, scartandoli.
 * Questa soluzione non è ottimale, e per risolvere al meglio, bisognerebbe prevedere
 * lato software una capacità che consenta di applicare un piccolo ciclo di isteresi 
 * (filtro passa basso).
 * 
 * Modalità di test: E' sufficiente collegare il Robot al PC tramite il cavo 
 * USB usato per la programmazione di Arduino, dopo averlo programmto avviare
 * il Serial Monitor per visualizzare i messaggi.
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
#define LED_STATUS_1        4
#define LED_STATUS_2        9
#define PUSH_BUTTON_START   2   // interrupt 0
#define PUSH_BUTTON_STOP    3   // interrupt 1
#define INTERVALLO          1000

unsigned long newMillisEvent = 0;
int ledBuiltinStatus = HIGH;

int ledStateStart = LOW;   // all'inizio i led sono spenti.
int ledStateStop = LOW;   // all'inizio i led sono spenti.

unsigned long lastInterruptStart = 0;   // riferimento millis() dell'ultima volta che è stato gestito l'interrupt 0 con rimbalzo (gestione isteresi via software).
unsigned long lastInterruptStop = 0;    // riferimento millis() dell'ultima volta che è stato gestito l'interrupt 1 con rimbalzo (gestione isteresi via software).

void setup() {
  // Digital output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_STATUS_1, OUTPUT);
  pinMode(LED_STATUS_2, OUTPUT);
  
  // Digital input
  pinMode(PUSH_BUTTON_START, INPUT);
  pinMode(PUSH_BUTTON_STOP, INPUT);

  // inizializzazione interrupt pulsanti:
  attachInterrupt(0, manageLedStateStart, RISING);
  attachInterrupt(1, manageLedStateStop, RISING);

  // Init Serial
  Serial.begin(9600);
  while (!Serial);

  digitalWrite(LED_BUILTIN, ledBuiltinStatus);
}

void loop() {
  // Lampeggio del Led buitin su Arduino Nano
  if(millis() >= newMillisEvent) {
    if(ledBuiltinStatus==HIGH) {
      ledBuiltinStatus=LOW;
    } else {
      ledBuiltinStatus=HIGH;
    }
    digitalWrite(LED_BUILTIN, ledBuiltinStatus);
    newMillisEvent = millis() + INTERVALLO;
  }
}

void manageLedStateStart() {
  if(millis() - lastInterruptStart > 10) {
    Serial.println("Scattato interrupt per il pulsante di Start");
    ledStateStart = !ledStateStart;
    digitalWrite(LED_STATUS_1, ledStateStart);
    lastInterruptStart = millis();
  }
}

void manageLedStateStop() {
  if(millis() - lastInterruptStop > 10) {
    Serial.println("Scattato interrupt per il pulsante di Stop");
    ledStateStop = !ledStateStop;
    digitalWrite(LED_STATUS_2, ledStateStop);
    lastInterruptStop = millis();
  }
}
