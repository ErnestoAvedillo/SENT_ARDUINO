#pragma once

#include <Arduino.h>
#include <time.h>
#include <../include/Vector.h>

#define SENSOR1 2
#define SENSOR2 3

void blink1();
void blink2();
uint8_t calculateCRC(uint32_t crcData, uint8_t seed);
uint32_t mergeNibbles(uint8_t* nibblesArray, bool recalculate);
uint16_t PolinomialDivision(uint32_t Dividend, uint16_t Divisor);
uint8_t calculateCRC2(uint32_t crcData, uint8_t _seed);
uint8_t calculateCRC3(uint32_t crcData);
uint8_t calculateCRC4(uint32_t crcData, uint8_t _seed);
uint32_t mergeNibbles(uint8_t* nibblesArray, bool recalculate);
