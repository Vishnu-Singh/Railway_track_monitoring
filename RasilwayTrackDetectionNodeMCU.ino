/*************************************************************


/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TinyGPS.h>

char auth[] = "YM_qAUvJHq4ro_sbCuyCFcKK15Fqsl5k";
char ssid[] = "Pooja";
char pass[] = "poojaroja123";

int crackPin=D7;
int objectPin=D8;
int motorClock=D4;
int motorAntiClock=D5;

TinyGPS gps;
WidgetMap myMap(V9);

void setup()
{
  // Debug console
  pinMode(crackPin,INPUT);
  pinMode(objectPin,INPUT);
  pinMode(motorClock,OUTPUT);
  pinMode(motorAntiClock,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V8){
  int val=param.asInt();
  if(val){
    check();
    Serial.println("Started");
    Blynk.virtualWrite(V12,"Started");
  }else{
    Blynk.virtualWrite(V12,"Stoped");
  }
}


BLYNK_WRITE(V7){
  int val=param.asInt();
  if(val==HIGH){
    digitalWrite(motorAntiClock,HIGH);
    Serial.println("BackWard");
    Blynk.virtualWrite(V12,"Backward");
  }else{
    digitalWrite(motorAntiClock,LOW);
    Serial.println(".....");
    Blynk.virtualWrite(V12,"......");
  }
}

void loop()
{
  Blynk.run();
  check();
}


void checkCrack(){
  if(digitalRead(crackPin)==HIGH){
    Blynk.virtualWrite(V10,"Crack");
  }else{
    Blynk.virtualWrite(V10,".....");
  }
  
}


void checkObject(){
  if(digitalRead(objectPin)==HIGH){
    Blynk.virtualWrite(V11,"Object");
  }else{
    Blynk.virtualWrite(V11,".....");
  }
  
}


void wheel(int val){
  if(val){
    digitalWrite(motorClock,HIGH); 
    Blynk.virtualWrite(V13,"Started");
  }else{
    
    digitalWrite(motorClock,LOW); 
    Blynk.virtualWrite(V13,"......");
  }
}

void check(){
  while(digitalRead(objectPin)==LOW&&digitalRead(crackPin)==HIGH){
    wheel(HIGH);
    checkCrack();
    checkObject();
  }
  while(digitalRead(objectPin)==HIGH&&digitalRead(crackPin)==LOW){
    wheel(HIGH);
    checkCrack();
    checkObject();
  }
  wheel(LOW);
  getLocation();
}
void getLocation(){
  float lat,lon;
  while(Serial.available()){
    char c=Serial.read();
    if(gps.encode(c)){
      gps.f_get_position(&lat,&lon);
      //Blynk.virtualWrite();
      myMap.location(1,lat,lon,"BOT");
    }
  }
}
