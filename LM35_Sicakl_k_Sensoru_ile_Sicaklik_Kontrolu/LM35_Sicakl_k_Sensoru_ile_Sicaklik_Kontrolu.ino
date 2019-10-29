#define red 8
#define green 9
#define blue 10
#define lm35Pin A0

int okunanDeger = 0;
float sicaklikGerilim = 0.0;
float sicaklik = 0.0;

void setup()
{
  Serial.begin(9600);
  pinMode(red , OUTPUT);
  pinMode(green , OUTPUT);
  pinMode(blue , OUTPUT); 
}

void loop()
{  
   okunanDeger = analogRead(lm35Pin);
   sicaklikGerilim = (5000.0 / 1023.0)* okunanDeger;
   sicaklik = sicaklikGerilim / 10.0;

   Serial.println(sicaklik);

   if(sicaklik > 20 && sicaklik <=25)
   {
      renkAyarla(255,0,255);
   }
   else if(sicaklik > 25 && sicaklik <= 30)
   {
      renkAyarla(0,0,255); 
   }
   else if(sicaklik > 30)
   {
      renkAyarla(0,255,255); 
   }
   else
   {
      renkAyarla(255,255,0); 
   }
}

void renkAyarla(int redValue,int greenValue,int blueValue)
{ 
  analogWrite(red , redValue);
  analogWrite(green , greenValue);
  analogWrite(blue , blueValue);
}
