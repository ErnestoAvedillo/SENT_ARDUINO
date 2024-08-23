#include "main.h"

uint8_t calculateCRC(uint32_t data, uint8_t _seed) 
{
    uint8_t crc = 0;
    uint32_t seed = _seed;
    uint16_t polynomial = 0x1D; // CRC polynomial for SENT protocol
    uint32_t  seed_data = (seed << 24) | data;
    crc = PolinomialDivision(seed_data, polynomial);
    return crc & 0xFF; // Return the 8-bit CRC
}

uint8_t calculateCRC2(uint32_t crcData, uint8_t _seed)
{
  int CRC4Table[16] = {0, 13, 7, 10, 14, 3, 9, 4, 1, 12, 6, 11, 15, 2, 8, 5};
  uint8_t CRCvalue = _seed;
  uint32_t _crcData = crcData << 4;
  for (int i = 6; i >= 1; i--)
  {
    uint8_t crcDatum = (_crcData >> 4 * i) & 0x0F;
    CRCvalue = CRC4Table[CRCvalue+1];
    CRCvalue = CRCvalue ^ crcDatum;
  }
  CRCvalue = CRC4Table[CRCvalue];
  return CRCvalue;
}
uint8_t calculateCRC3(uint32_t crcData)
{
    uint8_t crc6_table [64] = {0, 25, 50, 43, 61, 36, 15, 22, 35, 58, 17, 8, 30, 7, 44, 53, 31, 6, 45, 52, 34, 59, 16, 9, 60, 37, 14, 23, 1, 24, 51, 42, 62, 39, 12, 21, 3, 26, 49, 40, 29, 4, 47, 54, 32, 57, 18, 11, 33, 56, 19, 10, 28, 5, 46, 55, 2, 27, 48, 41, 63, 38, 13, 20};
    uint8_t CheckSum64 = 21;
    uint32_t crcDataAux = crcData << 6;
    for (int i = 4; i >= 1; i--)
    {
        uint8_t data = (crcDataAux >> 6 * i) & 0x3F;
        CheckSum64 = data ^ crc6_table[CheckSum64];
    }
    CheckSum64 = 0 ^ crc6_table[CheckSum64+1];
  return CheckSum64;
}
uint8_t calculateCRC4(uint32_t crcData, uint8_t _seed)
{
    uint8_t CRC4Table[256]= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,13, 12, 15, 14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2,7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8,10, 11, 8, 9, 14, 15, 12, 13, 2, 3, 0, 1, 6, 7, 4, 5,14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1,3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12,9, 8, 11, 10, 13, 12, 15, 14, 1, 0, 3, 2, 5, 4, 7, 6,4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11,1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14,12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3,6, 7, 4, 5, 2, 3, 0, 1, 14, 15, 12, 13, 10, 11, 8, 9,11, 10, 9, 8, 15, 14, 13, 12, 3, 2, 1, 0, 7, 6, 5, 4,15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,2, 3, 0, 1, 6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13,8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7,5, 4, 7, 6, 1, 0, 3, 2, 13, 12, 15, 14, 9, 8, 11, 10};
    uint8_t CheckSum = _seed;
    uint32_t _crcData = crcData << 4;
    int numNibbles = 6;
    for (int i = numNibbles; i >= 1; i--)
    {
        uint8_t data = (_crcData >> 4 * i) & 0x0F;
        CheckSum = CRC4Table[(data + (CheckSum << 4))];
    }
    return CheckSum;
}