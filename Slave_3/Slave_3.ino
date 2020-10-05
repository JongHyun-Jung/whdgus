#include <Wire.h>
#include <Servo.h>
#define Slave_3 3
byte rec[128];
byte a[6];
byte b[6];

const int dirPin = 2;
const int stepPin = 3;
int c = 0;
int d = 0;
int e = 0;
int servoPin = 9;
int start_angle = 65 ;
int dd = 0;
Servo servo;


void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Wire.begin(Slave_3);  
  servo.attach(servoPin);
  servo.write(start_angle);
  Serial.begin(9600);
}

void loop()
{
      int condition = 1;
      Wire.onReceive(record);
      Serial.println(rec[0]);
      Serial.println(rec[1]);
      Serial.println(rec[2]);
      Serial.println(rec[3]);
      Serial.println(rec[4]);
      Serial.println(rec[5]);
      stepmotor(rec[3], rec[5]); //층(rec[3]과 호수(rec[5])를 입력값으로 사용하여 함수 사용
      Wire.onReceive(record);
      delay(500);
      if(rec[5]>=1)
      {
        while(condition) //Slave_1에서 다른 입력값을 받기 전까지, while문 안에 코드를 가둬놓는다.
        {
          for(int i = 0; i <= 5; i++)
          {
            a[i] = rec[i];
          }
          Wire.onReceive(record);
          Serial.print("확인 : ");
          Serial.print(a[2]);
          Serial.print(a[3]);
          Serial.print(a[5]);
          if(rec[0] != a[0] || rec[1] != a[1] || rec[2] != a[2] || rec[3] != a[3] || rec[4] != a[4] || rec[5] != a[5])//새로운 입력값을 받았을 때, while문을 빠져나온다.
            {
              condition = false;
            }
        }
      }
  
}
void record(int receiveNum)
{
  for(int i = 0; i<receiveNum; i++)
  {
  rec[i] = Wire.read();
  }
}
void stepmotor(int a, int b) //a는 층, b는 호수를 나타낸다. ex) 4층 1호
{
  if(a==1)
  {
    digitalWrite(dirPin, HIGH);
    for(int x=0; x<500 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
    delay(4000);
    if(b==1) //물건을 1호로 안착시켜야 할 때
    {
      servo.write(start_angle+30);
      delay(5000);
      servo.write(start_angle);
    }

    else if(b==2)//물건을 2호로 안착시켜야 할 때
    {
      servo.write(start_angle-30);
      delay(5000);
      servo.write(start_angle);
    }
    delay(4000);
    digitalWrite(dirPin, LOW);
     for(int x=0; x<500 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
    delay(4000);
  }

  else if(a==2)
  {
    digitalWrite(dirPin, HIGH);
    for(int x=0; x<1000 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
    delay(4000);
    if(b==1)
    {
         
      servo.write(start_angle+30);
      delay(5000);
      servo.write(start_angle);
    }

    else if(b==2)
    {
      servo.write(start_angle-30);
      delay(5000);
      servo.write(start_angle);
    }
    delay(4000);
     digitalWrite(dirPin, LOW);
    for(int x=0; x<1000 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
  }

  else if(a==3)
  {
    digitalWrite(dirPin, HIGH);
    for(int x=0; x<1500 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
    delay(4000);
    if(b==1)
    {
      servo.write(start_angle+30);
      delay(5000);
      servo.write(start_angle);
    }

    else if(b==2)
    {
      servo.write(start_angle-30);
      delay(5000);
      servo.write(start_angle);
    }
    delay(4000);
    digitalWrite(dirPin, LOW);
    for(int x=0; x<1500 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
  }

  else if(a==4)
  {
    digitalWrite(dirPin, HIGH);
    for(int x=0; x<2000 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
    delay(4000);
    if(b==1)
    {
      servo.write(start_angle+30);
      delay(5000);
      servo.write(start_angle);
    }

    else if(b==2)
    {
      servo.write(start_angle-30);
      delay(5000);
      servo.write(start_angle);
    }
    delay(4000);
    digitalWrite(dirPin, LOW);
    for(int x=0; x<2000 ; x++)
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
    }
  }
}
