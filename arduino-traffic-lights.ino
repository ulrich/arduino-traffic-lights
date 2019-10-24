/**
 * Get the value returns by the KY-038
 * 
 * Inspired by jenfoxbot <jenfoxbot@gmail.com>
 */
const int sampleTime = 50; 

int mic = A0;
int micOut;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int micOutput = findPTPAmp();

  if (micOutput > 20) {
    digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
}

// find the Peak-to-Peak Amplitude Function
int findPTPAmp() {
  // time variables to find the peak-to-peak amplitude
  unsigned long startTime = millis();  // Start of sample window
  unsigned int PTPAmp = 0;

  // signal variables to find the peak-to-peak amplitude
  unsigned int maxAmp = 0;
  unsigned int minAmp = 1023;

  // find the max and min of the mic output within the 50 ms timeframe
  while(millis() - startTime < sampleTime) {
    micOut = analogRead(mic);
    // prevent erroneous readings
    if (micOut < 1023) {
      if (micOut > maxAmp) {
        // save only the max reading
        maxAmp = micOut;
      } else if (micOut < minAmp) {
        minAmp = micOut; //save only the min reading
      }
    }
  }

  // (max amp) - (min amp) = peak-to-peak amplitude
  PTPAmp = maxAmp - minAmp;
  // debugging
  Serial.println(PTPAmp, DEC); 

  // Convert ADC into voltage
  double micOut_Volts = (PTPAmp * 3.3) / 1024;
  // debugging
  //Serial.println(micOut_Volts); 

  return PTPAmp;   
}
