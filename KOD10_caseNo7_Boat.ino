#define IK 2
#define SPEED 3
// пин выбора направления движения мотора
#define DIR A5
int ik = 1;
 
void setup() {
  pinMode(IK, INPUT);
  pinMode(DIR, OUTPUT); 
  pinMode(SPEED, OUTPUT); 
 
  Serial.begin(9600);

}

void loop() {
  digitalWrite(DIR, HIGH);
  digitalWrite(SPEED, 1);
  Serial.println("назад");
  ik = digitalRead(IK);
  while(ik == 1){
    ik = digitalRead(IK);
    delay(10);
    //Serial.println(ik);
  }
  digitalWrite(DIR, LOW);
  digitalWrite(SPEED, 10);
  Serial.println("плывем вперед");//проверили боновую защиту
  delay(10000);
  digitalWrite(DIR, HIGH);
  digitalWrite(SPEED, 10);
  Serial.println("назад");
  delay(10000);
  ik = digitalRead(IK);
  delay(10);
  while(ik == 1){//сдаем назад до окончания работы помп
    ik = digitalRead(IK);
    delay(10);
    Serial.println(ik);
  }
  digitalWrite(DIR, LOW);
  digitalWrite(SPEED, 10);
  delay(10);

  ik = digitalRead(IK);//
  delay(10);
  while(ik == 1){
    ik = digitalRead(IK);
    delay(10);
    Serial.println(ik);
  }
  digitalWrite(DIR, LOW);
  digitalWrite(SPEED, 10);
  delay(10);

  ik = digitalRead(IK);
  delay(10);
  while(ik == 1){//сдаем назад до окончания работы помп
    ik = digitalRead(IK);
    delay(10);
    Serial.println(ik);
  }
}
