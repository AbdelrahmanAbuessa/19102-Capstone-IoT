const int echoIN = 2;
const int trigIN = 3;

const int echoOUT = 4;
const int trigOUT = 5;

int timeIN = 0;
int timeOUT = 0;

int distIN = 0;
int distOUT = 0;

int people = 0;

bool inIN = false;
bool outIN = false;

bool inOUT = false;
bool outOUT = false;

void setup() {
  pinMode(trigIN, OUTPUT);
  pinMode(trigOUT, OUTPUT);
  pinMode(echoIN, INPUT);
  pinMode(echoOUT, INPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigIN, LOW);
  digitalWrite(trigOUT, LOW);
  delay(2);

  digitalWrite(trigIN, HIGH);
  digitalWrite(trigOUT, HIGH);
  delay(10);

  digitalWrite(trigIN, LOW);
  digitalWrite(trigOUT, LOW);

  timeIN = pulseIn(echoIN, HIGH);
  timeOUT = pulseIn(echoOUT, HIGH);

  distIN = timeIN / 58;
  distOUT = timeOUT / 58;

  if (distIN < 0) {
    distIN = 0;
  }
  
  if (distOUT < 0) {
    distOUT = 0;
  }

  if (distIN < 10 && inIN == false) {
    inIN = true;
  }

  if (distOUT < 10 && inIN == true) {
    outIN = true;
  }

  if (distIN > 10 && inIN == true && outIN == true) {
    people++;
    inIN = false;
    outIN = false;
  }

  if (distOUT < 10 && outOUT == false) {
    outOUT = true;
  }

  if (distIN < 10 && outOUT == true) {
    inOUT = true;
  }

  if (distOUT > 10 && inOUT == true && outOUT == true) {
    people--;
    inOUT = false;
    outOUT = false;
  }

  Serial.println(people);

  delay(2);
}
