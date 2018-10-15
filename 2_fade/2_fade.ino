const int BLINK_LED = 10; // Our LED is connected to pin 10
const int fadeAmount = 5; // How quickly to fade the LED by

int brightness = 0; // Variable to hold the current brightness of the LED start it at 0 or completely off
int direction = 1; // Variable to use for increasing the brightness or decreasing it (0 = down, 1 = up)

/**
 * The setup method gets called only once at the beginning of the application
 */
void setup() {
  // Before we can writ the LED we have to open this PIN for output
  pinMode(BLINK_LED, OUTPUT);
}

/**
 * Increases the brightness of the LED
 */
void increaseBrightness() {

  // Add the fade amount to the brightness to increase it
  brightness += fadeAmount;

  // The LED can only go up to 255 (the maximum value for an 8 bit register)
  if (brightness + fadeAmount > 255) {
    brightness = 255;
  }

  // Pulse the LED at the given brightness
  analogWrite(BLINK_LED, brightness);
}


/**
 * Increases the brightness of the LED
 */
void decreaseBrightness() {

  // Subtract the fade amount from the brightness to decrease it
  brightness -= fadeAmount;

  // The LED can only go down to 0
  if (brightness - fadeAmount < 0) {
    brightness = 0;
  }

  // Pulse the LED at the given brightness
  analogWrite(BLINK_LED, brightness);
}

/**
 * The loop method gets called over and over again as long as the board has power
 */
void loop() {

  if (direction == 1 && brightness >= 255) {
    direction = 0;
  }
  else if (direction == 0 && brightness <= 0) {
    direction = 1;
  }

  if (direction == 1) {
    increaseBrightness();
  }
  else {
    decreaseBrightness();
  }

  // Wait for 30 ms so we can see it slowly fade up or down
  delay(30);
}
