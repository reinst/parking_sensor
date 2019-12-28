#include <FastLED.h>
#include <NewPing.h>

#define LED_PIN     7
#define NUM_LEDS    15
#define TRIGGER_ECHO_PIN  9  // Tied to both pins
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_ECHO_PIN, TRIGGER_ECHO_PIN, MAX_DISTANCE);
CRGB leds[NUM_LEDS];
int stopdistance = 50; //parking position from sensor (CENTIMETERS)
int startdistance = 200; 
int sonar_distance;
int distance;

void setup() 
{ 
  LEDS.setBrightness(50);
  LEDS.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200); // Starts the serial communication
}
void loop() 
{
  sonar_distance = sonar.ping_cm();
  distance = map(sonar_distance, 50, 200, 0, 90);
  delay(60);                     // Wait 60ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  for(int i = 0; i < NUM_LEDS; i++)
    { if (sonar_distance>=stopdistance)
      {
        leds[i].setHue(distance);
        FastLED.show(); 
        delay(10);
      }

      else if (distance<=stopdistance)
      {
        fill_solid(leds, NUM_LEDS, CRGB::Red);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100);
        
      }
    }
}
