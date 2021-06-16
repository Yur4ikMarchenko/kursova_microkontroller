#define BLUE_LED 10
#define PIN_PHOTO_SENSOR A0
#define PIN_TRIG 12
#define PIN_ECHO 11
#define GREEN_LED 8
#define YELLOW_LED 9
#define RED_LED 7
#define SPIKER 6
#define PIN_PIR 13
#define PIN_LAMP 4

long duration, cm;


void setup() 
{
  Serial.begin(9600); //ініціалізую взяаємодію по послідовному порту зі швидкістю 9600
  //
  pinMode(BLUE_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);			//визначаю входи та виходи
  pinMode(SPIKER, OUTPUT);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_LAMP, OUTPUT);
}

void loop() 
{
  int pirVal = digitalRead(PIN_PIR);
  Serial.println(digitalRead(PIN_PIR));

  //якщо э рух світиться лампочка, якщо руху немає то не світить
  if (pirVal)
  {
    digitalWrite(PIN_LAMP, HIGH);
    Serial.println("Motion detected");
    delay(5000);
  }
  else
  {
    Serial.print("No motion");
    digitalWrite(PIN_LAMP, LOW);
  }
  
  //спочатку генерую короткий імпульс в 5 мікросекунд
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  
  //датчик посилає сигнали з частотою 40КГц
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  //затримка сигналу
  duration = pulseIn(PIN_ECHO, HIGH);
  
  //перетворення часу в відстань
  cm = (duration / 2) / 29.1;
  
  //вивід відстані на ПК
  Serial.print("Vidstan do object: ");
  Serial.print(cm);
  Serial.println(" cm");
  
  //допустима відстань (світиться зелений індикатор)
  if (cm < 280 && cm > 140)
  {
    digitalWrite(SPIKER, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  //також допустима відстань, але потрібно зменшити швидкість (світиться жовтий індикатор)
  if (cm < 140 && cm > 90)
  {
    digitalWrite(SPIKER, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
  //відстать для зупинки (червоний індикатор та звукове попередження)
  if (cm < 90 && cm > 0)
  {
    digitalWrite(SPIKER, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    delay(5000);
  }
  
  //зміна для отримання степеню освітленості
  int val = analogRead(PIN_PHOTO_SENSOR);
  
  //вивід степеню на ПК
  Serial.print("Osvitlenist: ");
  Serial.println(val);
  
  //коли степінь освітленості більший за 90, тобто на вулиці світло, індикатор не світиться 
  if (val < 90) 
  {
    digitalWrite(BLUE_LED, LOW);
  } 
  //коли степінь освітленості менший за 90, тобто на вулиці пасмурно, індикатор світиться
  else 
  {
    digitalWrite(BLUE_LED, HIGH);
  }
}