#include "main.h"

int getMSBpos (uint32_t value)
{
  int MSBpos = 0;
  while(value & 0x0FFFFFFFF)
  {
    value >>= 1;
    MSBpos++;;
  }
//  Serial.print("MSB pos------------------");
//  Serial.println(MSBpos);
  
  return MSBpos;
}

uint16_t PolinomialDivision(uint32_t Dividend, uint16_t Divisor)
{
  uint32_t result = 0;
  uint32_t _divisor = Divisor;
  result = Dividend << 4;
  _divisor = _divisor << (getMSBpos(result) - getMSBpos(_divisor));
//  Serial.println("------------------");
//  Serial.println(result,BIN);
//  Serial.println(_divisor,BIN);
//  Serial.println("------------------");
  while(getMSBpos(result) > 4)
  {
//    Serial.println(result,BIN);
    _divisor = _divisor >> (getMSBpos(_divisor) - getMSBpos(result));
    result = result ^ _divisor;
//    Serial.println(_divisor,BIN);
//    Serial.println("------------------");
  }
//  Serial.print(" -o ");
//  Serial.print(result,HEX);

  return result;
}