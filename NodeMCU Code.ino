// NodeMCU Code
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



SoftwareSerial NodeMCU(D2,D3);
char auth[] = "GZrHi_u0D9d4BC3gb0w6q_qgINa6aBsZ"; //Blynk authentication token
char ssid[] = "";        // wifi hotspot
char pass[] = "";   //wifi password

void setup(){
	Serial.begin(9600);
	NodeMCU.begin(4800);
	pinMode(D2,INPUT);
	pinMode(D3,OUTPUT);
 pinMode(D0,OUTPUT);
   Blynk.begin(auth, ssid, pass);
 
 

}

void loop(){
   Blynk.run();
  while(NodeMCU.available()>0){
  int val = NodeMCU.parseInt();
  if(NodeMCU.read()== '\n'){
  Serial.println(val);
  if(val==1)
  {
    digitalWrite(D0,HIGH);
     Blynk.email("mabhishek0898@gmail.com", "Smart Lock", "Somebody Entered Wrong Password ");
    Blynk.notify("Smart Lock -> Somebody Entered Wrong Password");
  
    
  }
  else
  {
    digitalWrite(D0,LOW);
  }
  }
}
delay(30);
  
  

 }
