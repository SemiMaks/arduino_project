//  Connection:
//  Vcc (Arduino)    ->   Pin 1 VCC (URM V5.0)
//  GND (Arduino)    ->   Pin 2 GND (URM V5.0)
//  Pin 3 (Arduino)  ->   Pin 4 ECHO-1 (URM V5.0)
//  Pin 5 (Arduino)  ->   Pin 6 COMP/TRIG-1 (URM V5.0)
//  Pin 9 (Arduino)  ->   Pin 4 ECHO-2 (URM V5.0)
//  Pin 10 (Arduino)  ->   Pin 6 COMP/TRIG-2 (URM V5.0)

float URECHO = 3;         // PWM Output 0-50000US,Every 50US represent 1cm
float URTRIG = 5;         // trigger pin
float ex = 0.02;          // 1/50

float DistM = 0;
float u_av = 0;
int trig = 0;

void setup()
{
  Serial.begin(9600);                        // установка скорости порта 9600
  pinMode(URTRIG, OUTPUT);                   // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH);                // Set to HIGH
  pinMode(URECHO, INPUT);                    // Sending Enable PWM mode command
  delay(500);
  Serial.println("Инициализация сенсора выполнена.");
  Serial.println("- - - - - - - - - - - - - - - - ");   
}
void loop()
{
  Serial.print("Дистанция = ");
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH); 

               

  float LLT = pulseIn(URECHO, LOW) ; // LowLevelTime
  
  if (LLT >= 50000)              // при превышении дистанции 10 м
  {
    Serial.println("Достигнут эффект бесконечности....");
  }
  else
  {
    DistM = LLT * ex;  // 1/50
    Serial.print(DistM);
    Serial.println(" см.");
  
    float ht = u_av - LLT;
    float height = u_av - ht;
    Serial.print("Рост = ");
    Serial.print(height * ex);
    Serial.println(" см");
  }

  delay(3000);
}
