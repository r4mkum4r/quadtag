#include "configuration.h"
#include "constants.h"
#include "notes.h"

// Value as read from the PWM input
int pwm_value;

void setup()  {
  // Setup pins
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LASER, OUTPUT);
  pinMode(PIN_PWM, INPUT);

  // Startup sound
  playNote(NOTE_E0, 125);
  playNote(NOTE_A0, 125);
}

void loop()  {
  // @todo check if we're being hit

  // Read PWM input value
  pwm_value = pulseIn(PIN_PWM, HIGH);

  // Check if we can fire
  if (
    // @todo don't fire if we're being hit
    pwm_value > PWM_THRESHOLD
  ) {
    fire();
  }
}

/**
  Fire the IR "laser" and beep
*/
void fire() {
  Serial.println("Firing!");

  // @todo send data instead of just turning on
  analogWrite(PIN_BUZZER, BUZZER_OUTPUT);
  digitalWrite(PIN_LASER, HIGH);
  delay(TIME_FIRE);

  analogWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LASER, LOW);
  delay(TIME_FIRE_WAIT);
}

/**
  Flash the indicator LED and beep

  @param <short> times
    The number of times to flash
*/
void indicate(short times) {
  for (short i = 0; i < times; i++) {
    analogWrite(PIN_BUZZER, BUZZER_OUTPUT);
    digitalWrite(PIN_LED, HIGH);
    delay(TIME_INDICATE);

    analogWrite(PIN_BUZZER, LOW);
    digitalWrite(PIN_LED, LOW);
    delay(TIME_INDICATE_WAIT);
  }
}

/**
  Play the specified tone for the specified duration

  @param <int> tone
    The tone to play in Hz + NOTE_BASE
  @param <int> duration
    The time to play the tone for in milliseconds
*/
void playNote(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(PIN_BUZZER, HIGH);
    delayMicroseconds(tone);
    digitalWrite(PIN_BUZZER, LOW);
    delayMicroseconds(tone);
  }
  delay(TIME_PAUSE);
}
