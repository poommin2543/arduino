#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "cOGDz4MW5vczC0Wp4wsg0H489vAVXMhv"; 
char ssid[] = "phinphimai";
char pass[] = "0861107657";

#define r 5 // D1 <-> IN1
#define b 0  // D3 <-> IN2
#define l 4  // D2 <-> IN3
#define g 2  // D4 <-> IN4 
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,"blynk.iot-cm.com", 8080);

  pinMode(r, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(l, OUTPUT);
  pinMode(g, OUTPUT);

  digitalWrite(r, LOW);
  digitalWrite(b, LOW);
  digitalWrite(l, LOW);
  digitalWrite(g, LOW);

}

void loop() {
  Blynk.run();
}
void halt()
{
 digitalWrite(l, LOW);
 digitalWrite(r, LOW);
 digitalWrite(g, LOW);
 digitalWrite(b, LOW);
}

BLYNK_WRITE(V0)
{
 if (param[0]){
 digitalWrite(g, HIGH);
 Serial.println("Go");}
 else
 halt();
}

BLYNK_WRITE(V1)
{
 if (param[0]){
 digitalWrite(b, HIGH);
 Serial.println("back");}
 else
 halt();
}

BLYNK_WRITE(V2)
{
 if (param[0]){
 digitalWrite(r, HIGH);
 Serial.println("right");}
 else
 halt();
}

BLYNK_WRITE(V3)
{
 if (param[0]){
 digitalWrite(l, HIGH);
 Serial.println("life");}
 else
 halt();
}  
