#define blue 9//RGB ledin mavi bacagini 9.pine bagliyoruz
#define green 10//RGB ledin yesil bacagini 10.pine bagliyoruz
#define red 11//RGB ledin kirmizi bacagini 11.pine bagliyoruz
#define potBlue A0//Mavi rengin degeri icin A0 pinine potansiyometre bagliyoruz
#define potGreen A1//Yesil rengin degeri icin A1 pinine potansiyometre bagliyoruz
#define potRed A2//Kirmizi rengin degeri icin A2 pinine potansiyometre bagliyoruz

void setup() 
{  
  //RGB led icin renkleri cikis veriyoruz 
  pinMode(blue , OUTPUT);
  pinMode(green , OUTPUT);
  pinMode(red , OUTPUT);
}

void loop() 
{  
  //potlardan gelen verileri degiskenlere aktariyoruz
  int blueValue = analogRead(potBlue);
  int greenValue = analogRead(potGreen);
  int redValue = analogRead(potRed);

  //potlardan gelen 0-1023 araligini 0-255 araligina ceviriyoruz
  //cunku RGB led 0-255 araliginda calisir
  blueValue = map(blueValue , 0 , 1023 , 0 , 255);
  greenValue = map(greenValue , 0 , 1023 , 0 , 255);
  redValue = map(redValue , 0 , 1023 , 0 , 255);
  
  //potlardan okunan degerleri RGB lede yaziyoruz
  analogWrite(blue , blueValue);
  analogWrite(green , greenValue);
  analogWrite(red , redValue);
}
