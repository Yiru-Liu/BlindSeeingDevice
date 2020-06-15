#define TRIG1_PIN 10
#define ECHO1_PIN 9
#define VIBRATOR1_PIN 8

long duration1;
int16_t distance1;
int16_t currentPeriod1;

bool currentVibrator1State = LOW;
int32_t vibrator1StartedTime = 0;

int32_t currentTime;

int16_t vibrationPeriods[] = {100, 171, 214, 261, 333, -1};

void setup() {
  pinMode(VIBRATOR1_PIN, OUTPUT);
  pinMode(TRIG1_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
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

}
