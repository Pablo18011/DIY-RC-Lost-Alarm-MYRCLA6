

// Read the analog value of an external voltage at the AREF pin.
//
// Warning: Do no use this sketch !
//
// This sketch is when an external voltage is supplied to the AREF pin.
// That is a very rare situation.
//
// Warning: using an external voltage at AREF might cause an
// internal shortcut when analogRead() is called before the
// reference is set to external.
//

void setup() {
  Serial.begin (9600);
  Serial.println ("\nRead voltage at AREF pin");

  analogReference (EXTERNAL);
}

void loop() {
  float voltage = readAref();
  Serial.println(voltage); 
  delay(1000);
}


//
// Function readAref
//
// Reads AREF (when external voltage is supplied).
// When the AREF pin is open, a value of 1.1V is returned.
// This function is only valid for a voltage at AREF of 1.1 to 5V.
//
// The calculations can be translated for integers to prevent
// use of float.
// Only for the Arduino Uno, Nano, Pro Micro at this moment.
// Experimental, no guarantees.
// public domain
//
float readAref (void) {
  float volt;

#if defined (__AVR_ATmega8__)
#elif defined (__AVR_ATmega168__)
#elif defined (__AVR_ATmega168A__)
#elif defined (__AVR_ATmega168P__)
#elif defined (__AVR_ATmega328__)
#elif defined (__AVR_ATmega328P__)

  // set reference to AREF, and mux to read the internal 1.1V
  // REFS1 = 0, REFS0 = 0, MUX3..0 = 1110
  ADMUX = _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
 
  // Enable the ADC
  ADCSRA |= _BV(ADEN);

  // Wait for voltage to become stable after changing the mux.
  delay(20);

  // Start ADC
  ADCSRA |= _BV(ADSC);

  // wait for the ADC to finish
  while (bit_is_set(ADCSRA,ADSC));

  // Read the ADC result
  // The 16-bit ADC register is 'ADC' or 'ADCW'
  unsigned int raw = ADCW;

  // Calculate the Aref.
  volt = 1.1 / (float) raw * 1024.0;

#elif defined (__AVR_ATmega32U4__)
#elif defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
#endif


  // Try to return to normal.
  analogReference(EXTERNAL);
  analogRead(A0);            // the mux is set, throw away ADC value
  delay(20);                 // wait for voltages to become stable

  return volt;
}
