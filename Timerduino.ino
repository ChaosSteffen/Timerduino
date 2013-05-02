#include <SimpleTimer.h>

// There must be one global SimpleTimer object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer timer;

int oneMin = LOW;
int twoMin = LOW;
int threeMin = LOW;
int fourMin = LOW;

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
  // put your main code here, to run repeatedly: 
  
  oneMin = digitalRead(2);
  twoMin = digitalRead(3);
  threeMin = digitalRead(4);
  fourMin = digitalRead(5);

  if (oneMin == HIGH) {
    disableAllLeds();
    digitalWrite(8, oneMin);
    
    timer.deleteTimer(timerId);
    timerId = timer.setTimeout(10000, alarm);
  }
  
  if (twoMin == HIGH) {
    disableAllLeds();
    digitalWrite(9, twoMin);
    
    timer.deleteTimer(timerId);
    timerId = timer.setTimeout(120000, alarm);
  }

  if (threeMin == HIGH) {
    disableAllLeds();
    digitalWrite(10, threeMin);
    
    timer.deleteTimer(timerId);
    timerId = timer.setTimeout(180000, alarm);
  }

  if (fourMin == HIGH) {
    disableAllLeds();
    digitalWrite(11, fourMin);
    
    timer.deleteTimer(timerId);
    timerId = timer.setTimeout(240000, alarm);
  }
  
  timer.run();
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


void alarm() {
  oneMin = digitalRead(2);
  twoMin = digitalRead(3);
  threeMin = digitalRead(4);
  fourMin = digitalRead(5);

  enableAllLeds();

  tone(7, 3600);
  delay(70);

  noTone(7);
  delay(70);
  
  tone(7, 3600);
  delay(70);

  noTone(7);
  delay(700);
  
  disableAllLeds();
  
  if (oneMin == HIGH || twoMin == HIGH || threeMin == HIGH || fourMin == HIGH) {
    delay(1000);
  } else {
    alarm();
  }
}
