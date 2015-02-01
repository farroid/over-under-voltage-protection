const byte LED_COMMON_GROUND = 4;
//const byte LED_RED = 3;
//const byte LED_GREEN = 6;
const byte LED_BLUE = 5;
const byte LED_BOARD = 13;
const byte RELAY = 12;

const short VOLT = A0;
const short DELAY = 1000; // 500ms
const short DURATION = (1000 / DELAY) * 500; // (5 minutes == 500ms * 600)

// Max Volt = 570 (~300V)
// Min Volt = 350 (~180V)
const short MIN_VOLT = 360;
const short MAX_VOLT = 570;

short wait;
bool led_state;

void setup() {
  pinMode(LED_COMMON_GROUND, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(LED_BOARD, OUTPUT);

  digitalWrite(LED_COMMON_GROUND, LOW);

  wait = 0;
  led_state = false;
  //Serial.begin(9600);
}

void switch_on() {
  analogWrite(LED_BLUE, 20);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(RELAY, HIGH);
  digitalWrite(LED_BOARD, HIGH);
}

void switch_off() {
  analogWrite(LED_BLUE, 0);
  digitalWrite(RELAY, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_BOARD, LOW);
}

void blink() {
  analogWrite(LED_BLUE, (led_state = !led_state) ? 20 : 0);
}
// the loop function runs over and over again forever
void loop() {
  // read the input on analog pin A0:
  short voltage = analogRead(VOLT);

  if (voltage >= MIN_VOLT && voltage <= MAX_VOLT) {
    if (wait < DURATION) {
      ++wait;
      blink();
    } else {
      switch_on();
    }
  } else {
    wait = 0;
    switch_off();
    analogWrite(LED_BLUE, 20);
    delay(100);
    analogWrite(LED_BLUE, 0);
    delay(100);
    analogWrite(LED_BLUE, 20);
    delay(100);
    analogWrite(LED_BLUE, 0);
    delay(1000);
  }

  //Serial.println(voltage);
  delay(DELAY); // delay in between reads for stability
}
