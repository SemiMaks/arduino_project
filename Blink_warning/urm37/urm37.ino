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

float calibre = 0;
float DistM = 0;
float u_av = 0;
float LLT;
int trig = 0;

void setup()
{
  Serial.begin(9600);                        // установка скорости порта 9600
  pinMode(URTRIG, OUTPUT);                   // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH);                // Set to HIGH
  pinMode(URECHO, INPUT);                    // Sending Enable PWM mode command
  Serial.println("Инициализация сенсора выполнена.");
  Serial.println("- - - - - - - - - - - - - - - - ");
  delay(500);
}

void loop() {
  if (trig == 0) {
    Serial.print("Начальное значение тригера: ");
    Serial.println(trig);
    testMm();
    Serial.print("Текущее состояние тригера: ");
    Serial.println(trig);
    }
  
  else if (trig == 1) {
    getMm();    
    Serial.print("Текущее состояние тригера: ");
    Serial.println(trig); 
  }

  else if (trig == 2) {
    
    Serial.print("Текущее состояние тригера: ");
    Serial.println(trig);
    Serial.println("Сброс тригера....");
    resMm();
    Serial.println("===================");
  }
  delay(3000);
}

float testMm() {
  Serial.println("Выполняется калибровка...");

  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  LLT = pulseIn(URECHO, LOW);
  float cb1 = LLT;
  delay(40);

  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  LLT = pulseIn(URECHO, LOW);
  float cb2 = LLT;
  delay(40);

  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  LLT = pulseIn(URECHO, LOW);
  float cb3 = LLT;

  calibre = (cb1 + cb2 + cb3) / 3;
  
  Serial.print("Калибровка - ");
  Serial.print(calibre);
  Serial.println(" мс");  
  
  DistM = calibre * ex;
  Serial.print("...в сантиметрах - ");
  Serial.print(DistM);
  Serial.println(" см");
  delay(2000);
  
  trig = 1;
  return trig, calibre;
}

float getMm() {
  Serial.println("Производится замер...");  
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  LLT = pulseIn(URECHO, LOW);
  float dis1 = LLT;
  delay(40);

  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  LLT = pulseIn(URECHO, LOW);
  float dis2 = LLT;
  delay(40);

  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  LLT = pulseIn(URECHO, LOW);
  float dis3 = LLT;

  u_av = (dis1 + dis2 + dis3) / 3;
  Serial.print("Среднее значение - ");
  Serial.print(u_av);
  Serial.println(" мс");

  float h = calibre - u_av;
  float height = (calibre - h) * ex;
  Serial.print("Рост - ");
  Serial.print(height);
  Serial.println(" см");
  
  trig = 2;
  delay(2000);
  return trig;
}

float resMm() {  
    trig = 0;
    return trig;
    delay(5000);
}
