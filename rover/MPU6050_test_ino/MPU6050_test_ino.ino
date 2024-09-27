#include <Wire.h>

const int MPU = 0x68;  // I2C address of the MPU-6050

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // Power management register
  Wire.write(0);     // Wake the MPU-6050 up
  Wire.endTransmission(true);

  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // Starting with the register for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);  // Request 14 registers

  AcX = Wire.read() << 8 | Wire.read();  // Accelerometer X
  AcY = Wire.read() << 8 | Wire.read();  // Accelerometer Y
  AcZ = Wire.read() << 8 | Wire.read();  // Accelerometer Z
  GyX = Wire.read() << 8 | Wire.read();  // Gyroscope X
  GyY = Wire.read() << 8 | Wire.read();  // Gyroscope Y
  GyZ = Wire.read() << 8 | Wire.read();  // Gyroscope Z

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ);

  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);

  delay(500);  // Delay to make the output readable
}
