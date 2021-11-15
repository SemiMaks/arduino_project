/*char inChar;*/

int trigPin = 10;
int echoPin = 11;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);
}

void loop() {
  int duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(13, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;

  Serial.print(distance);
  Serial.println(" cm");
  delay(100)
}
