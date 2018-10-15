#include "IRremote.h"

const int BLINK_LED = 10;   // Our LED is connected to pin 10
const int FADE_AMOUNT = 5;  // How quickly to fade the LED by
const int IR_RECEIVER = 11; // Our IR receiver will be connected to GPIO Pin 11

int brightness = 0; // Variable to hold the current brightness of the LED start it at 0 or completely off

IRrecv irReciever(IR_RECEIVER); // create instance of 'irrecv'
decode_results irResults;       // create instance of 'decode_results'

/**
 * The setup method gets called only once at the beginning of the application
 */
void setup() {
  pinMode(BLINK_LED, OUTPUT); // Before we can writ the LED we have to open this PIN for output
  irReciever.enableIRIn();    // Startup the IR Receiver
}

/**
 * Increases the brightness of the LED
 */
void increaseBrightness() {

  // Add the fade amount to the brightness to increase it
  brightness += FADE_AMOUNT;

  // The LED can only go up to 255 (the maximum value for an 8 bit register)
  if (brightness + FADE_AMOUNT > 255) {
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
  brightness -= FADE_AMOUNT;

  // The LED can only go down to 0
  if (brightness - FADE_AMOUNT < 0) {
    brightness = 0;
  }

  // Pulse the LED at the given brightness
  analogWrite(BLINK_LED, brightness);
}

/**
 * Turns the LED On or off
 * If it's on already it will turn it off..
 * If it's completely off it will turn it on at full brightness
 */
void toggleLED() {
  if (brightness > 0) {
    brightness = 0;
  }
  else {
    brightness = 255;
  }
  analogWrite(BLINK_LED, brightness);
}

/**
 * This function translates a code received from the remote to actual
 * application logic that we want to perform within our application.
 */
void translateIR() {
  switch(irResults.value) {
    case 0xFFA25D: // POWER
      toggleLED();
      break;
    case 0xFF629D:   // VOL+
      increaseBrightness();
      break;
    case 0xFFA857:   // VOL-
      decreaseBrightness();
      break;
    case 0xFFE21D:   // FUNC/STOP
    case 0xFF22DD:   // FAST BACK
    case 0xFF02FD:   // PAUSE
    case 0xFFC23D:   // FAST FORWARD
    case 0xFFE01F:   // DOWN
    case 0xFF906F:   // UP
    case 0xFF9867:   // EQ
    case 0xFFB04F:   // ST/REPT
    case 0xFF6897:   // 0
    case 0xFF30CF:   // 1
    case 0xFF18E7:   // 2
    case 0xFF7A85:   // 3
    case 0xFF10EF:   // 4
    case 0xFF38C7:   // 5
    case 0xFF5AA5:   // 6
    case 0xFF42BD:   // 7
    case 0xFF4AB5:   // 8
    case 0xFF52AD:   // 9
    case 0xFFFFFFFF: // REPEAT
    default: 
      break;  // Do nothing
  }

  delay(100); // Pause for a little bit to "debounce" the remote button press
}


/**
 * The loop method gets called over and over again as long as the board has power
 */
void loop() {
  if (irReciever.decode(&irResults)) {
    translateIR();
    irReciever.resume();
  }
}
