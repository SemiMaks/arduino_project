char inChar;
 
#define HC_TRIG 2
#define HC_ECHO 3
#define HC_LED 13

int trig = 0;
int u_av = 0;

void setup() {
  Serial.begin(115200);       // для связи
  pinMode(HC_TRIG, OUTPUT);   // trig выход
  pinMode(HC_ECHO, INPUT);    // echo вход
  pinMode(HC_LED, OUTPUT);    // для диода на плате
}

void loop() {
  float t = 24;           // представим, что получили с датчика 24гр 
  delay(1000);
  if (Serial.available() > 0) 
  {
    inChar = Serial.read();
    if (inChar=='k' or 'K')
    {
      testMm(t);
    }
  }
    else if (inChar=='s' or 'S')
    {
      getMm(t);
      Serial.print("Рост составляет: ");
      Serial.print(u_av);
      Serial.println(" мм");
    }
  }

// функция для изммерения
float getMm(float t) {
  digitalWrite(HC_TRIG, HIGH);
  digitalWrite(HC_LED, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_LED, LOW);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us1 = pulseIn(HC_ECHO, HIGH);
  us1 = us1 * (t * 6 / 10 + 330) / 2000ul;
  digitalWrite(HC_TRIG, HIGH);
  digitalWrite(HC_LED, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_LED, LOW);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us2 = pulseIn(HC_ECHO, HIGH);
  us2 = us2 * (t * 6 / 10 + 330) / 2000ul;
  digitalWrite(HC_TRIG, HIGH);
  digitalWrite(HC_LED, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_LED, LOW);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us3 = pulseIn(HC_ECHO, HIGH);
  us3 = us3 * (t * 6 / 10 + 330) / 2000ul;
  u_av = (us1 + us2 + us3) / 3;
  return u_av;
}

// функция для калибровки
float testMm(float t) {
  // импульс 40 мкс
  digitalWrite(HC_TRIG, HIGH);
  digitalWrite(HC_LED, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_LED, LOW);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us1 = pulseIn(HC_ECHO, HIGH);
  us1 = us1 * (t * 6 / 10 + 330) / 2000ul;
  Serial.println("Запуск калибровки (мм): ");
  Serial.print("проход 1: ");
  Serial.println(us1);

  digitalWrite(HC_TRIG, HIGH);
  digitalWrite(HC_LED, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_LED, LOW);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us2 = pulseIn(HC_ECHO, HIGH);
  us2 = us2 * (t * 6 / 10 + 330) / 2000ul;
  Serial.print("проход 2: ");
  Serial.println(us2);

  digitalWrite(HC_TRIG, HIGH);
  digitalWrite(HC_LED, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_LED, LOW);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us3 = pulseIn(HC_ECHO, HIGH);
  us3 = us3 * (t * 6 / 10 + 330) / 2000ul;
  Serial.print("проход 3: ");
  Serial.println(us3);
  
  Serial.print("Среднее значение (мм): ");
  u_av = (us1 + us2 + us3) / 3;
  Serial.println(u_av);
  return u_av;
}
