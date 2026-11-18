#include <Servo.h>
Servo john;

double avg;
double avgmod;
int arr[5] = {0};
bool check = false;
bool closed = false;

void setup() {
  Serial.begin(9600);
  john.attach(8);
  int val;
  int sum = 0;
  for (int i = 0; i < 1000; ++i) {
    val = analogRead(A0);
    sum += static_cast<double>(val);
    delay(1);
  }
  avg = sum / 1000.0;
  avgmod = avg * 1.5;
  Serial.println("Ready");
}

void loop() {
  int val = analogRead(A0);
  int sum = val;
  for (int i = 0; i < 4; ++i) {
    arr[i] = arr[i + 1];
    sum += arr[i];
  }
  arr[4] = val;
  int avgl = sum / 5;
  if (avgl > avgmod && !check) {
    check = true;
    if (closed) {
      Serial.println("Opening...");
      john.write(0);
      avgmod = avg * 1.4;
    }
    else {
      Serial.println("Closing...");
      john.write(180);
      avgmod = avg * 1.5;
    }
    closed = !closed;
  }
  else if (avgl < avgmod && check) {
    check = false;
    Serial.println("ready");
  }
  delay(50);
}
