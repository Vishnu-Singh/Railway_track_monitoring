int objectPin=2;
int trackPin=3;
int clockPin=4;
int antiClockPin=5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(objectPin,INPUT);
  pinMode(trackPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);
  trackStatus();
  delay(1000);
  anyObject();
  delay(1000);
}

void getGPSLocation(){
  
  Serial.println("longi: 123.45.21\nlati: 256.34.23");
  //Serial.print((char)Serial.read());
}

boolean trackStatus(){
  Serial.println("\n\n--------------------------------");
  boolean stat=false;
  if(digitalRead(trackPin)){
    Serial.println("Track disconnected");
      getGPSLocation();
    stat=true;
  }
  else{
    Serial.println("Track OK");
  }
  Serial.println("--------------------------------\n\n");
}

boolean anyObject(){
  boolean stat=false;
  if(digitalRead(objectPin)){
    Serial.println("\n\n--------------------------------");
    Serial.println("Object Detected");
    Serial.println("Vechile Stoped");
    digitalWrite(clockPin,LOW);
    digitalWrite(antiClockPin,LOW);
    stat=true;
    
  }
  else{
    Serial.println("No Object");
  }
  Serial.println("--------------------------------\n\n");
}
