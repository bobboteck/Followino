/******************************************************************************
 * Followino Test pulsanti
 * 
 * Created 02/08/2018 - By Roberto D'Amico
 * 
 * Descrizione: ...
 * 
 * Modalità di test: ...
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
#define PUSH_BUTTON_START 5
#define PUSH_BUTTON_STOP  6

void setup()
{
  // Digital output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_STATUS_1, OUTPUT);
  pinMode(LED_STATUS_2, OUTPUT);
  // Digital input
  pinMode(PUSH_BUTTON_START, INPUT);
  pinMode(PUSH_BUTTON_STOP, INPUT);

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  if(digitalRead(PUSH_BUTTON_START)==HIGH)
  {
    digitalWrite(LED_STATUS_1, HIGH);
  }
  else
  {
    digitalWrite(LED_STATUS_1, LOW);
  }

  if(digitalRead(PUSH_BUTTON_STOP)==HIGH)
  {
    digitalWrite(LED_STATUS_2, HIGH);
  }
  else
  {
    digitalWrite(LED_STATUS_2, LOW);
  }
}
