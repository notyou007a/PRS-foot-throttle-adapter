/*************
 * 
 *  This code reads a throttle input from a resistive foot throttle
 *  (resistive throttle not compatible with hall-effect controller)
 *  and outputs a PWM (analog) signal for throttle that is compatible
 * 
 * ***********
 */

//#define ENABLE_DEBUG // Comment out for no debug / in for serial debug.
#ifdef ENABLE_DEBUG
  #define DEBUG_PRINT_VARIABLE(x) \
    Serial.print(#x); \
    Serial.print(" = "); \
    Serial.print(x); \
    Serial.print("\r\n")
  #define DEBUG_PRINT_RAW(x)
    Serial.print(x)
#else
  #define DEBUG_PRINT_VARIABLE(x) {}
  #define DEBUG_PRINT_RAW(x) {}
#endif

// Definitions

// Physical GPIO pins: 
int controller = 0; // controller digital output pin 
int pedal = 1;  // gas pedal pot pin; trinket GPIO #2 is called 1
int pedal_failsafe = 3; // not implemented yet, but to be soldered for

// Vars:
int timer = 5;      // higher == longer delay.
int Value;

const int cells = 6;
int avg[cells];  // array for averaging the throttle position -- noise reduction.
int pos;      // array position

void setup() {
  Serial.begin(9600);  // debugging
  for (int i = 0; i < cells; i++) {
    avg[i] = 0;
  }
}

void loop() {
  Value = analogRead(pedal);      // read value from gas pedal
    DEBUG_PRINT_VARIABLE(Value)
  Value = shift(Value);           // shift the value from the pedal range to the controller range.
  Value = averageFunct(Value);              // take the average of the last "count" reads
  Value = cutoff(Value);          // make sure the value is a positive number
  DEBUG_PRINT_VARIABLE(Value)
  analogWrite(controller, Value); // write value to controller 
  delay(timer);                   // for stability
    //Serial.println();
}

int shift(int var) { // shift the value from the pedal range to the controller range.
  int shifted = map(var, 0, 1023, -135, 2220);
  DEBUG_PRINT_VARIABLE(shifted)
  return shifted;
}

int averageFunct(int var) {
  int total = 0;
  int average = 0;
  avg[pos] = var;        // write the current throttle value to the next cell in the array.
  for (int i = 0; i <= cells; i++) {
    total = total + i;   // take the sum of the array
  }
  pos++;                 // increment the position
  if (pos >= cells){
    pos = 0;             // and wrap around successfully
  }
  DEBUG_PRINT_VARIABLE(total);
  average = (total/cells);
  DEBUG_PRINT_VARIABLE(average);
  return (avg);  // return the average
}

int cutoff(int var) {
  if (var <= 0) {
    var = 0;
  }
  return var;
}
