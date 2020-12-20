
// 16u2 Firmware

#include "HID-Project.h"


void setup() {
  //  USB Serial
  Serial.begin(115200);

  //  IO MCU Serial
  Serial1.begin(115200);

  Gamepad.begin();

}

void loop() {
  {

    while (Serial1.available() > 0) {

            int xAxisReading = Serial1.parseInt();
            Gamepad.xAxis(xAxisReading);
            
            int yAxisReading = Serial1.parseInt();
            Gamepad.yAxis(yAxisReading);

            int rxAxisReading = Serial1.parseInt();
            Gamepad.rxAxis(rxAxisReading);

            int ryAxui= Serial1.parseInt();
            Gamepad.ryAxis(0);

            int zAxisReading = Serial1.parseInt();
            Gamepad.zAxis(zAxisReading);

            int rzAxisReading = Serial1.parseInt();
            Gamepad.rzAxis(rzAxisReading);


      for (int button = 1; button < 6; button++) {
        int buttonState = Serial1.parseInt();
        if (buttonState == 1) {
          Gamepad.press(button);
        }
        else {
          Gamepad.release(button);
        }
      }

      Gamepad.write();
      delay(5);
    }
  }
}
