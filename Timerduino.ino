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

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  readInputs();

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
    setLedForStatus();
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
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
}

void disableAllLeds() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void setLedForStatus() {
  if (oneMinActivated) {
    digitalWrite(8, HIGH);
  }

  if (twoMinActivated) {
    digitalWrite(9, HIGH);
  }

  if (fourMinActivated) {
    digitalWrite(10, HIGH);
  }

  if (eightMinActivated) {
    digitalWrite(11, HIGH);
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

  tone(7, 3600);
  delay(70);

  noTone(7);
  delay(70);

  tone(7, 3600);
  delay(70);

  noTone(7);
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
