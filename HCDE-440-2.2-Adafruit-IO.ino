// Peter Schultz ICE 2 4/12/19
/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
/************************ Example Starts Here *******************************/
float hum=0;
// pin connected to DH22 data line
#define DATA_PIN 12 

// create DHT22 instance
DHT_Unified dht(DATA_PIN, DHT22); // initializes dht object

int PHOTOCELL_PIN = 0; // photocell data input to pin 0

int curPhoto = 0;

AdafruitIO_Feed *analog = io.feed("analog"); // set up feeds
AdafruitIO_Feed *humidity = io.feed("humidity");

void setup() {


  // start the serial connection
  Serial.begin(115200);
  Serial.print("This board is running: ");
  Serial.println(F(__FILE__));
  Serial.print("Compiled: ");
  Serial.println(F(__DATE__ " " __TIME__));
   
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect(); // connects to the adafruit website

  // wait for a connection
  while(io.status() < AIO_CONNECTED) { //test
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  Serial.println("initializing dht");
  dht.begin(); // initializes dht sensor

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  curPhoto = analogRead(PHOTOCELL_PIN); // reads analog data from photocell
  Serial.print("Photocell: ");
  Serial.println(curPhoto);
  sensors_event_t event;// initializes dht sensor event

  dht.humidity().getEvent(&event); // define event
  hum = event.relative_humidity;
  Serial.print("humidity: ");
  Serial.print(hum);
  Serial.println("%");
  
  analog->save(curPhoto); // saves data to adafruit io
  humidity->save(hum);
  // store last button state
//  last = current;
  delay(3000);
}
