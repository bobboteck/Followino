/*
  LineSensors.h - Library for manage the Line Sensors of Followino.
  Created by Roberto D'Amico - Mauro Esposito, January 4, 2019.
  Released into the MIT Licence.
*/
#ifndef LineSensors_h
#define LineSensors_h

#include "Arduino.h"

class LineSensors
{
  public:
    LineSensors(int numberOfSample);
    
    int ReadSensors();
    int ReadSensor(int sensor);

    
  private:
    int _numberOfSample;
};

#endif