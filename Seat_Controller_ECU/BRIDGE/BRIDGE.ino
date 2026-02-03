//int numberToSend = 123;  // The number you want to send

void setup() {
  // Arduino sender code
  Serial.begin(9600); 
  Serial.print("1234");  // sends '1' '2' '3'
}


void loop() {
  // Send the number as raw binary (1 byte)
  //Serial.write(numberToSend);

  // Wait a bit before sending again
 // delay(1000);
}
