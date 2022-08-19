#define LED 9
#define threshold 200
#define LDR A1

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  int brightness = analogRead(LDR);
  if (brightness > threshold) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
}
