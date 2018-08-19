
/******************************************************************************
 * Followino Test algoritmo LF.
 * 
 * Created 19/08/2018 - By Mauro Esposito
 * 
 * Descrizione: Test funzionalità completa LF del robot.
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
 * 
 * Modalità di test: porre il robot su una linea nera..
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
#include <QTRSensors.h>

#define PIN_MOTORA_ENABLE 6
#define PIN_MOTORA_PHASE 8
#define PIN_MOTORB_ENABLE 5
#define PIN_MOTORB_PHASE 7

#define LED_STATUS_1  4
#define LED_STATUS_2  9

#define PUSH_BUTTON_START 2
#define PUSH_BUTTON_STOP  3

#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             0  // emitter is controlled by digital pin 2

#define Kp             0.3  // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd             14    // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 

#define rightMaxSpeed  400  // max speed of the robot
#define leftMaxSpeed   400  // max speed of the robot

#define rightBaseSpeed 200  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed  200  // this is the speed at which the motors should spin when the robot is perfectly on the line

QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


int motor_left[] = {PIN_MOTORB_PHASE, PIN_MOTORB_ENABLE};
int motor_right[] = {PIN_MOTORA_PHASE, PIN_MOTORA_ENABLE};

// ritardo tra un comando ed un altro inviati al driver:
int _delay = 2000;

// velocita' al massimo 400:
int _default_speed = 150; 

void setup() {
  // Setup sensori di linea:
//  pinMode(A0, INPUT);
//  pinMode(A1, INPUT);
//  pinMode(A2, INPUT);
//  pinMode(A3, INPUT);
//  pinMode(A4, INPUT);
//  pinMode(A5, INPUT);
  
  // Setup led:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_STATUS_1, OUTPUT);
  pinMode(LED_STATUS_2, OUTPUT);
  
  // Setup pulsanti:
  pinMode(PUSH_BUTTON_START, INPUT);
  pinMode(PUSH_BUTTON_STOP, INPUT);
  
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

  // Init Serial
  Serial.begin(9600);
  while (!Serial);


  digitalWrite(LED_STATUS_1, HIGH);
  digitalWrite(LED_STATUS_2, HIGH);
  
  for (int i = 0; i < 250; i++) {  // make the calibration take about 10 seconds
  
    qtra.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
    delay(20);
  }
  
  digitalWrite(LED_STATUS_1, LOW);
  digitalWrite(LED_STATUS_2, LOW);
  
  delay(2000);
}

int lastError = 0;
int ledWaitStatus = 1; // a 1 led lampeggiano in attesa dello start.

void loop() {

  if(ledWaitStatus == 0) {
    unsigned int sensors[NUM_SENSORS];
    int position = qtra.readLine(sensors);
    int error = position - 2500;
    int motorSpeed = Kp * error + Kd * (error - lastError);
    lastError = error;
  
    int rightMotorSpeed = rightBaseSpeed + motorSpeed;
    int leftMotorSpeed  = leftBaseSpeed  - motorSpeed;
    
    if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
    if (leftMotorSpeed > leftMaxSpeed )   leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  
    if (rightMotorSpeed < 0)              rightMotorSpeed = 0; // keep the motor speed positive
    if (leftMotorSpeed < 0)               leftMotorSpeed = 0; // keep the motor speed positive
  
    setSpeeds(leftMotorSpeed, rightMotorSpeed);
  }
  
  // Verfifica se è premuto il pulsante di Start
  if(digitalRead(PUSH_BUTTON_START) == HIGH) {
    ledWaitStatus = 0;
  }
  // Verfifica se è premuto il pulsante di Stop
  if(digitalRead(PUSH_BUTTON_STOP) == HIGH) {
    motor_stop();
    ledWaitStatus = 1;
  }

  if (ledWaitStatus == 1) {
    digitalWrite(LED_STATUS_1, HIGH);
    digitalWrite(LED_STATUS_2, HIGH);
    delay(500);
    digitalWrite(LED_STATUS_1, LOW);
    digitalWrite(LED_STATUS_2, LOW);
    delay(500);
  }
}

void blinkLeds(int _status) {
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
    
  analogWrite(motor_left[1], speed * 51 / 80); // default to using analogWrite, mapping 400 to 255

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
    
  analogWrite(motor_right[1], speed * 51 / 80); // default to using analogWrite, mapping 400 to 255

  if (reverse)
    digitalWrite(motor_right[0], HIGH);
  else
    digitalWrite(motor_right[0], LOW);
}

