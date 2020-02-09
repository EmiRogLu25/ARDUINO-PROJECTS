#include <Servo.h>

//L298N Motor Surucusunun Bağlantısı
#define motorSagIleri 5 //L298N'in IN1 girisi
#define motorSagGeri 6 //L298N'in IN2 girisi
#define motorSolIleri 9 //L298N'in IN3 girisi
#define motorSolGeri 10 //L298N'in IN4 girisi

//HC-SR04 Ultrasonik Mesafe Sensoru baglantisi
#define echoPin 12 //HC-SR04'in echoPin baglantisi
#define trigPin 13 //HC-SR04'in trigPin baglantisi

//Cizgi Izleyen Sensor baglantisi
#define sensorSol 2
#define sensorOrta 3
#define sensorSag 4

//HC-SR04'den gelen verilerin anlamli hale getirilmesine yarayan degiskenler
long sure;
long uzaklik;

//Bluetooth cihazindan gelecek sinyalin değiskeni
int bluetoothDurum;
//Bluetooth'dan gelen veriler ; 
//ileri=8
//geri=2
//sag=6
//sol=4
//dur=5

Servo servoMotor;//Servo motor degiskeni
int solUzaklik;//tank durdugunda HC06 sola doner ve sol uzakligi hesaplar
int sagUzaklik;//tank durdugunda HC06 saga doner ve sag uzakligi hesaplar

int motorHizi = 255;//motor hizini belirler

void setup()
{
  //Pinlerin belirlenmesi
  pinMode(motorSagIleri , OUTPUT);
  pinMode(motorSagGeri , OUTPUT);
  pinMode(motorSolIleri , OUTPUT);
  pinMode(motorSolGeri , OUTPUT);

  pinMode(trigPin , OUTPUT);//trigPin ses dalgasi gonderir
  pinMode(echoPin , INPUT);//echoPin bu ses dalgasini geri alir

  pinMode(sensorSol , INPUT);
  pinMode(sensorOrta , INPUT);
  pinMode(sensorSag , INPUT);

  servoMotor.attach(3);//Servo motoru 3 nolu pine baglanmasi
  servoMotor.write(90);//Servo motoru 90 dereceye ayarlanmasi
  
  Serial.begin(9600);//Bluetooth haberlesmesi icin seri port acilmasi
}

void loop()
{
  //Gelen veriyi 'bluetoothDurum' degiskenine kaydet
  if(Serial.available() > 0)
  {
    bluetoothDurum = Serial.read();
  }

  aracModKontrol();
  aracYonKontrol();
}

void aracModKontrol()
{
  if(bluetoothDurum == '1')//Arac modu "CIZGI TAKIP EDEN ARAC MODU" olur
  {
    cizgiIzle();
  }
  else if(bluetoothDurum == '0')//Arac modu "ENGELDEN KACAN ARAC MODU" olur
  {
    aracEngelKontrolluIlerle();
  }
  else if(bluetoothDurum == '5')
  {
    dur();
  }
}

void aracYonKontrol()
{
  motorHizi = 255;
  
  //Bluetooth'dan gelen veriye gore arac hareket eder
  if(bluetoothDurum == '8')//ileri gider
  {
    ileriGit();
  }
  else if(bluetoothDurum == '2')//geri gider
  {
    geriGit();
  }
  else if(bluetoothDurum == '6')//saga gider
  {
    sagaGit();
  }
  else if(bluetoothDurum == '4')//sola gider
  {
    solaGit();
  }
  else if(bluetoothDurum == '5')//durur
  {
    dur();
  }
}

void ileriGit()
{
  analogWrite(motorSagIleri , motorHizi);
  analogWrite(motorSagGeri , 0);
  analogWrite(motorSolIleri , motorHizi);
  analogWrite(motorSolGeri , 0);
}

void geriGit()
{
  analogWrite(motorSagIleri , 0);
  analogWrite(motorSagGeri , motorHizi);
  analogWrite(motorSolIleri , 0);
  analogWrite(motorSolGeri , motorHizi);
}

void sagaGit()
{
  analogWrite(motorSagIleri , 0);
  analogWrite(motorSagGeri , 150);
  analogWrite(motorSolIleri , motorHizi);
  analogWrite(motorSolGeri , 0);
}

void solaGit()
{
  analogWrite(motorSagIleri , motorHizi);
  analogWrite(motorSagGeri , 0);
  analogWrite(motorSolIleri , 0);
  analogWrite(motorSolGeri , 150);
}

void dur()
{
  analogWrite(motorSagIleri , 0);
  analogWrite(motorSagGeri , 0);
  analogWrite(motorSolIleri , 0);
  analogWrite(motorSolGeri , 0);
}

void aracEngelKontrolluIlerle()
{
  motorHizi = 255;
  
  //Aracin engele olan uzakligi 15cm den kucukse arac durur
  //Diger durumda arac ileri gider
  if(mesafeOlc() < 15)
  {
    dur();

    //Servo motor yardimiyla HC-SR04 sensoru sola ve saga bakar ve uzakliklari hesaplar
    servoMotor.write(0);
    delay(100);
    solUzaklik = mesafeOlc();
    servoMotor.write(180);
    delay(100);
    sagUzaklik = mesafeOlc();
    delay(100);
    servoMotor.write(90);

    //Eger sol uzaklik sag uzakliktan kucukse arac saga doner
    //Eger sag uzaklik sol uzakliktan kucukse arac sola doner
    //Bunlarin disi durumda ise arac saga doner
    if(solUzaklik < sagUzaklik)
    {
      geriGit();
      delay(150);
      sagaGit();
      delay(250);
    }
    else if(sagUzaklik < solUzaklik)
    {
      geriGit();
      delay(150);
      solaGit();
      delay(250);
    }
    else
    {
      geriGit();
      delay(150);
      sagaGit();
      delay(250);
    }     
  }
  else
  {
    ileriGit();
  }
}

int mesafeOlc()
{
  //HC-SR04'in trigPininden sinyali gonderdi ve 10 microsaniye bekledi
  //Sonra bu sinyali echoPininden geri aldi
  //sureyi hesapladiktan sonra ozel bir formulle uzakligi hesapladi
  digitalWrite(trigPin , LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin , HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin , LOW);

  sure = pulseIn(echoPin , HIGH);
  uzaklik = sure/58.2;

  return uzaklik;
}

void cizgiIzle()
{
  motorHizi = 150;
  
  if(digitalRead(sensorSol) == 0 && digitalRead(sensorOrta) == 1 && digitalRead(sensorSag) == 0)
  {
    ileriGit();
  }
  else if(digitalRead(sensorSol) == 1 && digitalRead(sensorOrta) == 0 && digitalRead(sensorSag) == 0)
  {
    solaGit();
  }
  else if(digitalRead(sensorSol) == 0 && digitalRead(sensorOrta) == 0 && digitalRead(sensorSag) == 1)
  {
    sagaGit();
  }
}
