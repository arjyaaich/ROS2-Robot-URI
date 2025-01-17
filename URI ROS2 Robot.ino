
const int pinA = 2; // Encoder signal A connected to pin 2
const int pinB = 3; // Encoder signal B connected to pin 3

volatile int encoderPos = 0;  // Variable to store encoder position
volatile int direction = 0;   // 1 for clockwise, -1 for counterclockwise

// Interrupt service routine for pin A
void ISR_A() {
  // Read the state of pin B to determine the direction
  if (digitalRead(pinB) == HIGH) {
    direction = 1; // Clockwise
  } else {
    direction = -1; // Counterclockwise
  }

  encoderPos += direction;  // Update the encoder position
}

void setup() {
  // Initialize the serial monitor for output
  Serial.begin(9600);

  // Set the encoder pins as input
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  // Attach interrupts to detect changes in encoder signal A
  attachInterrupt(digitalPinToInterrupt(pinA), ISR_A, CHANGE);

  Serial.println("Motor Direction Detector");
}

void loop() {
  // Display the direction and position
  if (direction == 1) {
    Serial.println("Motor is moving Clockwise");
  } else if (direction == -1) {
    Serial.println("Motor is moving Counterclockwise");
  }
  delay(200);  // Delay for readability of the serial monitor
}
