// пины Arduino
#define HC_TRIG 2
#define HC_ECHO 3

int trig = 0;
int u_av = 0;

void setup() {
  Serial.begin(9600);       // для связи
  pinMode(HC_TRIG, OUTPUT);   // trig выход
  pinMode(HC_ECHO, INPUT);    // echo вход
}

void loop() {
  float t = 24;           // представим, что получили с датчика 24гр
  if (trig == 0) {
    Serial.println("Выполняется калибровка: ");
    float test = testMm(t); // калибровка
    trig = 1;
  }

  if(trig == 1) {
    Serial.println("-----------------------");
    Serial.print("Среднее значение при калибровке: ");
    Serial.print(u_av);
    Serial.println(" мм");
    Serial.print("Рост составляет: ");
    float dist = getMm(t);  // получаем расстояние в мм
    float h_p = u_av -dist;
    int height = u_av - h_p;
    Serial.print(height);
    Serial.println(" мм");
    Serial.print("Текущее состояние тригера: ");
    Serial.println(trig);
    delay(2000);
  }
}
// сделаем функцию для удобства
float getMm(float t) {
  // импульс 40 мкс
  delayMicroseconds(40);
  digitalWrite(HC_TRIG, LOW);
  // измеряем время ответного импульса
  uint32_t us = pulseIn(HC_ECHO, HIGH);
  // считаем расстояние и возвращаем
  return (us * (t * 6 / 10 + 330) / 2000ul);
}

// функция для калибровки
float testMm(float t) {
  // импульс 40 мкс
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_TRIG, LOW);
  // измеряем время ответного импульса
  uint32_t us1 = pulseIn(HC_ECHO, HIGH);
  us1 = us1 * (t * 6 / 10 + 330) / 2000ul;
  Serial.print("проход 1: ");
  Serial.println(us1);

  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us2 = pulseIn(HC_ECHO, HIGH);
  us2 = us2 * (t * 6 / 10 + 330) / 2000ul;
  Serial.print("проход 2: ");
  Serial.println(us2);

  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(40);
  digitalWrite(HC_TRIG, LOW);
  uint32_t us3 = pulseIn(HC_ECHO, HIGH);
  us3 = us3 * (t * 6 / 10 + 330) / 2000ul;
  Serial.print("проход 3: ");
  Serial.println(us3);
  
  Serial.print("Среднее значение теста (мм): ");
  u_av = (us1 + us2 + us3) / 3;
  Serial.println(u_av);
  return u_av;
}
