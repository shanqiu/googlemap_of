const int left_pin=6;
const int right_pin=7;
const int up_pin=8;
const int down_pin=9;

int status_left=0;
int status_right=0;
int status_up=0;
int status_down=0;

void setup() {
 Serial.begin(9600);
 Mouse.begin();
 Keyboard.begin();
 pinMode(left_pin,INPUT);
 pinMode(right_pin,INPUT);
 pinMode(up_pin,INPUT);
 pinMode(down_pin,INPUT);
}


void loop() {
  // use serial input to control the mouse:
  status_left=digitalRead(left_pin);
  status_right=digitalRead(right_pin);
  status_up=digitalRead(up_pin);
  status_down=digitalRead(down_pin);
  Serial.println(status_left);
    if(status_left){
     Keyboard.press(KEY_LEFT_ARROW);
     delay(2000);
     Keyboard.releaseAll();
     delay(2000);
    }
    else if(status_right){
     Keyboard.press(KEY_RIGHT_ARROW);
     delay(2000);
     Keyboard.releaseAll();
     delay(2000);
    }
    else if(status_up){
     Keyboard.press(KEY_UP_ARROW);
     delay(2000);
     Keyboard.releaseAll();
     delay(2000);
    }
    else if(status_down){
     Keyboard.press(KEY_DOWN_ARROW);
     delay(2000);
     Keyboard.releaseAll();
     delay(2000);
    }
    else{
     Keyboard.releaseAll();
    }
delay(100);
}
