/*
*/

uint8_t pin_pair = 0;
uint8_t pin_cts = 19;
uint8_t pin_rts = 22;
uint8_t pin_statusLED = 13;
uint8_t pin_connectLED = 14;

unsigned long lastChange = 0;

void setup()
{
  Serial.begin(115200); // Start serial for any initial debug messages

  pinMode(pin_pair, INPUT_PULLUP);

  pinMode(pin_cts, INPUT); //Has external pullup

  pinMode(pin_rts, OUTPUT);
  digitalWrite(pin_rts, LOW);

  pinMode(pin_statusLED, OUTPUT);
  digitalWrite(pin_statusLED, LOW);

  pinMode(pin_connectLED, OUTPUT);
  digitalWrite(pin_connectLED, HIGH);
}

void loop()
{
  Serial.println("Running");
  
  if (millis() - lastChange > 1000)
  {
    lastChange = millis();
    digitalWrite(pin_statusLED, !digitalRead(pin_statusLED));
    digitalWrite(pin_connectLED, !digitalRead(pin_connectLED));
    digitalWrite(pin_rts, !digitalRead(pin_rts));
  }

  if (digitalRead(pin_cts) == LOW)
    Serial.println("CTS pressed!");

  if (digitalRead(pin_pair) == LOW)
    Serial.println("Pair pressed!");

  delay(100);

}
