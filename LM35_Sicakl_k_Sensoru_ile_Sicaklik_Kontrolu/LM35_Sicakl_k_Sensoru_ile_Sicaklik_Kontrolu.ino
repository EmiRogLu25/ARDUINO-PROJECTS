#define red 8//RGB ledin kirmizi bacagini 8.pine bagliyoruz
#define green 9//RGB ledin yesil bacagini 9.pine bagliyoruz
#define blue 10//RGB ledin mavi bacagini 10.pine bagliyoruz
#define lm35Pin A0//LM35 sicaklik sensorunu A0 pinine bagliyoruz

int okunanDeger = 0;//sicaklik sensorununden okunan degeri tutacagimiz degiskeni olusturuyoruz
float sicaklikGerilim = 0.0;//sicaklik geriliminin hesaplanmasi icin degiskeni olusturuyoruz
float sicaklik = 0.0;//sicaklik degeri degiskeni

void setup()
{
  Serial.begin(9600);//Serial monitorde sicaklik degerini gormek icin seriali baslatiyoruz
  
  //RGB led icin renkleri cikis veriyoruz
  pinMode(red , OUTPUT);
  pinMode(green , OUTPUT);
  pinMode(blue , OUTPUT); 
}

void loop()
{  
   //sicaklik sendorunden degeri okuyup santigrat cinsinden hesapliyip "sicaklik" degiskenine aktariyoruz
   okunanDeger = analogRead(lm35Pin);
   sicaklikGerilim = (5000.0 / 1023.0)* okunanDeger;
   sicaklik = sicaklikGerilim / 10.0;

   Serial.println(sicaklik);//sicaklik degerini serial monitore yazdiriyoruz
  
   if(sicaklik > 20 && sicaklik <=25)
   {
      renkAyarla(255,0,255);//yesil
   }
   else if(sicaklik > 25 && sicaklik <= 30)
   {
      renkAyarla(0,0,255);//sari 
   }
   else if(sicaklik > 30)
   {
      renkAyarla(0,255,255);//kirmizi
   }
   else
   {
      renkAyarla(255,255,0);//mavi 
   }
}

//RGB ledi ayarlayan metod
void renkAyarla(int redValue,int greenValue,int blueValue)
{ 
  analogWrite(red , redValue);
  analogWrite(green , greenValue);
  analogWrite(blue , blueValue);
}
