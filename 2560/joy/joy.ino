
int pinButtons[] = {53, 51, 49, 47, 45, 43, 41, 39, 37, 35,33,31,29,27};

struct Axis {
  int pin;
  int value;
  
  //  Minimum and Max Values read on the axis pin, Ex: 0 => 1024 at 5v
  int analogMinimum;
  int analogMaximum;

  //  Values to map to, Ex: Z axis is a 8bit range, = -128 => 128
  int32_t minRes;
  int32_t maxRes;

  boolean isActive;

} arrayOfAxis[6] = {
  //    xAxis
  {A0, 0, 0, 1023, -32768, 32767, false},
  //    yAxis     
  {A1, 0, 0, 1023, -32768,  32767, false},
  // rxAxis
  {A2, 0, 0, 1023, -32768,  32767, true},
  // ryAxis
  {A3, 0, 0, 1023, -32768,  32767, true},
  //    zAxis
  {A4, 0, 0, 1023, -128, 127, true},
  //   rzAxis
  {A5, 0, 0, 1023, -128, 127, false}
};

void setup()
{

  for (int buttonIndex = 0; buttonIndex < sizeof(pinButtons); buttonIndex++) {
    pinMode(pinButtons[buttonIndex], INPUT_PULLUP);
  }

  Serial.begin(230400);
}

void loop()
{
  String controlState = "<";

  // Iterate each axis and print its value
  for (int AxisIndex = 0; AxisIndex < 6; AxisIndex++) {
    GetAnalogValue(AxisIndex);
    controlState += GetAnalogValue(AxisIndex);
    controlState += ",";
  }

  // Iterate each button and print its value
  int pinButtonsLength = (sizeof(pinButtons) / sizeof(pinButtons[0]));
  for (int buttonIndex = 0; buttonIndex < pinButtonsLength; buttonIndex++) {
    controlState += GetButtonValue(pinButtons[buttonIndex]);
    if (buttonIndex != (pinButtonsLength - 1)) {
      controlState += ",";
    };

  };
  controlState += ">";
  Serial.println(controlState);
//  Serial.print('<');Serial.print(controlState);Serial.print('>');
  delay(50);
}

int32_t GetAnalogValue(int AxisIndex) {
  Axis singleAxis = arrayOfAxis[AxisIndex];
  singleAxis.value = analogRead(singleAxis.pin);
  int32_t axisValue = 0;
  if (singleAxis.isActive == true) {
    axisValue = map(singleAxis.value, singleAxis.analogMinimum, singleAxis.analogMaximum, singleAxis.minRes, singleAxis.maxRes);
  }
  return axisValue;
}

int GetButtonValue(int joyButton) {
  int PinState = digitalRead(joyButton);
  return !PinState;
}
