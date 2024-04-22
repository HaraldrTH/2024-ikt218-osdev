#include "../include/mem.h"
void memset(void* location, int val, int len)
{
   while(len > 0){
      location = val;
      len--;
      location++;
   }
}