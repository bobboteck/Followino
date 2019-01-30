/******************************************************************************
 * Followino Test Bluetooth
 * 
 * Created 06/08/2018 - By Roberto D'Amico
 * 
 * Descrizione: Questo programma permette di scambiare informazioni con un 
 * dispositivo Bluetooth a cui viene associato. ...
 * 
 * Modalità di test: E' sufficiente collegare il Robot al PC tramite il cavo 
 * USB usato per la programmazione di Arduino, ...
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
int incomingData=0;
int counter=0;
unsigned long time, intervallo;

void setup() 
{
  Serial.begin(9600);
  intervallo = millis();
}

void loop()
{
  time = millis();
  
  // send data only when you receive data:
  if(Serial.available() > 0)
  {
    incomingData = Serial.parseInt();
    if(incomingData > 0)
    {
      Serial.print("Received: ");
      Serial.println(incomingData);
      counter = incomingData;
    }
  }

  if(time > intervallo+1000)
  {
    counter++;
    Serial.print("counter: ");
    Serial.println(counter);
    intervallo = millis();
  }
}