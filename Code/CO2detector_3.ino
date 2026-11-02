#include <MQ135.h>

#define PIN_MQ135  0
#define GREEN_PIN1 8
#define GREEN_PIN2  4
#define YELLOW_PIN1 6
#define YELLOW_PIN2 9
#define RED_PIN1    11
#define RED_PIN2    12
#define PIN_NOISE  3


void printValues();

const int maxCount = 10;
int count = 0;
int noisecount = 0;
bool noiseActive = false;

float ppm;

MQ135 co2_sensor(PIN_MQ135);


void setup() {
  pinMode(GREEN_PIN1, OUTPUT);
  pinMode(YELLOW_PIN1, OUTPUT);
  pinMode(RED_PIN1, OUTPUT);
  pinMode(GREEN_PIN2, OUTPUT);
  pinMode(YELLOW_PIN2, OUTPUT);
  pinMode(RED_PIN2, OUTPUT);
  pinMode(PIN_NOISE, OUTPUT);

    Serial.begin(9600);
  co2_sensor.setR0(400);
  noisecount = 0;
}


void loop() {
  if (count >= maxCount || count < 0) {
    ppm = co2_sensor.getCO2();

    count = 0;
    if (ppm < 1000000) {
      noiseActive = false;
      noisecount = 0;
      digitalWrite(GREEN_PIN1, HIGH);
      digitalWrite(GREEN_PIN2, HIGH);
      digitalWrite(YELLOW_PIN1, LOW);
      digitalWrite(RED_PIN1, LOW);
      digitalWrite(YELLOW_PIN2, LOW);
      digitalWrite(RED_PIN2, LOW);
     }
    else if (ppm <= 1600000) {
      noiseActive = false;
      noisecount = 0;
     digitalWrite(GREEN_PIN1, LOW);
      digitalWrite(GREEN_PIN2, LOW);
      digitalWrite(YELLOW_PIN1, HIGH);
      digitalWrite(YELLOW_PIN2, HIGH);
      digitalWrite(RED_PIN1, LOW);
      digitalWrite(RED_PIN2, LOW);
    }
    else {
      noiseActive = true;
      digitalWrite(GREEN_PIN1, LOW);
      digitalWrite(GREEN_PIN2, LOW);
      digitalWrite(YELLOW_PIN1, LOW);
      digitalWrite(YELLOW_PIN2, LOW);
      digitalWrite(RED_PIN1, HIGH);
      digitalWrite(RED_PIN2, HIGH);
    }

    printValues();
  }
  delay(100);
  if (noiseActive && noisecount < 5) {
    noisecount += 1;
    digitalWrite(PIN_NOISE, HIGH);
  }
  else {
    digitalWrite(PIN_NOISE, 0);
  }

  delay(100);
  count++;
} 



void looptest() {
   digitalWrite(GREEN_PIN1, HIGH);
  digitalWrite(YELLOW_PIN1, LOW);
  digitalWrite(RED_PIN1, LOW);
  digitalWrite(GREEN_PIN2, LOW);
  digitalWrite(YELLOW_PIN2, LOW);
  digitalWrite(RED_PIN2, LOW);
  delay(1000); 

  
   digitalWrite(GREEN_PIN1, LOW);
  digitalWrite(YELLOW_PIN1, LOW);
  digitalWrite(RED_PIN1, LOW);
  digitalWrite(GREEN_PIN2, HIGH);
  digitalWrite(YELLOW_PIN2, LOW);
  digitalWrite(RED_PIN2, LOW);
  delay(1000);

 digitalWrite(GREEN_PIN1, LOW);
  digitalWrite(YELLOW_PIN1, HIGH);
  digitalWrite(RED_PIN1, LOW);
  digitalWrite(GREEN_PIN2, LOW);
  digitalWrite(YELLOW_PIN2, LOW);
  digitalWrite(RED_PIN2, LOW);
  delay(1000);

 digitalWrite(GREEN_PIN1, LOW);
  digitalWrite(YELLOW_PIN1, LOW);
  digitalWrite(RED_PIN1, LOW);
  digitalWrite(GREEN_PIN2, LOW);
  digitalWrite(YELLOW_PIN2, HIGH);
  digitalWrite(RED_PIN2, LOW);
  delay(1000);

 digitalWrite(GREEN_PIN1, LOW);
  digitalWrite(YELLOW_PIN1, LOW);
  digitalWrite(RED_PIN1, HIGH);
  digitalWrite(GREEN_PIN2, LOW);
  digitalWrite(YELLOW_PIN2, LOW);
  digitalWrite(RED_PIN2, LOW);
  delay(1000);

   digitalWrite(GREEN_PIN1, LOW);
  digitalWrite(YELLOW_PIN1, LOW);
  digitalWrite(RED_PIN1, LOW);
  digitalWrite(GREEN_PIN2, LOW);
  digitalWrite(YELLOW_PIN2, LOW);
  digitalWrite(RED_PIN2, HIGH);
  delay(1000);

    digitalWrite(GREEN_PIN1, LOW);
  digitalWrite(YELLOW_PIN1, LOW);
  digitalWrite(RED_PIN1, LOW);
  digitalWrite(GREEN_PIN2, LOW);
  digitalWrite(YELLOW_PIN2, LOW);
  digitalWrite(RED_PIN2, LOW);
    digitalWrite(PIN_NOISE, 0);

  delay(1000);
      digitalWrite(PIN_NOISE, HIGH);

  delay(1000);
      digitalWrite(PIN_NOISE, 0);

}

void printValues() {
  Serial.print("ppm: ");
  Serial.println(ppm);
}
