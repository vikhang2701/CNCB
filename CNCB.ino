#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int tempPin = A0;
float Vo;
float R1 = 10000;
float logR2, R2, T, temp;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float tempC;
int relay = 8;
int ledr = 9;
int ledxd = 10;
int buzzer = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledr, OUTPUT);
  digitalWrite(ledr, LOW);
  pinMode(ledxd, OUTPUT);
  digitalWrite(ledxd, LOW);  
  pinMode (relay, OUTPUT);
  digitalWrite(relay,LOW);
  pinMode(buzzer, OUTPUT);
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("    NHOM 5    "); 
  lcd.setCursor (0,1);
  lcd.print ("  DO NHIET DO ");
  Serial.begin(9600);
  pinMode(tempPin, INPUT);
  delay(3000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  tempC = get_temp();
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");
  lcd.setCursor(0, 0); 
  lcd.print("DO NHIET DO NTC  "); 
  lcd.setCursor (0,1);
  lcd.print("NHIET DO:");
  lcd.setCursor (9,1); 
  lcd.print (tempC);
  lcd.setCursor (14,1);
  lcd.print (" C");
  if(tempC <= 30)
  {
    digitalWrite(ledxd,HIGH);
    digitalWrite(ledr,LOW);
    digitalWrite(relay,LOW);
    digitalWrite(buzzer, LOW);  
  }
  else
  {
    digitalWrite(ledxd,LOW);
    digitalWrite(ledr,HIGH);
    digitalWrite(relay,HIGH);
    digitalWrite(buzzer, HIGH); 
  }
  delay(500);
}
float get_temp() {
  Vo = analogRead(tempPin);
  R2 = R1 * (1023.0 / Vo - 1.0); // R2= R1*(Vin/Vout - 1)
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  return T - 273.15; //độ C
}
