#define TRIG1_PIN 10
#define ECHO1_PIN 9
#define VIBRATOR1_PIN 8

#define TRIG2_PIN 7
#define ECHO2_PIN 6
#define VIBRATOR2_PIN 5

long duration1;
int16_t distance1;
int16_t currentPeriod1;

long duration2;
int16_t distance2;
int16_t currentPeriod2;

bool currentVibrator1State = LOW;
int32_t vibrator1StartedTime = 0;

bool currentVibrator2State = LOW;
int32_t vibrator2StartedTime = 0;

int32_t currentTime;

int16_t vibrationPeriods[] = {100, 171, 214, 261, 333, -1};

void setup() {
  pinMode(VIBRATOR1_PIN, OUTPUT);
  pinMode(TRIG1_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);

  pinMode(VIBRATOR2_PIN, OUTPUT);
  pinMode(TRIG2_PIN, OUTPUT);
  pinMode(ECHO2_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Vibrator 1:
  digitalWrite(TRIG1_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG1_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1_PIN, LOW);

  duration1  = pulseIn(ECHO1_PIN, HIGH);

  distance1 = duration1 * 0.017;

  Serial.print("distance1: ");
  Serial.print(distance1);
  Serial.println(" cm");


  if(distance1 < 100) {
    currentPeriod1 = vibrationPeriods[distance1/20];
  } else if(distance1 > 105) {
    currentPeriod1 = -1;
  }
  Serial.println(currentPeriod1);

  if(currentPeriod1 == -1) {
    currentVibrator1State = LOW;
    digitalWrite(VIBRATOR1_PIN, LOW);
    vibrator1StartedTime = 0;
  } else {
    currentTime = millis();
    if(currentTime >= vibrator1StartedTime + currentPeriod1) {
      currentVibrator1State = !currentVibrator1State;
      digitalWrite(VIBRATOR1_PIN, currentVibrator1State);
      vibrator1StartedTime = currentTime;
    }
  }

  // Vibrator 2:
  digitalWrite(TRIG2_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG2_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2_PIN, LOW);

  duration2  = pulseIn(ECHO2_PIN, HIGH);

  distance2 = duration2 * 0.017;

  Serial.print("distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");


  if(distance2 < 100) {
    currentPeriod2 = vibrationPeriods[distance2/20];
  } else if(distance2 > 105) {
    currentPeriod2 = -1;
  }
  Serial.println(currentPeriod2);

  if(currentPeriod2 == -1) {
    currentVibrator2State = LOW;
    digitalWrite(VIBRATOR2_PIN, LOW);
    vibrator2StartedTime = 0;
  } else {
    currentTime = millis();
    if(currentTime >= vibrator2StartedTime + currentPeriod2) {
      currentVibrator2State = !currentVibrator2State;
      digitalWrite(VIBRATOR2_PIN, currentVibrator2State);
      vibrator2StartedTime = currentTime;
    }
  }

}
