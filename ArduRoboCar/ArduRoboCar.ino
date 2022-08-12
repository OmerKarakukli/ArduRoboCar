#include "system_config.h"
#include "hrc.h"
#include "motor.h"

String serverIn = "";
bool stringComplete = false;

char tx_buffer[TX_BUFFER_SIZE];

HRC left_hrc{LEFT_HRC_TRIG_PIN, LEFT_HRC_ECHO_PIN};
HRC front_left_hrc{FRONT_LEFT_HRC_TRIG_PIN, FRONT_LEFT_HRC_ECHO_PIN};
HRC front_right_hrc{FRONT_RIGHT_HRC_TRIG_PIN, FRONT_RIGHT_HRC_ECHO_PIN};
HRC right_hrc{RIGHT_HRC_TRIG_PIN, RIGHT_HRC_ECHO_PIN};

Motor left_mot{LEFT_MOTOR_PWM_PIN, LEFT_MOTOR_DIR_1_PIN, LEFT_MOTOR_DIR_2_PIN, false};
Motor right_mot{RIGHT_MOTOR_PWM_PIN, RIGHT_MOTOR_DIR_1_PIN, RIGHT_MOTOR_DIR_2_PIN, false};

void setup() {
  // put your setup code here, to run once:
  serverIn.reserve(RX_BUFFER_SIZE);
  left_hrc.init();
  front_left_hrc.init();
  front_right_hrc.init();
  right_hrc.init();
  left_mot.init();
  right_mot.init();
  
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUDRATE);
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
      left_mot.setSpeed(255);
      right_mot.setSpeed(255);
    }
    else if ((serverIn == "X") || (serverIn == "x")) {
      Serial.println("Go Backward");
      left_mot.setSpeed(-255);
      right_mot.setSpeed(-255);
    }
    else if ((serverIn == "D") || (serverIn == "d")) {
      Serial.println("Turn Right");
      left_mot.setSpeed(255);
      right_mot.setSpeed(-255);
    }
    else if ((serverIn == "A") || (serverIn == "a")) {
      Serial.println("Turn Left");
      left_mot.setSpeed(-255);
      right_mot.setSpeed(255);
    }
    else if ((serverIn == "S") || (serverIn == "s")) {
      Serial.println("Stop");
      left_mot.setSpeed(0);
      right_mot.setSpeed(0);
    }
    else if ((serverIn == "Dist") || (serverIn == "dist")) {
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
