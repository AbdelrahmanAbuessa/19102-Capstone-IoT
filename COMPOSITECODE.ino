const int led = 8;

// -- ULTRASONIC INITIATE --
int currentPeople = 0;
bool people = false;
int distIN[] = {4,5}; // a[0] => echo, a[1] => trig
int distOUT[] = {6,7};
int distIN_Initial; // Initial reading of sensor
int distOUT_Initial;
String sequence = "";
int timeoutCounter = 0;

// -- LDR INITIATE --
const int ldrA = A1;
const int ldrB = A2;

// -- MQ2 + SERVO INITIATE --
#include <Servo.h> // Implement servo functions
Servo servo; // Define the servo
const int MQ2 = A0;
int gasValue = 0;

// -- DHT11 INITIATE --
#include <DHT11.h> // Implement DHT functions
DHT11 dhtIN(2); // Define DHT pin
DHT11 dhtOUT(3); // Define DHT pin

// -------------------------------------------------------------------------------------

// -- SETUP --
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  // -- ULTRASONIC SETUP --
  delay(500);
  distIN_Initial = measureDistance(distIN);
  distOUT_Initial = measureDistance(distOUT);
  pinMode(ldrA, INPUT);
  pinMode(ldrB, INPUT);

  // -- MQ2 + SERVO SETUP --
  servo.attach(9);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

// -- LOOP --
void loop() {
  // -- Measure Distance --
  int distINVal = measureDistance(distIN);
  int distOUTVal = measureDistance(distOUT);
  
  people = measurePresence(distINVal, distIN_Initial, distOUTVal, distOUT_Initial);

  // -- Measure Light Intensity --
  int lightIntensity = measureLight(ldrA, ldrB);
  
  // -- Measure Gas Leackage --
  bool gasPresence = measureGas(MQ2);

  // -- Activate Servo --
  activateServo(gasPresence);

  // -- Activate Lights --
  activateLight(led, gasPresence, lightIntensity, people);  

  // -- Measure Temperature Difference --
  int tempIN = dhtIN.readTemperature();
  int tempOUT = dhtOUT.readTemperature();
  Serial.println(tempOUT - tempIN);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------

// -- Measure Ultrasonic --
int measureDistance(int a[]) {
  pinMode(a[0], INPUT);
  pinMode(a[1], OUTPUT);
  digitalWrite(a[1], LOW);
  delay(2);
  digitalWrite(a[1], HIGH);
  delay(10);
  digitalWrite(a[1], LOW);
  long duration = pulseIn(a[0], HIGH);
  return duration / 29 / 2;
}

// -- Measure Light Intensity --
int measureLight(int a, int b) {
  int valA = analogRead(a);
  int valB = analogRead(b);
  int avg = valA + valB;
  avg = avg / 2;
  return avg;
}

// -- Measure Gas Purity --
int measureGas(int pin) {
  gasValue = analogRead(pin);
  if (gasValue >= 300) {
    return true;
  } else {
    return false;
  }
}

// -- Manipulate Ultrasonic to measure presence of people --
int measurePresence(int inA, int inO, int outA, int outO) {
  if (inA < inO - 15 && sequence.charAt(0) != '1') {
    sequence += "1";
  } else if (outA < outO - 15 && sequence.charAt(0) != '2') {
    sequence += "2";
  }
  
  if (sequence.equals("12")) {
    currentPeople++;  
    sequence = "";
    delay(550);
  } else if (sequence.equals("21") && currentPeople > 0) {
    currentPeople--;  
    sequence = "";
    delay(550);
  }

  if (sequence.length() > 2 || sequence.equals("11") || sequence.equals("22") || timeoutCounter > 200) {
    sequence = "";
  }

  if (sequence.length() == 1) { //
    timeoutCounter++;
  } else {
    timeoutCounter = 0;
  }
  
  if (currentPeople > 0) {
    return true;
  } else {
    return false;
  }
}

// -- Activate Light System --
int activateLight(int led, bool gas, int light, bool people) {
  if (gas >= 300) {
    digitalWrite(led, LOW);
  } else {
    if (people && light >= 550) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }  
  }
}

// -- Activate Servo --
int activateServo(bool condition) {
  if (condition == true) {
    servo.write(180);
    delay(2000);
    servo.write(90);
  } else {
    servo.write(90);
  }
}
