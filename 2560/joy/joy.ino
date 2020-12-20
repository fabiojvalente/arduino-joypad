
int pinButtons[] = {53, 49, 45, 41, 37};

struct Axis {
  int pin;
  int value;
  //  Minimum and Max Values read on the axis pin, Ex: 0 => 1024 at 5v
  int analogMinimum;
  int analogMaximum;

  //  values to map to, Ex: Z axis is a 8bit range, = -128 => 128
  int32_t minRes;
  int32_t maxRes;

  boolean isActive;

} arrayOfAxis[6] = {
  //    xAxis
  {A0, 0, 0, 1023, -32768, 32768, false},
  //    yAxis
  {A1, 0, 0, 1023, -32768,  32768, false},
  // rxAxis
  {A2, 0, 0, 1023, -32768,  32768, false},
  // ryAxis
  {A3, 0, 0, 1023, -32768,  32768, false},
  //    zAxis
  {A4, 0, 0, 1023, -128, 128, true},
  //   rzAxis
  {A5, 0, 0, 1023, -128, 128, false}
};

void setup()
{

  for (int buttonIndex = 0; buttonIndex < sizeof(pinButtons); buttonIndex++) {
    pinMode(pinButtons[buttonIndex], INPUT);
  }

  Serial.begin(115200);
}

void loop()
{
  // Iterate each axis and print its value
  for (int AxisIndex = 0; AxisIndex < 6; AxisIndex++) {
    GetAnalogValue(AxisIndex );
  }
  // Iterate each button and print its value
  for (int buttonIndex = 0; buttonIndex < (sizeof(pinButtons) / sizeof(pinButtons[0])); buttonIndex++) {
    GetButtonValue(pinButtons[buttonIndex]);
  };

  Serial.println();
  delay(30);
}

void GetAnalogValue(int AxisIndex) {
  Axis singleAxis = arrayOfAxis[AxisIndex];
  singleAxis.value = analogRead(singleAxis.pin);
  if (singleAxis.isActive == true) {
    int32_t axisValue = map(singleAxis.value, singleAxis.analogMinimum, singleAxis.analogMaximum, singleAxis.minRes, singleAxis.maxRes);
    Serial.print(axisValue);
  } else {
    Serial.print(0);
  };
  Serial.print(",");
}

void GetButtonValue(int joyButton) {
  int PinState = digitalRead(joyButton);
  if (PinState == HIGH) {
    Serial.write("1");
  } else {
    Serial.write("0");
  }
  Serial.write(",");
}
