
#include <Servo.h>

Servo myServo;

const int CLK = 2;
const int DT = 3;
const int SW = 4;

const int SERVO_PIN = 9;

int angle = 90;
int lastCLK;

bool lastButtonState = HIGH;
unsigned long lastButtonTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  myServo.attach(SERVO_PIN);
  myServo.write(angle);

  lastCLK = digitalRead(CLK);

  Serial.println("Rotary Encoder Servo Controller");
  Serial.println("Starting angle: 90");
}

void loop() {
  int currentCLK = digitalRead(CLK);

  if (currentCLK != lastCLK && currentCLK == LOW) {

    if (digitalRead(DT) != currentCLK) {
      angle += 5;
    } else {
      angle -= 5;
    }

    angle = constrain(angle, 0, 180);

    myServo.write(angle);

    Serial.print("Servo Angle: ");
    Serial.println(angle);
  }

  lastCLK = currentCLK;

  bool buttonState = digitalRead(SW);

  if (buttonState == LOW && lastButtonState == HIGH &&
      millis() - lastButtonTime > 200) {

    angle = 90;
    myServo.write(angle);

    Serial.println("Reset to 90 degrees");

    lastButtonTime = millis();
  }

  lastButtonState = buttonState;
}
