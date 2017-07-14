unsigned int vcellMAX17043()
{
  unsigned int vcell;

  vcell = i2cRead16(0x02);
  vcell = vcell >> 4;  // last 4 bits of vcell are nothing

  return vcell;
}

/*
percentMAX17043() returns a float value of the battery percentage
reported from the SOC register of the MAX17043.
*/
float percentMAX17043()
{
  unsigned int soc;
  float percent;

  soc = i2cRead16(0x04);  // Read SOC register of MAX17043
  percent = (byte) (soc >> 8);  // High byte of SOC is percentage
  percent += ((float)((byte)soc))/256;  // Low byte is 1/256%

  return percent;
}

/* 
configMAX17043(byte percent) configures the config register of
the MAX170143, specifically the alert threshold therein. Pass a 
value between 1 and 32 to set the alert threshold to a value between
1 and 32%. Any other values will set the threshold to 32%.
*/
void configMAX17043(byte percent)
{
  if ((percent >= 32)||(percent == 0))  // Anything 32 or greater will set to 32%
    i2cWrite16(0x9700, 0x0C);
  else
  {
    byte percentBits = 32 - percent;
    i2cWrite16((0x9700 | percentBits), 0x0C);
  }
}

/* 
qsMAX17043() issues a quick-start command to the MAX17043.
A quick start allows the MAX17043 to restart fuel-gauge calculations
in the same manner as initial power-up of the IC. If an application's
power-up sequence is very noisy, such that excess error is introduced
into the IC's first guess of SOC, the Arduino can issue a quick-start
to reduce the error.
*/
void qsMAX17043()
{
  i2cWrite16(0x4000, 0x06);  // Write a 0x4000 to the MODE register
}

/* 
i2cRead16(unsigned char address) reads a 16-bit value beginning
at the 8-bit address, and continuing to the next address. A 16-bit
value is returned.
*/
unsigned int i2cRead16(unsigned char address)
{
  int data = 0;

  Wire.beginTransmission(MAX17043_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(MAX17043_ADDRESS, 2);
  while (Wire.available() < 2)
    ;
  data = ((int) Wire.read()) << 8;
  data |= Wire.read();

  return data;
}

/*
i2cWrite16(unsigned int data, unsigned char address) writes 16 bits
of data beginning at an 8-bit address, and continuing to the next.
*/
void i2cWrite16(unsigned int data, unsigned char address)
{
  Wire.beginTransmission(MAX17043_ADDRESS);
  Wire.write(address);
  Wire.write((byte)((data >> 8) & 0x00FF));
  Wire.write((byte)(data & 0x00FF));
  Wire.endTransmission();
}
