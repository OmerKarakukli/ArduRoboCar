#include "SystemConfig.h"
#include "HRC.h"

String serverIn = "";
bool stringComplete = false;

char tx_buffer[TX_BUFFER_SIZE];

HRC left_hrc{LEFT_HRC_TRIG_PIN, LEFT_HRC_ECHO_PIN};
HRC front_left_hrc{FRONT_LEFT_HRC_TRIG_PIN, FRONT_LEFT_HRC_ECHO_PIN};
HRC front_right_hrc{FRONT_RIGHT_HRC_TRIG_PIN, FRONT_RIGHT_HRC_ECHO_PIN};
HRC right_hrc{RIGHT_HRC_TRIG_PIN, RIGHT_HRC_ECHO_PIN};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUDRATE);
  serverIn.reserve(RX_BUFFER_SIZE);
  pinMode(RIGHT_MOTOR_PWM_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_PWM_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR_1_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR_2_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_DIR_1_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_DIR_2_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  analogWrite(RIGHT_MOTOR_PWM_PIN, 0);
  analogWrite(LEFT_MOTOR_PWM_PIN, 0);
  left_hrc.init();
  front_left_hrc.init();
  front_right_hrc.init();
  right_hrc.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete) {
    if ((serverIn == "ON") || (serverIn == "on") || (serverIn == "On") ) {
      Serial.println("Turn On");
      digitalWrite(LED_PIN, HIGH);
    }
    else if ((serverIn == "OFF") || (serverIn == "off") || (serverIn == "Off")) {
      Serial.println("Turn Off");
      digitalWrite(LED_PIN, LOW);
    }
    else if ((serverIn == "W") || (serverIn == "w")) {
      Serial.println("Go Forward");
      digitalWrite(RIGHT_MOTOR_DIR_1_PIN, LOW);
      digitalWrite(RIGHT_MOTOR_DIR_2_PIN, HIGH);
      digitalWrite(LEFT_MOTOR_DIR_1_PIN, LOW);
      digitalWrite(LEFT_MOTOR_DIR_2_PIN, HIGH);
      analogWrite(RIGHT_MOTOR_PWM_PIN, 255);
      analogWrite(LEFT_MOTOR_PWM_PIN, 255);
    }
    else if ((serverIn == "X") || (serverIn == "x")) {
      Serial.println("Go Backward");
      digitalWrite(RIGHT_MOTOR_DIR_1_PIN, HIGH);
      digitalWrite(RIGHT_MOTOR_DIR_2_PIN, LOW);
      digitalWrite(LEFT_MOTOR_DIR_1_PIN, HIGH);
      digitalWrite(LEFT_MOTOR_DIR_2_PIN, LOW);
      analogWrite(RIGHT_MOTOR_PWM_PIN, 255);
      analogWrite(LEFT_MOTOR_PWM_PIN, 255);
    }
    else if ((serverIn == "D") || (serverIn == "d")) {
      Serial.println("Turn Right");
      digitalWrite(RIGHT_MOTOR_DIR_1_PIN, HIGH);
      digitalWrite(RIGHT_MOTOR_DIR_2_PIN, LOW);
      digitalWrite(LEFT_MOTOR_DIR_1_PIN, LOW);
      digitalWrite(LEFT_MOTOR_DIR_2_PIN, HIGH);
      analogWrite(RIGHT_MOTOR_PWM_PIN, 255);
      analogWrite(LEFT_MOTOR_PWM_PIN, 255);
    }
    else if ((serverIn == "A") || (serverIn == "a")) {
      Serial.println("Turn Left");
      digitalWrite(RIGHT_MOTOR_DIR_1_PIN, LOW);
      digitalWrite(RIGHT_MOTOR_DIR_2_PIN, HIGH);
      digitalWrite(LEFT_MOTOR_DIR_1_PIN, HIGH);
      digitalWrite(LEFT_MOTOR_DIR_2_PIN, LOW);
      analogWrite(RIGHT_MOTOR_PWM_PIN, 255);
      analogWrite(LEFT_MOTOR_PWM_PIN, 255);
    }
    else if ((serverIn == "S") || (serverIn == "s")) {
      Serial.println("Stop");
      analogWrite(RIGHT_MOTOR_PWM_PIN, 0);
      analogWrite(LEFT_MOTOR_PWM_PIN, 0);
    }
    else if ((serverIn == "S") || (serverIn == "s")) {
      Serial.println("Stop");
      analogWrite(RIGHT_MOTOR_PWM_PIN, 0);
      analogWrite(LEFT_MOTOR_PWM_PIN, 0);
    }
    else if ((serverIn == "Dist") || (serverIn == "dist")) {
      //updateFrontDist();
      //Serial.println(frontDist);
      left_hrc.updateDist();
      front_left_hrc.updateDist();
      front_right_hrc.updateDist();
      right_hrc.updateDist();
      sprintf_P(tx_buffer, "%lu,%lu,%lu,%lu\n", left_hrc.get_cur_dist(), front_left_hrc.get_cur_dist(), front_right_hrc.get_cur_dist(), right_hrc.get_cur_dist());
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
