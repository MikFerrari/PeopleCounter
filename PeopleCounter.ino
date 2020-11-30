#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long dist;
long threshold = 20;
int counter = 0;
int max_people = 150;
int places_left = max_people;
int time_offset = 5;
long dt = 0;
bool detected = false;

void setup() {
   Serial.begin(9600);
   delay(1000);
}

void loop() {
   dist = sr04.Distance();
   
   // Serial.print(dist);
   // Serial.println(" cm");

   if (dist < threshold && detected == false) {
      dt++;
      if (dt >= time_offset) {
        counter++;
        places_left = max_people - counter;
        // Serial.println("Detected");
        dt = 0;
        detected = true;
      }
      else {
        detected = false;
      }
   }
   else if (dist >= threshold && detected == true) {
      dt++;
      if (dt >= time_offset) {
        detected = false;
      }
   }
   else {
    dt = 0;
   }
   
   if (places_left <= 0) {
     // Serial.println("No more places left");
     places_left = 0;
   }
   
   // Serial.print("Places left: ");
   Serial.println(places_left);

   delay(1);
}
