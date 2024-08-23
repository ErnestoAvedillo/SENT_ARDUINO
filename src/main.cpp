#include "main.h"

// put function declarations here:

//int myFunction(int, int);


//void printSensorValue(int sensorValue, int sensorNumber, unsigned long currentTime);
unsigned long initialTimeSensor1, initialTimeSensor2;
unsigned long fullperiodTime1, fullperiodTime2;
bool statusSensor1, statusSensor2;
bool toPrintSignal1, toPrintSignal2;
int tickNumber = 64;
int numInt = 0;
uint8_t Values1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t Values2[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println ("Initialising");
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR1), blink1, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR2), blink2, FALLING);
  initialTimeSensor1 = micros();
  initialTimeSensor2 = micros();
  toPrintSignal1 = false;
  toPrintSignal2 = false;
  statusSensor1 = false;
  statusSensor2 = false;
  Serial.println ("Start measuring");
// int result = myFunction(2, 3);
}

void loop() {
  unsigned int finalResult1 = 0;
  unsigned int finalResult2 = 0;
  int32_t srcData = 0;
  uint8_t CRC = 0;
  if (toPrintSignal1)
  {
    Serial.print(" 1- ");
    Serial.print(Values1[0], HEX);
    Serial.print(" - ");
    for (int i = 1; i < 9; i++)
    {  
      Serial.print((Values1[i] / 3) - 12, HEX);
      Serial.print(" - ");
    }
    srcData = mergeNibbles(Values1, true);
    Serial.print(srcData, HEX);
    for (uint8_t i = 0; i <= 0xF; i++)
    {
      CRC = calculateCRC(srcData, i);
      if (CRC == (Values1[8] / 3) - 12)
      {
        Serial.print(" -i ");
        Serial.print(i, HEX);
        Serial.print(" -crc ");
        Serial.print(CRC, HEX);
      }
    }
    Serial.println(".");
    toPrintSignal1 = false;
    statusSensor1 = false;
  }
  if (toPrintSignal2)
  {
    Serial.print(" 2- ");
    Serial.print(Values2[0], HEX);
    Serial.print(" - ");
    for (int i = 1; i < 9; i++)
    {  
      Serial.print((Values2[i] / 3) - 12, HEX);
      Serial.print(" - ");
    }
    srcData = mergeNibbles(Values2, true);
    Serial.print(srcData, HEX);
    for (uint8_t i = 0; i <= 0xF; i++)
    {
      CRC = calculateCRC(srcData, i);
      if (CRC == (Values2[8] / 3) - 12)
      {
        Serial.print(" -i ");
        Serial.print(i, HEX);
        Serial.print(" -crc ");
        Serial.print(CRC, HEX);
      }
    }
    Serial.println(".");
    toPrintSignal2 = false;
    statusSensor2 = false;
  }
//    uint8_t sal1[9] = {164, 0, 5, 3, 14, 5 ,3 ,14, 15};
//    srcData = mergeNibbles(sal1, false);
//    Serial.print(srcData, HEX);
//    Serial.print(" -v ");
//    Serial.print(sal1[8], HEX);
//    CRC = calculateCRC2(srcData);
//    Serial.print(" - ");
//    Serial.print(CRC, HEX);
//    Serial.println(".");
//    uint8_t sal2[9] = {164, 0, 7, 4, 8, 7, 4, 8, 3};
//    srcData = mergeNibbles(sal2, false);
//    Serial.print(srcData, HEX);
//    Serial.print(" -v ");
//    Serial.print(sal2[8], HEX);
//    CRC = calculateCRC3(srcData);
//    Serial.print(" - ");
//    Serial.print(CRC, HEX);
//    Serial.println(".");
//    uint8_t sal3[9] = {164, 0, 4, 10, 12, 4, 10, 12, 10};
//    srcData = mergeNibbles(sal3, false);
//    Serial.print(srcData, HEX);
//    Serial.print(" -v ");
//    Serial.print(sal3[8], HEX);
//    CRC = calculateCRC4(srcData);
//    Serial.print(" - ");
//    Serial.print(CRC, HEX);
//    Serial.println(".");
//    uint8_t sal4[9] = {164, 0, 7, 8, 15, 7, 8, 15, 5};
//    srcData = mergeNibbles(sal4, false);
//    Serial.print(srcData, HEX);
//    Serial.print(" -v ");
//    Serial.print(sal4[8], HEX);
//    CRC = calculateCRC(srcData, 0x5);
//    Serial.print(" - ");
//    Serial.print(CRC, HEX);
//    Serial.println(".");    
//    uint8_t sal5[9] = {164, 0, 9, 1, 13, 9, 1, 13 , 6};
//    srcData = mergeNibbles(sal5, false);
//    Serial.print(srcData, HEX);
//    Serial.print(" -v ");
//    Serial.print(sal5[8], HEX);
//    CRC = calculateCRC(srcData, 0x5);
//    Serial.print(" - ");
//    Serial.print(CRC, HEX);
//    Serial.println(".");
//    uint8_t sal6[9] = {164, 0, 0, 0, 0, 0, 0, 0 ,5};
//    srcData = mergeNibbles(sal6, false);
//    Serial.print(srcData, HEX);
//    Serial.print(" -v ");
//    Serial.print(sal6[8], HEX);
//    CRC = calculateCRC(srcData, 0x5);
//    Serial.print(" - ");
//    Serial.print(CRC, HEX);
//    Serial.println(".");
//    Serial.print(Values1[0]);
//    Serial.print(" -Status  ");
//    Serial.print((Values1[1] / 3) - 12);
//    Serial.print(" Data1 ");
//    finalResult1 = ((Values1[2] / 3) - 12);
//    finalResult1 = (finalResult1 << 4) | ((Values1[3] / 3) - 12);
//    finalResult1 = (finalResult1 << 4) | ((Values1[4] / 3) - 12);
//    Serial.print(finalResult1);
//    Serial.print(" Data2 ");
//    finalResult2 = ((Values1[5] / 3) - 12);
//    finalResult2 = (finalResult2 << 4) | ((Values1[6] / 3) - 12);
//    finalResult2 = (finalResult2 << 4) | ((Values1[7] / 3) - 12);
//    Serial.print(finalResult2);
//    Serial.print(" CRC ");
//    Serial.print((Values1[8] / 3) - 12);
//    Serial.println(".");
}

// put function definitions here:
//int myFunction(int x, int y) {
//  return x + y;
//}

void printvalue(int sensorvalue)
{
  if(sensorvalue == HIGH)
    Serial.print("HIGH");
  else
    Serial.print("LOW ");
}

//void printSensorValue(int sensorValue1, int sensorValue2, unsigned long currentTime) {
//  Serial.print("Time microseconds:");
//  Serial.print(currentTime - initialTime);
//  Serial.print(" Sensor 1|2:");
//  printvalue(sensorValue1);
//  Serial.print("|");
//  printvalue(sensorValue2);
//  Serial.println(".");
//}

void blink1() {
  unsigned long currentTime;
  currentTime = micros();
  fullperiodTime1 = currentTime - initialTimeSensor1;
  initialTimeSensor1 = currentTime;
  if (!toPrintSignal1)
  {
    if (fullperiodTime1 == 164 && !statusSensor1)
    {
      statusSensor1 = true;
      numInt = 0;
      Values1[numInt++] = static_cast <uint8_t> (fullperiodTime1);
    }
    else if(statusSensor1)
    {
      if (fullperiodTime1 < 36 || fullperiodTime1 > 81)
        statusSensor1 = false; //start again
      else
        Values1[numInt++] = static_cast <uint8_t> (fullperiodTime1);
      if(numInt == 9)
      {
        statusSensor1 = false;
        toPrintSignal1 = true;
      }
    }
  }
}

void blink2() {
  unsigned long currentTime;
  currentTime = micros();
  fullperiodTime2 = currentTime - initialTimeSensor2;
  initialTimeSensor2 = currentTime;
  if (!toPrintSignal2)
  {
    if (fullperiodTime2 == 164 && !statusSensor2)
    {
      statusSensor2 = true;
      numInt = 0;
      Values2[numInt++] = static_cast <uint8_t> (fullperiodTime2);
    }
    else if(statusSensor2)
    {
      if (fullperiodTime2 < 36 || fullperiodTime2 > 81)
        statusSensor2 = false; //start again
      else
        Values2[numInt++] = static_cast <uint8_t> (fullperiodTime2);
      if(numInt == 9)
      {
        statusSensor2 = false;
        toPrintSignal2 = true;
      }
    }
  }
}


