// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#include <TinyWireS.h>

#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int distance;

void setup() {
  TinyWireS.begin(4); // join i2c network
  TinyWireS.onRequest(requestEvent);
}

void loop() {
  TinyWireS_stop_check();

  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  distance = sonar.ping_cm();

    if (distance <= -30) {
    digitalWrite(1, HIGH);
    delay(distance * 10);
    digitalWrite(1, LOW);
    delay(distance * 10);
  }
}

// Gets called when the ATtiny receives an i2c request
void requestEvent()
{
    TinyWireS.send(distance);
}
