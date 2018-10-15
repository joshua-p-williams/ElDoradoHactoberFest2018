// Our LED is connected to pin 10
const int BLINK_LED = 10;

/**
 * The setup method gets called only once at the beginning of the application
 */
void setup() {
  // Before we can writ the LED we have to open this PIN for output
  pinMode(BLINK_LED, OUTPUT);
}

/**
 * The loop method gets called over and over again as long as the board has power
 */
void loop() {

  // Turn the LED on
  digitalWrite(BLINK_LED, HIGH);
  delay(1000);  // Pause for 1000 MS or (1 second)

  // Turn the LED off
  digitalWrite(BLINK_LED, LOW);
  delay(1000);  // Pause for 1000 MS or (1 second)
}
