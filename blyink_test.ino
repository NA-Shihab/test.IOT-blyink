#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6rbwLppdo"
#define BLYNK_TEMPLATE_NAME "Ohhhhh HELLLLLLLL YAAA"
#define BLYNK_AUTH_TOKEN "K2GEWZ26SpTNetYuePiUGh5Dtim1NfH2"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>  // Ensure this library is installed


// Your WiFi credentials
char ssid[] = "";
char pass[] = "";

// Define LED pins
#define YELLOW_LED_PIN 2
#define BLUE_LED_PIN 4
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define DHT_PIN 14
#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);

// Blynk Timers for each LED
BlynkTimer timer;
int yellowBlinkTimerId = 0;
int blueBlinkTimerId = 0;
int redBlinkTimerId = 0;
int greenBlinkTimerId = 0;

// Function to toggle the state of an LED
void toggleLED(int pin, bool &state) {
  state = !state;
  digitalWrite(pin, state);
}

// Functions to blink each LED
bool yellowLedState = false;
void blinkYellowLED() {
  toggleLED(YELLOW_LED_PIN, yellowLedState);
}

bool blueLedState = false;
void blinkBlueLED() {
  toggleLED(BLUE_LED_PIN, blueLedState);
}

bool redLedState = false;
void blinkRedLED() {
  toggleLED(RED_LED_PIN, redLedState);
}

bool greenLedState = false;
void blinkGreenLED() {
  toggleLED(GREEN_LED_PIN, greenLedState);
}

void setup() {
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();

  // Set LED pins as outputs
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

// Function to handle the button press from the Blynk app for each LED
BLYNK_WRITE(V1) {
  int pinValue = param.asInt(); // Get the value of the button

  if (pinValue == 1) {
    if (yellowBlinkTimerId == 0) {
      yellowBlinkTimerId = timer.setInterval(1000L, blinkYellowLED);
    }
  } else {
    if (yellowBlinkTimerId != 0) {
      timer.deleteTimer(yellowBlinkTimerId);
      yellowBlinkTimerId = 0;
      digitalWrite(YELLOW_LED_PIN, LOW);
      yellowLedState = false;
    }
  }
}

BLYNK_WRITE(V2) {
  int pinValue = param.asInt(); // Get the value of the button

  if (pinValue == 1) {
    if (blueBlinkTimerId == 0) {
      blueBlinkTimerId = timer.setInterval(1000L, blinkBlueLED);
    }
  } else {
    if (blueBlinkTimerId != 0) {
      timer.deleteTimer(blueBlinkTimerId);
      blueBlinkTimerId = 0;
      digitalWrite(BLUE_LED_PIN, LOW);
      blueLedState = false;
    }
  }
}

BLYNK_WRITE(V3) {
  int pinValue = param.asInt(); // Get the value of the button

  if (pinValue == 1) {
    if (redBlinkTimerId == 0) {
      redBlinkTimerId = timer.setInterval(1000L, blinkRedLED);
    }
  } else {
    if (redBlinkTimerId != 0) {
      timer.deleteTimer(redBlinkTimerId);
      redBlinkTimerId = 0;
      digitalWrite(RED_LED_PIN, LOW);
      redLedState = false;
    }
  }
}

BLYNK_WRITE(V4) {
  int pinValue = param.asInt(); // Get the value of the button

  if (pinValue == 1) {
    if (greenBlinkTimerId == 0) {
      greenBlinkTimerId = timer.setInterval(1000L, blinkGreenLED);
    }
  } else {
    if (greenBlinkTimerId != 0) {
      timer.deleteTimer(greenBlinkTimerId);
      greenBlinkTimerId = 0;
      digitalWrite(GREEN_LED_PIN, LOW);
      greenLedState = false;
    }
  }
}

void loop() {
  Blynk.run();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.println(humidity);
  Serial.println(temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V0, temperature);
  timer.run();
}
