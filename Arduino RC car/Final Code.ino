#include <SoftwareSerial.h>
#include <Servo.h>

#define in1 8
#define in2 10
#define ena1 9   // enable pin za L298N

Servo steering; 
SoftwareSerial mySerial(3, 2); // HC-05 Tx -> pin 3, Rx -> pin 2

unsigned long lastCommandTime = 0; 
const unsigned long commandTimeout = 200; // ms

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena1, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ena1, 0);
   
  steering.attach(6); 
  steering.write(90); // neutralna pozicija

  Serial.println("BT RC car ready!");
}

void loop() {
  if (mySerial.available()) {
    char inputvalue = mySerial.read();

    if (inputvalue == 'F') {        // naprijed
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(ena1, 255);
    }
    else if (inputvalue == 'B') {   // nazad
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(ena1, 255);
    }
    else if (inputvalue == 'L') {   // lijevo
      steering.write(120);
    }
    else if (inputvalue == 'R') {   // desno
      steering.write(60);
    }
    else if (inputvalue == 'H') {   // naprijed desno
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(ena1, 255);
      steering.write(60);
    }
    else if (inputvalue == 'G') {   // naprijed lijevo
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(ena1, 255);
      steering.write(120);
    }
    else if (inputvalue == 'J') {   // nazad desno
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(ena1, 255);
      steering.write(60);
    }
    else if (inputvalue == 'I') {   // nazad lijevo
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(ena1, 255);
      steering.write(120);
    }
    else if (inputvalue == 'Z') {   // vrati smjer na ravno
      steering.write(90);
    }
  }

}
