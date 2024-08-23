#include "main.h"

uint32_t mergeNibbles(uint8_t* nibblesArray, bool recalculate)
{
  uint32_t returnvalue = 0;
  if (recalculate)
      returnvalue = (returnvalue) | ((nibblesArray[2] / 3) - 12);
  else
      returnvalue = (returnvalue) | nibblesArray[2];
  for (int i = 3; i < 8; i++)
  {
    if (recalculate)
        returnvalue = (returnvalue << 4) | ((nibblesArray[i] / 3) - 12);
    else
        returnvalue = (returnvalue << 4) | nibblesArray[i];
  }
  return returnvalue;
}

