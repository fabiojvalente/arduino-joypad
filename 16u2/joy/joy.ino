
// 16u2 Firmware

#include "HID-Project.h"


void setup() {
  //  USB Serial
  Serial.begin(230400);

  //  IO MCU Serial
  Serial1.begin(230400);
//  Serial1.setTimeout(15);



}

void loop() {
    String msg = getMessage();
    Serial.println(msg );
//  while (Serial1.available() > 0) {
//    String controlState = Serial1.readStringUntil('#');
//
//    Serial.println("BEGIN");
//    Serial.println(controlState);
//    Serial.println("End");
//    int xAxisReading = getValue(controlState, ',', 0);
//    int yAxisReading = getValue(controlState, ',', 1);
//    int rxAxisReading = getValue(controlState, ',', 2);
//    int ryAxisReading = getValue(controlState, ',', 3);
//    int zAxisReading = getValue(controlState, ',', 4);
//    int rzAxisReading = getValue(controlState, ',', 5);
//        
//    Gamepad.xAxis(xAxisReading);  
//    Gamepad.yAxis(yAxisReading);
//    Gamepad.rxAxis(rxAxisReading);
//    Gamepad.ryAxis(ryAxisReading);
//    Gamepad.zAxis(zAxisReading);
//    Gamepad.rzAxis(rzAxisReading);
//  }
//  
//  Gamepad.write();
//
  delay(20);
}

String getMessage() {
  String msg = "";

  while (Serial1.available()>0) {
    msg =  Serial1.readStringUntil('#');
  }
  return msg;
}

int getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]).toInt() : 0;
}
