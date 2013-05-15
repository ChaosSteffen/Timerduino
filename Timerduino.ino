#include <SimpleTimer.h>

// There must be one global SimpleTimer object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer timer;

int oneMin = LOW;
int twoMin = LOW;
int fourMin = LOW;
int eightMin = LOW;

boolean oneMinActivated = false;
boolean twoMinActivated = false;
boolean fourMinActivated = false;
boolean eightMinActivated = false;

int timerId = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  readInputs();
  detectButtonPress();
  setLedForStatus();

  timer.run();
}

void detectButtonPress() {
  if (oneMin == HIGH) {
    oneMinActivated = true;
  }

  if (twoMin == HIGH) {
    twoMinActivated = true;
  }

  if (fourMin == HIGH) {
    fourMinActivated = true;
  }

  if (eightMin == HIGH) {
    eightMinActivated = true;
  }

  if (oneMin == HIGH | twoMin == HIGH | fourMin == HIGH | eightMin == HIGH) {
    timer.deleteTimer(timerId);
    timerId = timer.setTimeout(calculateTime(), alarm);
  }

  timer.run();
}

double calculateTime() {
  double time = 0.0;

  if (oneMinActivated) {
    time = time + 60000.0;
  }

  if (twoMinActivated) {
    time = time + 120000.0;
  }

  if (fourMinActivated) {
    time = time + 240000.0;
  }

  if (eightMinActivated) {
    time = time + 480000.0;
  }

  return time;
}

void enableAllLeds() {
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

void disableAllLeds() {
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void setLedForStatus() {
  if (oneMinActivated) {
    analogWrite(9, 0); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 0); // BLUE
    digitalWrite(7, HIGH);
    delay(1);
    digitalWrite(7, LOW);
    analogWrite(9, 255); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 255); // BLUE
  } else {
    delay(1);
  }

  if (twoMinActivated) {
    analogWrite(9, 0); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 0); // BLUE
    digitalWrite(8, HIGH);
    delay(1);
    digitalWrite(8, LOW);
    analogWrite(9, 255); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 255); // BLUE
  } else {
    delay(1);
  }

  if (fourMinActivated) {
    analogWrite(9, 0); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 0); // BLUE
    digitalWrite(12, HIGH);
    delay(1);
    digitalWrite(12, LOW);
    analogWrite(9, 255); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 255); // BLUE
  } else {
    delay(1);
  }

  if (eightMinActivated) {
    analogWrite(9, 0); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 0); // BLUE
    digitalWrite(13, HIGH);
    delay(1);
    digitalWrite(13, LOW);
    analogWrite(9, 255); // RED
    analogWrite(10, 255); // GREEN
    analogWrite(11, 255); // BLUE
  } else {
    delay(1);
  }
}

void readInputs() {
  oneMin = digitalRead(2);
  twoMin = digitalRead(3);
  fourMin = digitalRead(4);
  eightMin = digitalRead(5);
}

void alarm() {
  oneMinActivated = false;
  twoMinActivated = false;
  fourMinActivated = false;
  eightMinActivated = false;

  readInputs();
  enableAllLeds();

  tone(6, 3600);
  delay(70);

  noTone(6);
  delay(70);

  tone(6, 3600);
  delay(70);

  noTone(6);
  delay(200);

  disableAllLeds();
  delay(500);

  if (oneMin == HIGH || twoMin == HIGH || fourMin == HIGH || eightMin == HIGH) {
    delay(1000);
  } 
  else {
    alarm();
  }
}


