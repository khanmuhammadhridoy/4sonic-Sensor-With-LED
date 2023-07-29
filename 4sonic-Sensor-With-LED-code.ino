// Define LED pins
#define LED0 5
#define LED1 14
#define LED2 27
#define LED3 21

// Define trigger and echo pins for ultrasonic sensors
int trigPin0 = 2;
int echoPin0 = 4;
int trigPin1 = 12;
int echoPin1 = 13;
int trigPin2 = 25;
int echoPin2 = 26;
int trigPin3 = 18;
int echoPin3 = 19;

// Variables to store duration and distance measurements
long duration0, duration1, duration2, duration3;
int distance0, distance1, distance2, distance3;

// Variables to track LED states
bool led0State = false;
bool led1State = false;
bool led2State = false;
bool led3State = false;

// Variable to store previous millis for interval timing
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
    // Set LED pins as OUTPUT
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    // Set trigger pins as OUTPUT and echo pins as INPUT
    pinMode(trigPin0, OUTPUT);
    pinMode(echoPin0, INPUT);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);

    // Start serial communication at 36000 baud rate
    Serial.begin(36000);
}

void loop() {
    // Get the current millis value
    unsigned long currentMillis = millis();

    // Check if the interval has elapsed for simultaneous LED control
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        
        // Measure and display distance for each sensor and control respective LED
        measureAndDisplayDistance(trigPin0, echoPin0, "Distance Right Up : ", LED0, led0State);
        measureAndDisplayDistance(trigPin1, echoPin1, "Distance Left Up : ", LED1, led1State);
        measureAndDisplayDistance(trigPin2, echoPin2, "Distance Left Down : ", LED2, led2State);
        measureAndDisplayDistance(trigPin3, echoPin3, "Distance Right Down : ", LED3, led3State);
    }
}

// Function to measure distance and control LED based on distance range
void measureAndDisplayDistance(int trigPin, int echoPin, const char* prefix, int ledPin, bool& ledState) {
    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the duration and calculate distance
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;

    // Print distance to Serial Monitor
    Serial.print(prefix);
    Serial.println(distance);

    // Control LED based on distance range
    if (distance <= 100) {
        digitalWrite(ledPin, HIGH);
        ledState = true;
    } else if (distance > 100 && distance <= 200) {
        // Blink the LED if the distance is between 100 and 200
        if (ledState) {
            digitalWrite(ledPin, LOW);
            ledState = false;
        } else {
            digitalWrite(ledPin, HIGH);
            ledState = true;
        }
    } else {
        // Turn off the LED if the distance is greater than 200
        digitalWrite(ledPin, LOW);
        ledState = false;
    }
}
