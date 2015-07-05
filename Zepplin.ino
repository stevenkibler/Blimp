#include <Servo.h>

#define ID              0xef
#define LEFT_FORWARD    180
#define LEFT_BACK       0
#define RIGHT_FORWARD   0
#define RIGHT_BACK      180

uint8_t battery_pin=A0;
uint8_t right_motor=6;
uint8_t left_motor=11;
Servo left_servo;
Servo right_servo;

uint8_t voltage_cutoff=800;
uint8_t state=0;
int8_t pitch=0;
int8_t yaw=0;
uint8_t throttle=0;

void setup()
{
  Serial.begin(57600);

  pinMode(battery_pin,INPUT);
  pinMode(right_motor,OUTPUT);
  pinMode(left_motor,OUTPUT);
  analogWrite(right_motor,0);
  analogWrite(left_motor,0);

  left_servo.attach(5);
  right_servo.attach(3);
  left_servo.write(90);
  right_servo.write(90);
}

void loop()
{
  if(analogRead(battery_pin)>=voltage_cutoff)
  {
    while(Serial.available()>0)
    {
      int temp=Serial.read();
  
      if(temp!=-1)
      {
        switch(state)
        {
          case 0:
            if(temp==0xfa)
              state=1;
            break;
          case 1:
            if(temp==ID)
              state=2;
            else
              state=0;
            break;
          case 2:
            pitch=temp;
            state=3;
            break;
          case 3:
            yaw=temp;
            state=4;
            break;
          case 4:
            throttle=temp;
            state=0;
            break;
          default:
            state=0;
            break;
        }
      }
    }
  }
  else
  {
    pitch=0;
    yaw=0;
    throttle=0;
    left_servo.write(90);
    right_servo.write(90);
  }
  
  float left_value=90+(pitch/127.0)*90+(yaw/127.0)*90;
  float right_value=90+(pitch/127.0)*90-(yaw/127.0)*90;

  left_servo.write(map(left_value,LEFT_BACK,LEFT_FORWARD,0,180));
  right_servo.write(map(right_value,RIGHT_BACK,RIGHT_FORWARD,0,180));
  analogWrite(left_motor,throttle);
  analogWrite(right_motor,throttle);
}