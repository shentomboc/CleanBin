#include <Servo.h>
#define SERsensor 6
#define SERsensor2 7
Servo servo;
Servo servo2;

int IRsensor = 4;
int INsensor = 5;
int RDMsensor = A0;

int INvalue, CAPvalue, IRvalue, RDMvalue;

void setup() {
  // put your setup code here, to run once:
  pinMode(IRsensor, INPUT);
  pinMode(INsensor, INPUT);
  servo.attach(SERsensor);
  servo2.attach(SERsensor2);
  Serial.begin(9600);
}

void spinflip (String category, int b, String sen){
  Serial.println(category);
  servo.write(135);
  delay(2000);
  servo.write(90);
  delay(300);
  Serial.println(sen);
  servo2.write(b);
  delay(2000);
}

void servoreset (){
  servo.write(90);
  servo2.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  int IRvalue = digitalRead(IRsensor);
  int INvalue = digitalRead(INsensor);
  int RDMvalue = analogRead(RDMsensor);
  int RDMoutput = map (RDMvalue, 0, 1023, 255,0);
  servoreset();
  
  if (IRvalue == LOW){
    Serial.println("In");
    delay (2000);
    if (INvalue == LOW){ 
      Serial.println(INvalue);   
      spinflip("Dry", 45, "Metal");
    }
    else {
      if (RDMoutput <= 50){
        spinflip("Dry", 45, "Dry Waste");
      }
      else {
        spinflip("Wet", 135, "Wet Waste");
      }
    }
  }
  else {
    servoreset();
  }
  delay (100); 
}