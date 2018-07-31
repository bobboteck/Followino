/******
 * Followino Sensor Test
*/

void setup() 
{
  // Digital output
  pinMode(LED_BUILTIN, OUTPUT);
  // Analog INPUT
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Serial.begin(9600);

  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  int S0 = analogRead(A0);
  digitalWrite(LED_BUILTIN, LOW);
  int S1 = analogRead(A1);
  digitalWrite(LED_BUILTIN, HIGH);
  int S2 = analogRead(A2);
  digitalWrite(LED_BUILTIN, LOW);
  int S3 = analogRead(A3);
  digitalWrite(LED_BUILTIN, LOW);
  int S4 = analogRead(A4);
  digitalWrite(LED_BUILTIN, LOW);
  int S5 = analogRead(A5);
  digitalWrite(LED_BUILTIN, LOW);


  Serial.print("S0: ");
  Serial.print(S0, DEC);
  Serial.println("");

  Serial.print("S1: ");
  Serial.print(S1, DEC);
  Serial.println("");

  Serial.print("S2: ");
  Serial.print(S2, DEC);
  Serial.println("");

  Serial.print("S3: ");
  Serial.print(S3, DEC);
  Serial.println("");

  Serial.print("S4: ");
  Serial.print(S4, DEC);
  Serial.println("");

  Serial.print("S5: ");
  Serial.print(S5, DEC);
  Serial.println("");

  delay(500);
  Serial.println("-------");
}
