#include <ESP8266WiFi.h> 
#define EN1 D6    // Enable PIN to control speed 
#define EN2 D7 
 
const int trigP = 2; //D4
const int echoP = 0; //D3
long duration;
int distance;

 
String  data = "";  
 
void setup() { 
   
  pinMode(EN1, OUTPUT); 
  pinMode(EN2,OUTPUT); 
  pinMode(trigP, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoP, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
} 
 
void loop() { 
  digitalWrite(trigP, LOW); 
  delayMicroseconds(2);// Makes trigPin low
  digitalWrite(trigP, HIGH); // tigPin high
  delayMicroseconds(10);
  digitalWrite(trigP, LOW);
  duration = pulseIn(echoP, HIGH); //Read echo pin, time in
  distance= duration*0.034/2; //Calculating actual/real
double w1_fin = 10.140420;
double w2_fin = 14.012266;
double LS = w1_fin * distance;
double RS = w2_fin *distance; 
Serial.println("distance: ");
Serial.println(distance);
    analogWrite(EN1,LS); 
  analogWrite(EN2,RS);  
  Serial.println("RS: ");
  Serial.print(RS);
  Serial.println("LS: ");
  Serial.println(LS); 
} 
