#include "data.hpp"
#include <iostream>

#define TOTAL 2020
#define NUM_ENTRIES sizeof(input) / sizeof(unsigned int)


int main()
{
  int max = 0;

  for(int i = 0; i < NUM_ENTRIES; i++)
  {
    for(int j = 0; j < NUM_ENTRIES; j++)
    {
      for(int k = 0; k < NUM_ENTRIES; k++)
      {
        if(~(i == j || i == k || j == k))
        {
          if(input[i] + input[j] + input[k] == TOTAL)
          {
            max = input[i] * input[j] * input[k] > max ? input[i] * input[j] * input[k] : max;
          }
        }
      }
    }
  }

  std::cout << "Maximum value: " << max << std::endl;

}
