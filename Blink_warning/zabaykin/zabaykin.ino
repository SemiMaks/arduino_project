#include "Ultrasonic.h"
 
Ultrasonic us_4(8, 9); // Trig - first, Echo - second
Ultrasonic us_3(6, 7);
Ultrasonic us_2(4, 5);
Ultrasonic us_1(2, 3);
 
void setup()
{
  Serial.begin(9600);           // start the serial port
}
 
void loop()
{
  float d_1 = us_1.Ranging(CM);     // get distance
  float d_2 = us_2.Ranging(CM);     // get distance
  float d_3 = us_3.Ranging(CM);     // get distance
  float d_4 = us_4.Ranging(CM);     // get distance
  Serial.print(d_1);
  Serial.print("cm, ");
  Serial.print(d_2);
  Serial.print("cm, ");
  Serial.print(d_3);
  Serial.print("cm, ");
  Serial.print(d_4);
  Serial.println("cm.");        // print the distance
   
  delay(500);                               // arbitrary wait time.
}
