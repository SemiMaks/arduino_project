char inChar;

void setup() {
  pinMode(13, OUTPUT); // Инициализация светодиода
  Serial.begin(115200); // Инициализация Serial - порта
}

void loop() {
  if (Serial.available() > 0)
  {
    inChar = Serial.read();
    if (inChar=='e') // e - Enable - включить
    {
      Serial.println("Светодиод включен.");
      digitalWrite(13,HIGH);
    }
  }
  
    else if (inChar=='d') // d - Disable - выключить
    {
      Serial.println("Светодиод выключен.");
      digitalWrite(13,LOW);
    }
  
    else if (inChar=='b')  // b - Blink - выключить режим мигания
    {
      while (true){
      Serial.println("Светодиод дважды мигает.");
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      delay(1000);
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      delay(1000);
      break;
      
    }
    }
}
