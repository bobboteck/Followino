#include "src/LineSensors/LineSensors.h"

LineSensors Sensors(4);

void setup()
{
  // Init Serial
  Serial.begin(9600);
  while (!Serial);

}

void loop()
{
  Serial.println(Sensors.ReadSensor(A0));
  //Delay(1000);
}
