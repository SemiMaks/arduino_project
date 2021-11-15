//  Connection:
//  Vcc (Arduino)    ->   Pin 1 VCC (URM V5.0)
//  GND (Arduino)    ->   Pin 2 GND (URM V5.0)
//  Pin 3 (Arduino)  ->   Pin 4 ECHO-1 (URM V5.0)
//  Pin 5 (Arduino)  ->   Pin 6 COMP/TRIG-1 (URM V5.0)
//  Pin 9 (Arduino)  ->   Pin 4 ECHO-2 (URM V5.0)
//  Pin 10 (Arduino)  ->   Pin 6 COMP/TRIG-2 (URM V5.0)

float URECHO_1 = 3;         //  0-50000 мс каждые 50US represent 1cm
float URTRIG_1 = 5;         // trigger pin
float URECHO_2 = 9;         // PWM Output 0-50000US,Every 50US represent 1cm
float URTRIG_2 = 10;

float ex = 0.02;          // 1/50

float calibre_1 = 0;
float calibre_2 = 0;
float DistM_1 = 0;
float DistM_2 = 0;
float u_av_1 = 0;
float u_av_2 = 0;
float LLT_1 = 0;
float LLT_2 = 0;
int trig = 0;


void setup()
{
  Serial.begin(9600);                        // установка скорости порта 9600
  pinMode(URTRIG_1, OUTPUT);                   // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG_1, HIGH);                // Set to HIGH
  pinMode(URECHO_1, INPUT);                    // Sending Enable PWM mode command
  delay(10);
  pinMode(URTRIG_2, OUTPUT);
  digitalWrite(URTRIG_2, HIGH);
  pinMode(URECHO_2, INPUT);
  Serial.println("Инициализация сенсора выполнена.");
  Serial.println("- - - - - - - - - - - - - - - - ");
  delay(200);
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
    Serial.println("=============================");
  }
  delay(3000);
}

float testMm() {
  Serial.println("Выполняется калибровка сенсоров 1 и 2 ...");

  digitalWrite(URTRIG_1, LOW);  
  digitalWrite(URTRIG_1, HIGH);  
  LLT_1 = pulseIn(URECHO_1, LOW);  
  float cb11 = LLT_1;
  delay(40);

  digitalWrite(URTRIG_2, LOW);
  digitalWrite(URTRIG_2, HIGH);
  LLT_2 = pulseIn(URECHO_2, LOW);
  float cb21 = LLT_2;
  delay(40);

  digitalWrite(URTRIG_1, LOW);
  digitalWrite(URTRIG_1, HIGH);
  LLT_1 = pulseIn(URECHO_1, LOW);
  float cb12 = LLT_1;
  delay(40);
  
  digitalWrite(URTRIG_2, LOW);  
  digitalWrite(URTRIG_2, HIGH);
  LLT_2 = pulseIn(URECHO_2, LOW);
  float cb22 = LLT_2;
  delay(40);

  digitalWrite(URTRIG_1, LOW);  
  digitalWrite(URTRIG_1, HIGH);  
  LLT_1 = pulseIn(URECHO_1, LOW);  
  float cb13 = LLT_1;
  delay(40);

  digitalWrite(URTRIG_2, LOW);
  digitalWrite(URTRIG_2, HIGH);
  LLT_2 = pulseIn(URECHO_2, LOW);
  float cb23 = LLT_2;
  
  calibre_1 = (cb11 + cb12 + cb13) / 3;
  calibre_2 = (cb21 + cb22 + cb23) / 3;
  
  Serial.print("Калибровка сенсора 1- ");
  Serial.print(calibre_1);
  Serial.println(" мс");

  Serial.print("Калибровка сенсора 2- ");
  Serial.print(calibre_2);
  Serial.println(" мс");
  
  DistM_1 = calibre_1 * ex;
  Serial.print("...в сантиметрах 1 сенсор - ");
  Serial.print(DistM_1);
  Serial.println(" см");

  DistM_2 = calibre_2 * ex;
  Serial.print("...в сантиметрах 2 сенсор- ");
  Serial.print(DistM_2);
  Serial.println(" см");
  
  trig = 1;
  
  return trig, calibre_1, calibre_2;
  delay(100);
}

float getMm() {
  Serial.println("Производится замер...");  
  digitalWrite(URTRIG_1, LOW);
  digitalWrite(URTRIG_1, HIGH);
  float LLT_11 = pulseIn(URECHO_1, LOW);
  float dis11 = LLT_11;
  delay(40);
  
  digitalWrite(URTRIG_2, LOW);
  digitalWrite(URTRIG_2, HIGH);
  float LLT_21 = pulseIn(URECHO_2, LOW);
  float dis21 = LLT_21;
  delay(40);

  digitalWrite(URTRIG_1, LOW);
  digitalWrite(URTRIG_1, HIGH);
  float LLT_12 = pulseIn(URECHO_1, LOW);
  float dis12 = LLT_12;
  delay(40);
  
  digitalWrite(URTRIG_2, LOW);
  digitalWrite(URTRIG_2, HIGH);
  float LLT_22 = pulseIn(URECHO_2, LOW);
  float dis22 = LLT_22;
  delay(40);

  digitalWrite(URTRIG_1, LOW);
  digitalWrite(URTRIG_1, HIGH);
  float LLT_13 = pulseIn(URECHO_1, LOW);
  float dis13 = LLT_13;
  delay(40);

  digitalWrite(URTRIG_2, LOW);
  digitalWrite(URTRIG_2, HIGH);
  float LLT_23 = pulseIn(URECHO_2, LOW);
  float dis23 = LLT_23;

  u_av_1 = (dis11 + dis12 + dis13) / 3;
  u_av_2 = (dis21 + dis22 + dis23) / 3;
  Serial.print("Среднее значение сенсора 1 - ");
  Serial.print(u_av_1);
  Serial.println(" мс");

  Serial.print("Среднее значение сенсора 2 - ");
  Serial.print(u_av_2);
  Serial.println(" мс");

  float h_1 = calibre_1 - u_av_1;
  float height_1 = (calibre_1 - h_1) * ex;
  float h_2 = calibre_2 - u_av_2;
  float height_2 = (calibre_2 - h_2) * ex;

  int n =  height_1 - height_2;
  if (n <= 1) {
    float height = (height_1 + height_2) / 2;
    Serial.print("Рост - ");
    Serial.print(height);
    Serial.println(" см");
  }
  else {
    Serial.println("Значения обоих сенсоров отличается более чем на 1 см");
  }
    
  trig = 2;
  delay(500);
  return trig;
}

float resMm() {  
    trig = 0;
    return trig;
    delay(3000);
}
