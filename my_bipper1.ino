const int speakerPin = 6;   // Пін, на який підключено динамік (пищалку)
const int receiverPin = 11; // Пін, на який підключений приймач

const int signalDuration = 1000; // Тривалість сигналу в мілісекундах

const int filterFrequency = 27;  // Частота фільтра (27 Гц)
 unsigned long milis = 0;
const unsigned long filterPeriod = 41000;  // Період фільтрації (в мікросекундах)

 int count = 0;  // Період фільтрації (в мікросекундах)


void setup()
{
  pinMode(speakerPin, OUTPUT);
  pinMode(receiverPin, INPUT);
  digitalWrite(receiverPin, HIGH); // Встановлення високого рівня сигналу на піні приймача

  Serial.begin(9600); // Ініціалізація з'єднання з серійним портом
}

void loop()
{
 
  if (micros()-milis > 1500000) {
    milis = micros();
    count = 0;
  }
  unsigned long pulseStart = 0;
  unsigned long pulseEnd = 0;

  // Зчитати початковий час пульсу
  while (digitalRead(receiverPin) == LOW) {
    pulseStart = micros();
  }

  // Зчитати кінцевий час пульсу
  while (digitalRead(receiverPin) == HIGH) {
    pulseEnd = micros();
  }

  unsigned long pulseDuration = pulseEnd - pulseStart;    // Обчислити тривалість пульсу
  //Serial.println(pulseDuration);                         // Вивести тривалість пульсу на Serial Monitor

  if (pulseDuration > filterPeriod - 7000 && pulseDuration < filterPeriod + 7000) // Перевірити частоту пульсу
  {
    count++;
  }  
 // Serial.println(micros()-milis);                         // Вивести тривалість пульсу на Serial Monitor

  if(count>1)
  {
    tone(speakerPin, 1000);      // Увімкнути звуковий сигнал на пищалці
    delay(300);       // Затримка для тривалості сигналу
    noTone(speakerPin);          // Вимкнути звуковий сигнал
    delay(6000);                  // Затримка між сигналами
    count=0;    
    //Serial.println("Отримано сигнал"); // Вивести повідомлення на серійний монітор
  }
}
