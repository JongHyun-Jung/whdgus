#include <Wire.h>
#include <Servo.h>
#define Slave 1
#define Slave_2 2
#define Slave_3 3
byte rec[128];
byte a[6];
byte b[6];

int servoPin_1 = 8;
int servoPin_2 = 9;

Servo servo;
Servo servo_2;

void setup()
{
  Serial.begin(9600);
  Wire.begin(Slave);
  servo.attach(servoPin_1);
  servo_2.attach(servoPin_2);
  servo.writeMicroseconds(1000);
  servo_2.writeMicroseconds(1000);
  servo.write(90);
  servo_2.write(90);
}

void loop() 
{
  int condition = 1;
  Wire.onReceive(record);

  if(rec[2] == 1)//101동일 경우
  {
    for(int i = 0; i <= 5; i++)
      {
        a[i] = rec[i];
      }
    servo_2.write(90); //102동과 연결된 컨베이어벨트는 정지상태에 머물게 한다.
    servo.write(0); //101동과 연결된 컨베이어벨트를 움직이게 한다.
    delay(10000);
    servo.write(90); 
    delay(1000);
    Wire.beginTransmission(Slave_2); //컨베이어벨트의 작동이 끝난 후, Slave_2(101동과 연결된 보드)에 입력값을 송신한다.
    for(int i = 0; i <= 5; i++)
    {
      Wire.write(a[i]);
    }
    Wire.endTransmission();
    while(condition) // Master에서 다른 입력값을 받기 전까지, while문 안에 코드를 가둬놓는다. 
    {
      for(int i = 0; i <= 5; i++)
      {
        b[i] = rec[i];
      }
      Wire.onReceive(record);
      if(rec[0] != b[0] || rec[1] != b[1] || rec[2] != b[2] || rec[3] != b[3] || rec[4] != b[4] || rec[5] != b[5]) //새로운 입력값을 받았을 때, while문을 빠져나온다.
      {
        condition = false;
      }
    }
  }

  if(rec[2] == 2)//102동일 경우
  {
    for(int i = 0; i <= 5; i++)
      {
        a[i] = rec[i];
      }
    servo_2.write(180);
    servo.write(90);
    delay(10000);
    servo_2.write(90);
    delay(1000);
    Wire.beginTransmission(Slave_3);
    for(int i = 0; i <= 5; i++)
    {
      Wire.write(a[i]);
    }
    Wire.endTransmission();
    while(condition)
    {
      for(int i = 0; i <= 5; i++)
      {
        b[i] = rec[i];
      }
      Wire.onReceive(record);
      if(rec[0] != b[0] || rec[1] != b[1] || rec[2] != b[2] || rec[3] != b[3] || rec[4] != b[4] || rec[5] != b[5])
      {
        condition = false;
      }
    }
  }
}

void record(int receiveNum) // 통신으로 받는 숫자를 차례대로 rec[0],rec[1],rec[2],rec[3],rec[4],rec[5]에 저장한다.
{
  for(int i = 0; i < receiveNum; i++)
  {
    rec[i] =  Wire.read();
  }
}
