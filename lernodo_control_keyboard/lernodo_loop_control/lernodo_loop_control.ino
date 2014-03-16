void setup() {
 Serial.begin(9600);
 Mouse.begin();
 Keyboard.begin();
}


void loop() {
  // use serial input to control the mouse:

     Keyboard.press(KEY_LEFT_ARROW);
     delay(2000);
      Keyboard.releaseAll();
      delay(1000);
}
