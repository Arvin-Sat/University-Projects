int soundPin = A0;
int motorPin = 6;

int soundLevel = 0;
int motorLevel = 0;

char buff[20];

void setup() {

  // Define Pin Directions
  //pinMode(soundPin, INPUT);
  pinMode(motorPin, OUTPUT);

  // Initiate Output Pins
  digitalWrite(motorPin, LOW);

  Serial.begin(9600);
}

void loop() {

  /*
   *  Arduino has ADC 10 bit resolution --> 0..5V translates to 0..1023 (2^10 - 1) --> Each step is ~ 5mV
   *  Our Audio pre-amplifier module output is 0..2V range.
   *  Our envelope detection circuit has a diode in forward bias (0.6V) in its input --> Envelope detection output is in 0 .. 1.4V which translates to 0..280 
   *  So soundLevel variable will be in 0..280 range
   */
  soundLevel = analogRead(soundPin);  

  /*
   *  Arduino uses PWM to simulate analog output 
   *  PWM signal is a square wave with a fixed frequency (490Hz in Arduino) and a changing DUTY CYCLE (onTime / offTime)
   *  A 1 byte variable (0..255) translates to 0..100% duty cycle
   */

  // We need to map 0..80 soundLevel to 0..255 motorLevel
  motorLevel = soundLevel * 255 / 280;
  analogWrite(motorPin, motorLevel & 0xFF);

  delay(100);
}
