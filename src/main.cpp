
#include <Arduino.h>
#ifndef RESPONSE
#define RESPONSE
#include <response.hpp>
#endif


#ifndef SERVER
#define SERVER
#include <server.hpp>
#endif

#define BUZZER_FET 30
#define IGNITE_FET 31
#define CURRENT_IN A0
#define MAX_TIME 30000
#define BAUD 9600
#define READ_RATE 200

// Initializing vars
unsigned int READ_INTERVAL = 1000 / READ_RATE;
unsigned long int t0 = 0;
unsigned long int t = 0;
double current = 0;
bool counting = false;
unsigned long int miliseconds_passed = 0;
unsigned long int delta;

Response r = Response();
Serv sv = Serv(counting, miliseconds_passed, current);

// Declaring functions
/* Returns the current in the CURRENT_IN pin */
double readCurrent(){
  return analogRead(CURRENT_IN);
}

/* Encodes the response into a human readable string */
void encodeResponse(char *buffer, Response r){
  sprintf(buffer, "%d - %s", r.status, r.payload);
}

/** Starts the ignition process; */
void ignite(){
  digitalWrite(IGNITE_FET, HIGH);
}

/* Stops the ignition process */
void unignite(){
  digitalWrite(IGNITE_FET, LOW);
}

// Arduino functions

void setup() {
  Serial1.begin(BAUD);  
  pinMode(BUZZER_FET, OUTPUT);
  pinMode(IGNITE_FET, OUTPUT);
}

void loop() {
  t = millis();
  if(t > (t0 + READ_INTERVAL)){
    current = readCurrent();
    if(Serial.available() > 0){
      r = sv.runCommand(Serial.read());
      char buffer[64];
      encodeResponse(buffer, r);
      Serial1.write(buffer);
    } 
    if(counting){
      delta = t - t0;
      if(miliseconds_passed > MAX_TIME){
        ignite();
      }else{
        miliseconds_passed += delta;
      }
    }
    t0 = t;
  }
}