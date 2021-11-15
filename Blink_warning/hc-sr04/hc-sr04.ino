char inChar;

int trigPin = 10; 
int echoPin = 11;  
 
void setup() { 
  Serial.begin (115200); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
} 
 
void loop() { 
  int duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  digitalWrite(13, HIGH);
  Serial.println("Шлём импульс");
  delayMicroseconds(10);
  Serial.println("Отключаем импульс, производим замер"); 
  digitalWrite(trigPin, LOW);
  digitalWrite(13, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = duration / 58;
  Serial.print(distance); 
  Serial.println(" cm"); 
  delay(10000);
}
