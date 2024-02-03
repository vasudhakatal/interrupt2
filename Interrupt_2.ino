const int tempPin = A0;  // Analog pin for temperature sensor
const int Blueled = 2;    // Digital pin for LED
const int Yellowled = 3;
const int motionPin = 4;  // Digital pin for ultrasonic sensor

int tempValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Blueled, OUTPUT);
  pinMode(Yellowled, OUTPUT);
  pinMode(motionPin, INPUT);  // Set ultrasonicPin as an input
  attachInterrupt(digitalPinToInterrupt(tempPin), temperatureChangeISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motionPin), motionISR, CHANGE);
}

void loop() 
{
  temperatureChangeISR();
  motionISR ();
}

void temperatureChangeISR() 
{
  tempValue = analogRead(tempPin);

  // Performing the calculation (tempValue)/6.12 to adjust the temperature
  float adjustedTemp = tempValue / 6.12;
  Serial.print("Temperature: ");
  Serial.print(adjustedTemp); 
  delay (500);
  
  if (adjustedTemp > 25) 
  {
    digitalWrite(Blueled, HIGH);
  	Serial.println(" LED ON (Interrupted)");
  } 
  else 
  {
    digitalWrite(Blueled, LOW);  
    Serial.println(" Not Interrupted");
  }
}

void motionISR() {
  int motionDetected = digitalRead(motionPin);  

  if (motionDetected == HIGH) {
    digitalWrite(Yellowled, HIGH);
    Serial.println("Motion detected!(Interrupted");
  } else {
    digitalWrite(Yellowled, LOW);
    delay(500);
  }
}