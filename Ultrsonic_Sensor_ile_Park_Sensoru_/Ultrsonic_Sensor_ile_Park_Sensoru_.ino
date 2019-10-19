#define echoPin 6
#define trigPin 7
#define buzzerPin 8
#define ledOne 10
#define ledTwo 11
#define ledThree 12

int maximumRange = 25;
int minimumRange = 0;

void setup() 
{
  pinMode(echoPin , INPUT);
  pinMode(trigPin , OUTPUT);
  pinMode(buzzerPin , OUTPUT);

  pinMode(ledOne , OUTPUT);
  pinMode(ledTwo , OUTPUT);
  pinMode(ledThree , OUTPUT);
}

void loop() 
{
  int olcum = mesafe(minimumRange , maximumRange);
  melodi(olcum*10);
  lambaYak(olcum);
}

int mesafe(int minRange , int maxRange)
{
  long duration , distance;

  digitalWrite(trigPin , LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin , HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin , LOW);

  duration = pulseIn(echoPin ,HIGH);
  distance = duration / 58.2;

  delay(50);

  if(distance >= maxRange || distance <= minRange)
  {
    return 0;
  }
  else
  {
    return distance;  
  }
}

void melodi(int dly)
{
  tone(buzzerPin , 440);
  delay(dly);
  noTone(buzzerPin);
  delay(dly);
}

void lambaYak(int dstnc)
{ 
  if(dstnc > 18 && dstnc <= 25)
  {
    digitalWrite(ledOne , HIGH);
  }
  else
  {
    digitalWrite(ledOne , LOW);
  }
  
  if(dstnc > 5 && dstnc <= 18)
  {
    digitalWrite(ledOne , HIGH);
    digitalWrite(ledTwo , HIGH);
  }
  else
  {
    digitalWrite(ledTwo , LOW);
  }
  
  if(dstnc > 0 && dstnc <= 5)
  {
    digitalWrite(ledOne , HIGH);
    digitalWrite(ledTwo , HIGH);
    digitalWrite(ledThree , HIGH);
  }
  else
  {
    digitalWrite(ledThree , LOW);
  }  
}
