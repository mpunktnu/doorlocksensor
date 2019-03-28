/*
 * Lock detector
 * 
 * Created by Erik Karlsson @ m.nu
 */
 
// LED pin number
#define LED_PIN     13

// button pin number
#define BTN_PIN     18

// channel number
#define ZUNO_CHANNEL_NUMBER_ONE   1

// variable to store current button state
byte lastButtonState;

// sets up the Z-Uno channels
ZUNO_SETUP_CHANNELS(ZUNO_SENSOR_BINARY(ZUNO_SENSOR_BINARY_TYPE_DOOR_WINDOW, getter));

void setup() {
 pinMode(LED_PIN, OUTPUT); // set LED pin as output
 pinMode(BTN_PIN, INPUT_PULLUP); // set button pin as input
}

void loop() {
  // sample current button state
  byte currenButtonState = digitalRead(BTN_PIN);
  
  if (currenButtonState != lastButtonState) { // if state changes
    lastButtonState = currenButtonState; // save new state
    zunoSendReport(ZUNO_CHANNEL_NUMBER_ONE); // send report over the Z-Wave to the controller
    if (currenButtonState == LOW) { // if button is pressed
      digitalWrite(LED_PIN, HIGH);  // shine the LED
    } else {                        // if button is released
      digitalWrite(LED_PIN, LOW);   // turn the LED off
    }
  }
}


// function, which returns the previously saved button state
// this function runs only once the controller asks
byte getter(){
  if (lastButtonState == 0) { // if button is pressed
    return 0xff;              // return "Triggered" state to the controller
  } else {                    // if button is released
    return 0;                 // return "Idle" state to the controller
  }
}

