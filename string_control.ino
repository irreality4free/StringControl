#include <string.h>
#include <avr/pgmspace.h>
const int led = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(50);
  pinMode(led, OUTPUT);
}

long current = 0;
int period = 500;

void blinking() {
  if (millis() - current > period) {
    digitalWrite(led, !digitalRead(led));
    current = millis();
  }
}




void StrCommand(const int param_limit = 10) {
  if (Serial.available() > 0) {
    String com = Serial.readString();
    unsigned int st_len = com.length();
    //  Serial.print(F("String legth - "));
    //  Serial.println(st_len);
    if (com.substring(0, 4) == "com:") {
      int param_num = com.substring(4, com.indexOf('$')).toInt();
      if (param_num > 0 && param_num < param_limit) {
        com = com.substring(com.indexOf('$') + 1, com.length());
        String params[param_num];
        for (int i = 0; i < param_num; i++) {
          params[i] = com.substring(0, com.indexOf(';'));
          //        Serial.print(F("Param num - "));
          //        Serial.println(i+1);
          //        Serial.println(params[i]);
          com = com.substring(com.indexOf(';') + 1, com.length());
        }

        Controller(params, param_num);
        Serial.println(params[1]);


      }
      else {
        Serial.println(F("Too much args"));
      }
    }
  }
}

void Controller(String params[],const int params_num) {
  if (params[0] == "servo") {
    int servo_num = params[1].toInt();
    int servo_pos = params[2].toInt();
    Serial.print(F("servo_num - "));
    Serial.println(servo_num);
    Serial.print(F("servo_pos - "));
    Serial.println(servo_pos);
    params[1] = "130";
  }
}

void loop() {
  //   put your main code here, to run repeatedly:
  blinking();
  StrCommand();



}



//String com = Serial.readStringUntil(';');
//i[0]=com;
//Serial.println(i[0]);
