
int pitch = 0;
int yaw = 0;
int roll = 0;
int throttle = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(57600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  throttle = analogRead(A3);
  roll = analogRead(A1);
  pitch = analogRead(A0);
  
  throttle = map(throttle, 0, 1023, 0, 125);
  roll = map(roll, 50, 950, -127, 127);
  pitch = map(pitch, 50, 950, -127, 127);
  
  if(throttle < 15) throttle = 0;
  else if(throttle > 125) throttle = 125;
  
  if(pitch < -125) pitch = -125;
  else if(pitch > 125) pitch = 125;
  
  if(roll < -125) roll = -125;
  else if(roll > 125) roll = 125;
  
//  Serial.print("Throttle: ");
//  Serial.print(throttle);
//  
//  Serial.print("     Roll: ");
//  Serial.print(roll);
//  
//  Serial.print("    Pitch: ");
//  Serial.println(pitch);

  Serial.write(0xFA);
  Serial.write(0xEF);
  Serial.write(pitch);
  Serial.write(roll);
  Serial.write(throttle);
  
  delay(20);

}
