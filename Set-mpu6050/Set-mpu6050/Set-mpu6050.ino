#include "Wire.h"
const int MPU_addr = 0x68;

// [accX, accY, accZ, temp, gyrX, gyrY, gyrZ]
int16_t data[7];
void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(9600);
}

void loop()
{
  getData();

  for (byte i = 0; i < 7; i++)
  {
    Serial.print(data[i]);
    Serial.print('\t');
  }
  Serial.println();
  delay(200);
}

void getData()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  for (byte i = 0; i < 7; i++)
  {
    data[i] = Wire.read() << 8 | Wire.read();
  }
}