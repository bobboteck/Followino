
/******************************************************************************
 * Followino Test motori utilizzando registri timer.
 * 
 * Created 16/08/2018 - By Mauro Esposito
 * 
 * Descrizione: Questo programma permette di effettuare un test del driver DRV8835
 * presente sul Robot.
 * Il test in maniera automatica prova a far andare avanti, indietro, destra e 
 * sinistra il robot. 
 * 
 * Configurazione pin del DRV8835:
 * MOTORA: motore a destra
 * MOTORB: motore a sinistra
 * pin:
 * -- AIN1/APHASE pin 8
 * -- AIN2/AENBL  pin 6  OCR0A
 * -- BIN1/BPHASE pin 7  
 * -- BIN2/BENBL  pin 5  OCR0B
 * -- MODE        +5V (Modalità Phase/Enable Mode, SM (Sign-Magnitude) http://www.tmasi.com/robotica/pwmtut/pwmtut_2.htm)
 * 
 * Se il processore utilizzare è un 328P sarebbe possibile utilizzare un calcolo del PWM
 * per i registri del timer TCCR1x (Timer 1) per sfruttare la frequenza di 20KHz a 16 bit.
 * Questo richiede l'utilizzo dei contatori ICR1x che su un arduino nano da noi utilizzato 
 * per questi test non viene esposto dal chip, cosa che invece è possibile fare da un arduino uno.
 * TODO: Bisogna eseguire questo test utilizzando i contatori ICR0x che sul nostro progetto sono 
 * correttamente fatti corrispondere a i pin D5 (OC0B, BIN2/BE) e D6 (OC0A, AIN2/AE) (Timer 0) 
 * La modalità di generazione del PWM sarà a 8 bit, bisogna impostare correttamente il timer TCCR0x
 * 
 * Modalità di test: E' sufficiente collegare il Robot al PC tramite il cavo 
 * USB usato per la programmazione di Arduino, dopo averlo programmto avviare
 * il Serial Monitor per visualizzare lo stato del comando inviato al motore.
 * ATTENZIONE: una volta caricato il programma, è importante che il robot sia sollevato 
 * da terra, per evitare spiacevoli incidenti se collegato ancora alla usb.
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
#include <avr/io.h>
#include <avr/interrupt.h>

#define PIN_MOTORA_ENABLE 6
#define PIN_MOTORA_PHASE 8
#define PIN_MOTORB_ENABLE 5
#define PIN_MOTORB_PHASE 7

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega32U4__)
  #define DRV8835MOTORSHIELD_USE_20KHZ_PWM
#endif

int motor_left[] = {PIN_MOTORB_PHASE, PIN_MOTORB_ENABLE};
int motor_right[] = {PIN_MOTORA_PHASE, PIN_MOTORA_ENABLE};

// ritardo tra un comando ed un altro inviati al driver:
int _delay = 2000;

// velocita' al massimo 400:
int _default_speed = 150; 

void setup() {
  Serial.begin(9600);
  // Setup motors
  
  // Initialize the pin states used by the motor driver shield
  // digitalWrite is called before and after setting pinMode.
  // It called before pinMode to handle the case where the board
  // is using an ATmega AVR to avoid ever driving the pin high, 
  // even for a short time.
  // It is called after pinMode to handle the case where the board
  // is based on the Atmel SAM3X8E ARM Cortex-M3 CPU, like the Arduino
  // Due. This is necessary because when pinMode is called for the Due
  // it sets the output to high (or 3.3V) regardless of previous
  // digitalWrite calls.
  
  digitalWrite(PIN_MOTORA_ENABLE, LOW);
  pinMode(PIN_MOTORA_ENABLE, OUTPUT);
  digitalWrite(PIN_MOTORA_ENABLE, LOW);
  digitalWrite(PIN_MOTORA_PHASE, LOW);
  pinMode(PIN_MOTORA_PHASE, OUTPUT);
  digitalWrite(PIN_MOTORA_PHASE, LOW);
  
  digitalWrite(PIN_MOTORB_ENABLE, LOW);
  pinMode(PIN_MOTORB_ENABLE, OUTPUT);
  digitalWrite(PIN_MOTORB_ENABLE, LOW);  
  digitalWrite(PIN_MOTORB_PHASE, LOW);
  pinMode(PIN_MOTORB_PHASE, OUTPUT);
  digitalWrite(PIN_MOTORB_PHASE, LOW);
  
#ifdef DRV8835MOTORSHIELD_USE_20KHZ_PWM
  // timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  // FIXME: utilizzare timer 0 per arduino nano, scrivi quì il perchè è meglio del timer 2.
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;
#endif
}

void loop() {
  Serial.println("-- Muovi avanti >>>>");
  drive_forward();
  delay(_delay);
  motor_stop();
  delay(_delay);
  
  Serial.println("-- Muovi indietro <<<<");
  drive_backward();
  delay(_delay);
  motor_stop();
  delay(_delay);
 
  Serial.println("-- Muovi a sinistra SSSS");
  turn_left();
  delay(_delay);
  motor_stop();
  delay(_delay);
  
  Serial.println("-- Muovi a destra DDDD");
  turn_right();
  delay(_delay);
  motor_stop();
  delay(_delay);
  
  Serial.println("-- ...");
  delay(_delay);
}

void motor_stop(){
  setSpeeds(0, 0);
  delay(25);
}

void drive_forward(){
  setSpeeds(_default_speed, _default_speed);
}

void drive_backward(){
  setSpeeds(-(_default_speed), -(_default_speed));
}

void turn_left(){
  setSpeeds(_default_speed, -0);
}

void turn_right(){
  setSpeeds(-0, _default_speed);
}

void setSpeeds(int leftSpeed, int rightSpeed) {
  setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
}

void setLeftSpeed(int speed) {
  boolean reverse = 0;
  if (speed < 0) {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 400)  // max 
    speed = 400;
    
#ifdef DRV8835MOTORSHIELD_USE_20KHZ_PWM
  OCR0B = speed;
#else
  analogWrite(motor_left[1], speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif 

  if (reverse)
    digitalWrite(motor_left[0], HIGH);
  else
    digitalWrite(motor_left[0], LOW);
}


void setRightSpeed(int speed) {
  boolean reverse = 0;
  if (speed < 0) {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 400)  // max 
    speed = 400;
    
#ifdef DRV8835MOTORSHIELD_USE_20KHZ_PWM
  OCR0A = speed;
#else
  analogWrite(motor_right[1], speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif 

  if (reverse)
    digitalWrite(motor_right[0], HIGH);
  else
    digitalWrite(motor_right[0], LOW);
}

