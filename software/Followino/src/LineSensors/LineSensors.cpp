/*
  LineSensors.cpp - Library for manage the Line Sensors of Followino.
  Created by Roberto D'Amico - Mauro Esposito, January 4, 2019.
  Released into the MIT Licence.
*/
#include "Arduino.h"
#include "LineSensors.h"

LineSensors::LineSensors(int numberOfSample)
{
  // Configure the input pin connectet to the Sensors as Analog INPUT
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  // Set e number of sample for each sensor, used in the ReadSensors function
  _numberOfSample = numberOfSample;
}

int LineSensors::ReadSensors()
{

}

int LineSensors::ReadSensor(int sensor)
{
  long sumOfReads = 0;

  for(int i=0;i<_numberOfSample;i++)
  {
    sumOfReads += analogRead(sensor);
  }

  return sumOfReads/_numberOfSample;
}