#define LED_R 9
#define LED_G 8
#define LED_I_1 12
#define LED_I_2 17
#define PORSHEN1 3
#define PORSHEN2 2
#define POMPA1 6
#define POMPA2 5
#define Motor_K 4
#define Motor_V 20
#define Motor_V_L 19
#define Water A1//Датчик уровня воды

#define TRIG_PIN_1 11
#define ECHO_PIN_1 10
#define TRIG_PIN_2 14
#define ECHO_PIN_2 15
float line, cm;
int f = 0;
int water_level;

void setup() {

  //pinMode(DIR_1, OUTPUT);
  pinMode(PORSHEN1, OUTPUT);
  pinMode(PORSHEN2, OUTPUT);
  pinMode(POMPA1, OUTPUT);
  pinMode(POMPA2, OUTPUT);
  pinMode(Motor_K, OUTPUT);
  pinMode(Motor_V, OUTPUT);
  pinMode(Motor_V_L, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_I_1, OUTPUT);
  pinMode(LED_I_2, OUTPUT);
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(Water, INPUT);
  //delay(10000);
  digitalWrite(Motor_V_L, HIGH);
  Serial.begin(9600);
}

void loop() {

  int k = digitalRead(16);
  while (k == 0){
    k = digitalRead(16);
    Serial.println(k);
  }
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);
  delay(10);
  digitalWrite(PORSHEN1, HIGH);
  delay(25000);  //выдвинули поршень1
  digitalWrite(PORSHEN2, HIGH);
  delay(50000);  //выдвинули поршень 2
  //боновая защита выдвинута

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);

  digitalWrite(LED_I_1, HIGH);
  delay(10);
  

  digitalWrite(TRIG_PIN_1, LOW);
  delay(10);
  digitalWrite(TRIG_PIN_1, HIGH);
  delay(10);
  digitalWrite(TRIG_PIN_1, LOW);
  line = pulseIn(ECHO_PIN_1, HIGH);  //замеряем длину волны в футах
  delay(10);

  while (line > 100) {  //ждем пока лодка пришвартуется
    digitalWrite(TRIG_PIN_1, LOW);
    delay(10);
    digitalWrite(TRIG_PIN_1, HIGH);
    delay(10);
    digitalWrite(TRIG_PIN_1, LOW);
    line = pulseIn(ECHO_PIN_1, HIGH);  //замеряем длину волны в футах
    delay(10);
    Serial.println(line);
  }
  digitalWrite(LED_I_1, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);
  delay(10);
  //water_level = analogRead(Water);
  while (analogRead(Water) > 250) {
    digitalWrite(POMPA1, HIGH);
    delay(10);
    Serial.println(analogRead(Water));
    if (f == 0) {
      digitalWrite(PORSHEN2, LOW);
      delay(2500);  //задвинули поршень 2
      digitalWrite(PORSHEN1, LOW);
      digitalWrite(Motor_K, HIGH);
      delay(6000);  //задвинули поршень 1
      digitalWrite(Motor_K, LOW);
      //боновая защита убрана
    }
    f = 1;
    //water_level = analogRead(Water);
    delay(10);
  }
  digitalWrite(POMPA1, LOW);
  delay(10);

  digitalWrite(Motor_V_L, LOW);
  digitalWrite(Motor_V, HIGH);
  delay(5000);
  digitalWrite(Motor_V, LOW);
  digitalWrite(Motor_V_L, HIGH);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);

  digitalWrite(LED_I_1, HIGH);
  delay(100); // лодка поплыла в нижний бьеф

 
  digitalWrite(TRIG_PIN_2, LOW);
  delay(10);
  digitalWrite(TRIG_PIN_2, HIGH);
  delay(10);
  digitalWrite(TRIG_PIN_2, LOW);
  line = pulseIn(ECHO_PIN_2, HIGH);  //замеряем длину волны в футах
  delay(10);

  while (line > 700) {  //ждем пока лодка достигнет края нижнего бьефа
    digitalWrite(TRIG_PIN_2, LOW);
    delay(10);
    digitalWrite(TRIG_PIN_2, HIGH);
    delay(10);
    digitalWrite(TRIG_PIN_2, LOW);
    line = pulseIn(ECHO_PIN_2, HIGH);  //замеряем длину волны в футах
    delay(10);
    Serial.println(line);
  }
  digitalWrite(LED_I_1, LOW); 
  digitalWrite(LED_I_2, HIGH);
  delay(100);

  digitalWrite(TRIG_PIN_1, LOW);
  delay(10);
  digitalWrite(TRIG_PIN_1, HIGH);
  delay(10);
  digitalWrite(TRIG_PIN_1, LOW);
  line = pulseIn(ECHO_PIN_1, HIGH);  //замеряем длину волны в футах
  delay(10);

  while (line > 700) {  //ждем пока лодка пришвартуется
    digitalWrite(TRIG_PIN_1, LOW);
    delay(10);
    digitalWrite(TRIG_PIN_1, HIGH);
    delay(10);
    digitalWrite(TRIG_PIN_1, LOW);
    line = pulseIn(ECHO_PIN_1, HIGH);  //замеряем длину волны в футах
    delay(10);
    Serial.println(line);
  }
  digitalWrite(LED_I_2, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);
  delay(10);

  digitalWrite(Motor_V_L, LOW);
  digitalWrite(Motor_V, LOW);
  delay(5000);
  digitalWrite(Motor_V, HIGH);
  digitalWrite(Motor_V_L, HIGH);


  while (analogRead(Water) < 250) {
    digitalWrite(POMPA2, HIGH);
    delay(10);
    if (f == 0) {
      digitalWrite(PORSHEN2, LOW);
      delay(2500);  //задвинули поршень 2
      digitalWrite(PORSHEN1, LOW);
      digitalWrite(Motor_K, HIGH);
      delay(5400);  //задвинули поршень 1
      digitalWrite(Motor_K, LOW);
      //боновая защита убрана
    }
    f = 1;
    //water_level = analogRead(Water);
    delay(10);
  }
  digitalWrite(POMPA2, LOW);
  delay(10);

  delay(30);
  Serial.println(water_level);
  delay(100000);
}
