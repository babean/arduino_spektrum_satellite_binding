#define         Bind_pin     D1
#define         Rx_PowerPin  D0
#define         numPulses    9
#define         pulseLength  116
/**
 * Change the number of pulses according to your setup:
 * 2 low pulses: DSM2 1024/22ms
 * 4 low pulses: DSM2 2048/11ms
 * 6 low pulses: DSMX 22ms
 * 8 low pulses: DSMX 11ms
 */
uint32_t mytime;

void setup() {
  pinMode(Rx_PowerPin, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);
}

void loop() {
  digitalWrite(Rx_PowerPin, HIGH); // power up receiver
  pinMode(Bind_pin, INPUT_PULLDOWN );
  if (digitalRead(Bind_pin) == LOW) {
    mytime = millis();
    while(mytime+10000 > millis()) { // wait at most 10 second for TxPin to become high
      if(digitalRead(Bind_pin) == HIGH) {
        pinMode(Bind_pin, OUTPUT);
        pinSetFast(Bind_pin);
        digitalWrite(D7, LOW);
        SpektrumBind(); // bring the receiver into binding mode by sending a sequence of low pulses
        while(1) Particle.process(); // assume everything worked fine and stay in endless loop
      }
    }
  }
  digitalWrite(Rx_PowerPin, LOW); // shut down receiver
}

void SpektrumBind(void)
{
  ATOMIC_BLOCK() {
    delay(72);
        for (int i=0;i<numPulses;i++) {
            pinResetFast(Bind_pin);
            delayMicroseconds(pulseLength);
            pinSetFast(Bind_pin);
            delayMicroseconds(pulseLength);
            }
    }
  delay(245);
  pinMode(Bind_pin, INPUT);
}
