#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>

void generate_combos(unsigned long long address, unsigned long long mask, int index, std::vector<unsigned long long> & list)
{
  if(index == 36)
  {
    list.push_back(address);
    return;
  }
  else
  {
    if((mask & (1ULL << index)) != 0)
    {
      unsigned long long new_address;

      new_address = address & ~(1ULL << index);
      list.push_back(new_address);
      generate_combos(new_address, mask, index + 1, list);

      new_address = address | (1ULL << index);
      list.push_back(new_address);
      generate_combos(new_address, mask, index + 1, list);
    }
    else
    {
      generate_combos(address, mask, index + 1, list);
    }
  }


}

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  unsigned long long float_mask = 0;
  unsigned long long set_mask = 0;

  std::map<unsigned long long, unsigned long long> mem;

  do{
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      if(line[3] == 'k')
      {
        float_mask = 0;
        set_mask = 0;
        for(int i = 0; i < line.size()-1; i++)
        {
          if(line[7+i] == 'X')
          {
            float_mask |= (1ULL << (35 - i));
          }
          if(line[7+i] == '1')
          {
            set_mask |= (1ULL << (35 - i));
          }
        }
      }
      else
      {
        unsigned long long address;
        unsigned long long value;

        sscanf(line.c_str(), "mem[%llu] = %llu", &address, &value);

        std::cout << "Addresses:" << std::endl;

        std::vector<unsigned long long> mem_combos;

        generate_combos(address | set_mask, float_mask, 0, mem_combos);

        std::sort(mem_combos.begin(), mem_combos.end());
        auto last = std::unique(mem_combos.begin(), mem_combos.end());
        mem_combos.erase(last, mem_combos.end());

        for(int i = 0; i < mem_combos.size(); i++)
        {
          std::cout << std::bitset<36>(mem_combos[i]) << " (" << mem_combos[i] << ")" << std::endl;
          mem[mem_combos[i]] = value;
        }
      }
    }
  }while(!input.eof());

  unsigned long long sum = 0;
  unsigned long long prev_sum = 0;

  std::map<unsigned long long, unsigned long long>::iterator it = mem.begin();

  while(it != mem.end())
  {
    sum += it->second;

    if(sum < prev_sum)
      std::cout << "Overflow!" << std::endl;

    prev_sum = sum;
    it++;
  }

  std::cout << "Sum: " << sum << std::endl;

  input.close();
}
