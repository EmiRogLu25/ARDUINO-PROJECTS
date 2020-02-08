#define echoPin 6//HC06 ultrasonic sensorun echo pini giris pinidir yani dalgayi alan pindir
#define trigPin 7//HC06 ultrasonic sensorun trig pini cikis pinidir yadi dalgayi ureten pindir
#define buzzerPin 8//Buzzeri 8. pine bagladik
//Mesafeninin siddetini gostermek icin uc led kullanildi
#define ledOne 10//Birinci led 10.pine bagladik
#define ledTwo 11//Ikinci ledi 11.pine bagladik
#define ledThree 12//Ucuncu ledi 12.pine bagladik

//HC06 ultrasonic sensorun hangi aralikta olcum yapacagini belirledik
int maximumRange = 25;
int minimumRange = 0;

void setup() 
{
  pinMode(echoPin , INPUT);//HC06 echo pini dalga alan pin oldugundan giris pinidir
  pinMode(trigPin , OUTPUT);//HC06 trig pini dalga ureten pin oldugundan cikis pinidir
  pinMode(buzzerPin , OUTPUT);//Buzzer ses ureten pin oldugundan cikis pinidir

  //ledler cikis pinidir
  pinMode(ledOne , OUTPUT);
  pinMode(ledTwo , OUTPUT);
  pinMode(ledThree , OUTPUT);
}

void loop() 
{
  //Mesafeyi olcer ve mesafeye gore ledi ve lambayı yakar
  int olcum = mesafe(minimumRange , maximumRange);
  melodi(olcum*10);
  lambaYak(olcum);
}

//Bu metod HC06 ultrasonic sensoru sayesinde mesafeyi olcer ve olculen deger max ve min deger araligindaysa dondurulur
int mesafe(int minRange , int maxRange)
{
  long duration , distance;

  //HC06 tarafindan dalga uretilir ve uretilen dalga cisme carptiginda geri doner ve dalga HC06 tarafindan geri alinir 
  digitalWrite(trigPin , LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin , HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin , LOW);

  //mesafe olculur
  duration = pulseIn(echoPin ,HIGH);
  distance = duration / 58.2;

  delay(50);

  //Olculen deger max-min deger araligindaysa geri donus yapilir
  if(distance >= maxRange || distance <= minRange)
  {
    return 0;
  }
  else
  {
    return distance;  
  }
}

//Bu metod buzzerdan mesafeye gore melodi calar
void melodi(int dly)
{
  tone(buzzerPin , 440);
  delay(dly);
  noTone(buzzerPin);
  delay(dly);
}

//Bu metod mesafeye gore ledleri yakar
void lambaYak(int dstnc)
{ 
  //Eğer mesafe 18-25 cm araligindaysa bir tane led yanar
  if(dstnc > 18 && dstnc <= 25)
  {
    digitalWrite(ledOne , HIGH);
  }
  else
  {
    digitalWrite(ledOne , LOW);
  }
  
  ////Eğer mesafe 5-18 cm araligindaysa iki tane led yanar
  if(dstnc > 5 && dstnc <= 18)
  {
    digitalWrite(ledOne , HIGH);
    digitalWrite(ledTwo , HIGH);
  }
  else
  {
    digitalWrite(ledTwo , LOW);
  }
  
  //Eğer mesafe 0-5 cm araligindaysa uc tane led yanar
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
