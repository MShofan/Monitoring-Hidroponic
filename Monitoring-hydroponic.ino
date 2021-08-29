#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";

#define triggerPin D8
#define echoPin    D7
int Buzzer = D6;
const int oneWireBus = D5;
int relayPin1 = D0;
int relayPin2 = D1;

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);




void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  sensors.begin();
  Blynk.begin(auth, ssid, pass);
  digitalWrite(relayPin1, OUTPUT);
  digitalWrite(relayPin2, OUTPUT);
 }

void loop() {
  {
  // put your main code here, to run repeatedly:
long duration, jarak;
digitalWrite(triggerPin, LOW);
delayMicroseconds(2);
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(triggerPin, LOW);
duration = pulseIn(echoPin, HIGH);
jarak = (duration/2)/29.1;
Serial.println("jarak : ");
Serial.print(jarak);
Serial.println("  cm");
Blynk.virtualWrite(11, jarak);
delay(5000);
if(jarak <= 5){
  digitalWrite(Buzzer, LOW);
}else{
  tone(Buzzer, 400);
  Blynk.notify("cek dan tambahkan air nutrisi.!!");
}
sensors.requestTemperatures();
float temperatureC = sensors.getTempCByIndex(0);
Blynk.virtualWrite(10, temperatureC);
delay(1000);
Blynk.run();
}
}
