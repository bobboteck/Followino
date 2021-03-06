/******************************************************************************
 * Followino Test Led
 * 
 * Created 01/08/2018 - By Mauro Esposito
 * 
 * Descrizione: Questo programma permette di effettuare un test sui 2 LED di
 * stato presenti sul Robot, una volta avviato i due LED si accendo e si 
 * spengono in modo alternato ogni secondo. 
 * 
 * Modalità di test: E' sufficiente collegare il Robot al PC tramite il cavo 
 * USB usato per la programmazione di Arduino.
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
  // Digital OUTPUT
  pinMode(LED_STATUS_1, OUTPUT);
  pinMode(LED_STATUS_2, OUTPUT);
}

void loop() 
{
  digitalWrite(LED_STATUS_1, HIGH);   // status 1 acceso
  digitalWrite(LED_STATUS_2, LOW);    // status 2 spento
  delay(1000);                        // pausa di un secondo
  digitalWrite(LED_STATUS_1, LOW);    // status 1 spento
  digitalWrite(LED_STATUS_2, HIGH);   // status 2 acceso
  delay(1000);                        // pausa di un secondo
}
