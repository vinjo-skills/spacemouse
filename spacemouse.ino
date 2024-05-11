#include <BleMouse.h>
const int DEADZONE = 7;  // Adjust this value based on your joystick
// Define the pins for the joystick module
const int VRX_PIN = D0;  // X-axis analog pin
const int VRY_PIN = D1;  // Y-axis analog pin
const int SW_PIN = D2;   // Switch/Button pin
int state = HIGH;
int ledstate = LOW;
BleMouse bleMouse;

void setup() {
  Serial.begin(115200);
  bleMouse.begin();
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  int x = analogRead(VRX_PIN);
  int y = analogRead(VRY_PIN);
  int sw = digitalRead(SW_PIN);
  int mouse_x = map(x, 4, 4095, -10, 10);  // Adjust sensitivity as needed
  int mouse_y = map(y, 2, 4095, -10, 10);  // Adjust sensitivity as needed


  if (mouse_x == 7) {
    mouse_x = 0;
  }

  if (mouse_y == 7) {
    mouse_y = 0;
  }

  // Move the mouse pointer based on joystick values
  if (mouse_x != 0 || mouse_y != 0) {
    bleMouse.move(mouse_x, mouse_y, 0);
  }

  //Check if the joystick button is pressed
  if (sw == LOW) {
    if (ledstate == LOW) {
      ledstate = HIGH;
    } else {
      ledstate = LOW;
    }
    if (ledstate == HIGH) {
      bleMouse.press(MOUSE_RIGHT);
      Serial.print("Mouse Right pressed.");
      Serial.print("\t");
    } else {
      bleMouse.release(MOUSE_RIGHT);
      Serial.print("Mouse Right released.");
      Serial.print("\t");
    }
  }

  Serial.print("X:");
  Serial.print(x);
  Serial.print(" ");
  Serial.print("Y:");
  Serial.print(y);
  Serial.print("\t");
  Serial.print("X-Mouse:");
  Serial.print(mouse_x);
  Serial.print(" ");
  Serial.print("Y-Mouse:");
  Serial.print(mouse_y);
  Serial.print("Y-Mouse:");
  Serial.print(mouse_y);
  Serial.print("\t");
  Serial.print("BUTTON STATE =>");
  Serial.print(sw);
  Serial.print(" ");
  Serial.print("PREV STATE =>");
  Serial.print(ledstate);
  Serial.println();
  delay(10);
}