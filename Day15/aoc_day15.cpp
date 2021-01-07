#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <chrono>

#define MAX_I 30000000

int main()
{

  auto start = std::chrono::high_resolution_clock::now();

  std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int> > nums;

  nums.reserve(MAX_I);

  nums[12].first = 0;
  nums[12].second = 1;

  nums[20].first = 0;
  nums[20].second = 2;

  nums[0].first = 0;
  nums[0].second = 3;

  nums[6].first = 0;
  nums[6].second = 4;

  nums[1].first = 0;
  nums[1].second = 5;

  nums[17].first = 0;
  nums[17].second = 6;

  nums[7].first = 0;
  nums[7].second = 7;

  unsigned int prev_num = 7;

  for(int i = 7; i < MAX_I; i++)
  {
    if(nums[prev_num].first != 0)
    {
      unsigned int next_num = nums[prev_num].second - nums[prev_num].first;
      nums[next_num].first = nums[next_num].second;
      nums[next_num].second = i+1;
      if(i == MAX_I-1)
        std::cout << next_num << std::endl;
      prev_num = next_num;
    }
    else
    {
      if(i == MAX_I-1)
        std::cout << 0 << std::endl;
      nums[0].first = nums[0].second;
      nums[0].second = i+1;
      prev_num = 0;
    }
  }

  auto stop = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  std::cout << "Runtume: " << duration.count() << " microseconds" << std::endl; 

}
