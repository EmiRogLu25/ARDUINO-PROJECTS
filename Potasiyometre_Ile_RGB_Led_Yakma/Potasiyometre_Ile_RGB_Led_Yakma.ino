#define blue 9
#define green 10
#define red 11
#define potBlue A0
#define potGreen A1
#define potRed A2

void setup() 
{  
  pinMode(blue , OUTPUT);
  pinMode(green , OUTPUT);
  pinMode(red , OUTPUT);
}

void loop() 
{  
  int blueValue = analogRead(potBlue);
  int greenValue = analogRead(potGreen);
  int redValue = analogRead(potRed);

  blueValue = map(blueValue , 0 , 1023 , 0 , 255);
  greenValue = map(greenValue , 0 , 1023 , 0 , 255);
  redValue = map(redValue , 0 , 1023 , 0 , 255);
  
  analogWrite(blue , blueValue);
  analogWrite(green , greenValue);
  analogWrite(red , redValue);
}
