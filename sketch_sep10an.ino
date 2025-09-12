void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // Built-in LED on Uno WiFi Rev2
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn LED on
  delay(200);                      // wait 1 second
  digitalWrite(LED_BUILTIN, LOW);   // turn LED off
  delay(200);                      // wait 1 second
}