#include "HRC.h"

#define ledPin 13

#define RightMotPwm 7
#define LeftMotPwm 6
#define RightMotDir1 4
#define RightMotDir2 5
#define LeftMotDir1 2
#define LeftMotDir2 3

#define L_TRIG_PIN 48
#define L_ECHO_PIN 49
#define FL_TRIG_PIN 52
#define FL_ECHO_PIN 53
#define FR_TRIG_PIN 50
#define FR_ECHO_PIN 51
#define R_TRIG_PIN 46
#define R_ECHO_PIN 47

#define SERIAL_BAUDRATE 115200

#define TX_BUFF_SIZE 128
#define RX_BUFF_SIZE 128

String serverIn = "";
bool stringComplete = false;

char tx_buffer[TX_BUFF_SIZE];

HRC L{L_TRIG_PIN, L_ECHO_PIN};
HRC FL{FL_TRIG_PIN, FL_ECHO_PIN};
HRC FR{FR_TRIG_PIN, FR_ECHO_PIN};
HRC R{R_TRIG_PIN, R_ECHO_PIN};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUDRATE);
  serverIn.reserve(RX_BUFF_SIZE);
  pinMode(RightMotPwm, OUTPUT);
  pinMode(LeftMotPwm, OUTPUT);
  pinMode(RightMotDir1, OUTPUT);
  pinMode(RightMotDir2, OUTPUT);
  pinMode(LeftMotDir1, OUTPUT);
  pinMode(LeftMotDir2, OUTPUT);
  pinMode(ledPin, OUTPUT);
  analogWrite(RightMotPwm, 0);
  analogWrite(LeftMotPwm, 0);
  L.init();
  FL.init();
  FR.init();
  R.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete) {
    if ((serverIn == "ON") || (serverIn == "on") || (serverIn == "On") ) {
      Serial.println("Turn On");
      digitalWrite(ledPin, HIGH);
    }
    else if ((serverIn == "OFF") || (serverIn == "off") || (serverIn == "Off")) {
      Serial.println("Turn Off");
      digitalWrite(ledPin, LOW);
    }
    else if ((serverIn == "W") || (serverIn == "w")) {
      Serial.println("Go Forward");
      digitalWrite(RightMotDir1, LOW);
      digitalWrite(RightMotDir2, HIGH);
      digitalWrite(LeftMotDir1, LOW);
      digitalWrite(LeftMotDir2, HIGH);
      analogWrite(RightMotPwm, 255);
      analogWrite(LeftMotPwm, 255);
    }
    else if ((serverIn == "X") || (serverIn == "x")) {
      Serial.println("Go Backward");
      digitalWrite(RightMotDir1, HIGH);
      digitalWrite(RightMotDir2, LOW);
      digitalWrite(LeftMotDir1, HIGH);
      digitalWrite(LeftMotDir2, LOW);
      analogWrite(RightMotPwm, 255);
      analogWrite(LeftMotPwm, 255);
    }
    else if ((serverIn == "D") || (serverIn == "d")) {
      Serial.println("Turn Right");
      digitalWrite(RightMotDir1, HIGH);
      digitalWrite(RightMotDir2, LOW);
      digitalWrite(LeftMotDir1, LOW);
      digitalWrite(LeftMotDir2, HIGH);
      analogWrite(RightMotPwm, 255);
      analogWrite(LeftMotPwm, 255);
    }
    else if ((serverIn == "A") || (serverIn == "a")) {
      Serial.println("Turn Left");
      digitalWrite(RightMotDir1, LOW);
      digitalWrite(RightMotDir2, HIGH);
      digitalWrite(LeftMotDir1, HIGH);
      digitalWrite(LeftMotDir2, LOW);
      analogWrite(RightMotPwm, 255);
      analogWrite(LeftMotPwm, 255);
    }
    else if ((serverIn == "S") || (serverIn == "s")) {
      Serial.println("Stop");
      analogWrite(RightMotPwm, 0);
      analogWrite(LeftMotPwm, 0);
    }
    else if ((serverIn == "S") || (serverIn == "s")) {
      Serial.println("Stop");
      analogWrite(RightMotPwm, 0);
      analogWrite(LeftMotPwm, 0);
    }
    else if ((serverIn == "Dist") || (serverIn == "dist")) {
      //updateFrontDist();
      //Serial.println(frontDist);
      L.updateDist();
      FL.updateDist();
      FR.updateDist();
      R.updateDist();
      sprintf_P(tx_buffer, "%lu,%lu,%lu,%lu\n", L.get_cur_dist(), FL.get_cur_dist(), FR.get_cur_dist(), R.get_cur_dist());
      Serial.write(tx_buffer);
    }
    else {
      Serial.println("Unknown command");
    }
    serverIn = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      serverIn += inChar;
    }
    //delay(5);
  }
}
