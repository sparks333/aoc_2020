#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  unsigned long long set_mask = 0;
  unsigned long long clear_mask = 0;

  std::map<unsigned int, unsigned long long> mem;

  do{
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      if(line[3] == 'k')
      {
        std::cout << line.size() << std::endl;
        set_mask = 0;
        clear_mask = 0;
        for(int i = 0; i < line.size()-1; i++)
        {
          if(line[7+i] == '1')
          {
            std::cout << "Set: " << 35 - i << std::endl;
            set_mask |= (1ULL << (35 - i));
          }
          if(line[7+i] == '0')
          {
            std::cout << "Clear: " << 35 - i << std::endl;
            clear_mask |= (1ULL << (35 - i));
          }
        }
        std::cout << std::endl;
        std::cout << "Set Mask:\t" << std::bitset<36>(set_mask) << std::endl;
        std::cout << "Clear Mask:\t" << std::bitset<36>(clear_mask) << std::endl;

      }
      else
      {
        int address;
        unsigned long long value;

        sscanf(line.c_str(), "mem[%i] = %llu", &address, &value);

        mem[address] = (value & ~clear_mask) | set_mask;

        std::cout << "Setting " << address << " to " << std::bitset<36>((value & ~clear_mask) | set_mask) << std::endl;
      }


    }
  }while(!input.eof());

  unsigned long long sum = 0;

  std::map<unsigned int, unsigned long long>::iterator it = mem.begin();

  while(it != mem.end())
  {
    sum += it->second;
    it++;
  }

  std::cout << "Sum: " << sum << std::endl;

  input.close();
}
