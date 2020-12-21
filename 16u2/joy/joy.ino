#include "HID-Project.h"

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  Serial1.begin(230400);
  Serial.begin(230400);
  Gamepad.begin();
}

void loop() {
  recvWithStartEndMarkers();
  getMessage();
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial1.available() > 0 && newData == false) {
    rc = Serial1.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

char getMessage() {
  if (newData == true) {
    processControllerInput();
    newData = false;
    //        return receivedChars;
  }
}

void processControllerInput() {
  char *pch =  NULL;
  char *inputs[32];
  byte index = 0;

  pch = strtok  (receivedChars, ",:;");
  while (pch != NULL)
  {
    inputs[index] = pch;
    index++;
    pch = strtok (NULL, ",:;");
  }

  Gamepad.xAxis(atol ( inputs[0] ));
  Gamepad.yAxis(atol ( inputs[1] ));
  Gamepad.rxAxis(atol ( inputs[2] ));
  Gamepad.ryAxis(atol ( inputs[3] ));
  Gamepad.zAxis( atol ( inputs[4] ));
  Gamepad.rzAxis(atol ( inputs[5] ));

  for (int button = 1; button < 6; button++) {
    long buttonState = atol (  inputs[(button + 5)] );
    Serial.println(buttonState);
    if (  buttonState == 1) {
      Gamepad.press(button);
    }
    else {
      Gamepad.release(button);
    }
  }

  Gamepad.write();
  delay(5);


}
