#include "SR04.h"
#include "IRremote.h"

#define TRIG_PIN 12
#define ECHO_PIN 11

int receiver = 10; // Signal Pin of IR receiver to Arduino Digital Pin 11

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

long dist;
long threshold = 17;
int counter = 0;
int max_people = 160;
int places_left = max_people;
int time_offset = 5;
long dt = 0;
bool detected = false;

void setup() {
   Serial.begin(9600);
   irrecv.enableIRIn(); // Start the receiver
   delay(500);
}

int translateIR() { // Takes action based on IR code received
  int res = 0;
  switch(results.value) {
    case 0xFFA25D:  ; break; // Power
    case 0xFFE21D:  ; break; // Func/Stop
    case 0xFF629D:  ; break; // Vol+
    case 0xFF22DD:  ; break; // Fast Back
    case 0xFF02FD:  ; break; // Pause
    case 0xFFC23D:  ; break; // Fast Forward
    case 0xFFE01F:  res = -1; break; // Down
    case 0xFFA857:  ; break; // Vol-
    case 0xFF906F:  res = 1; break; // Up
    case 0xFF9867:  ; break; // Eq
    case 0xFFB04F:  ; break; // St/Rept
    case 0xFF6897:  ; break; // 0
    case 0xFF30CF:  ; break; // 1
    case 0xFF18E7:  ; break; // 2
    case 0xFF7A85:  ; break; // 3
    case 0xFF10EF:  ; break; // 4
    case 0xFF38C7:  ; break; // 5
    case 0xFF5AA5:  ; break; // 6
    case 0xFF42BD:  ; break; // 7
    case 0xFF4AB5:  ; break; // 8
    case 0xFF52AD:  ; break; // 9
    case 0xFFFFFFFF:  ; break; // Repeat  

    default: 
      break;
      
  } // End Case

  // delay(500); // Do not get immediate repeat
  return res;

} //END translateIR


void loop() {
   dist = sr04.Distance();
   
   // Serial.print(dist);
   // Serial.println(" cm");

   if (dist < threshold && detected == false) {
      dt++;
      if (dt >= time_offset) {
        places_left--;
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

   // Receive IR signal
   if (irrecv.decode(&results)) {
     places_left = places_left + translateIR(); 
     irrecv.resume();
   }
   
   // Serial.print("Places left: ");
   Serial.println(places_left);

   delay(1);
}
