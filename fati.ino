#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX)
SoftwareSerial BTSerial(2, 3); 

int tilt_val=0;
int infrared_val=0;
int buzzer_val=0;
int ble_val=0;
int count=0;

int buzzer_count = 0;
unsigned int timer_old = 0;
unsigned int timer_new = 0;
unsigned int timer_step = 0;
unsigned int timer_total = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(7,OUTPUT);  //  부저의 output
  pinMode(5,INPUT); //  기울기 센서 input
  pinMode(12,INPUT); //  적외선 센서 input
//  pinMode(10, OUTPUT);  
}

void loop() {
  tilt_val = digitalRead(5);
  
  if (tilt_val == HIGH){ //  labtop opened
    infrared_val = digitalRead(12);  //  적외선 : 12
  }
  else{
    infrared_val = LOW;
  }
   
  if (infrared_val == HIGH){
    timer_old = timer_new;
    timer_new = millis();
    timer_step = timer_new - timer_old;
    timer_total += timer_step;
    Serial.println(timer_total);
    delay(10);
  }
  else{
    timer_new = millis();
    timer_total = 0;
  }

  if(timer_total > 10000){
     digitalWrite(7,HIGH);
     BTSerial.println("ON");
  }
}
