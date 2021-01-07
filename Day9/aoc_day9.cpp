#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#define PREV_NUM 25
#define INVALID_NUM 1124361034

bool is_valid(int num, std::vector<int> prev_numbers)
{
  for(int i = 0; i < prev_numbers.size()-1; i++)
  {
    for(int j = i+1; j < prev_numbers.size(); j++)
    {
      if(prev_numbers[i] + prev_numbers[j] == num)
      {
        return true;
      }
    }
  }

  return false;
}

void contiguous_find(int num, std::vector<int> numbers)
{
  int index = 0;

  bool done = false;

  while(!done)
  {
    long int sum = 0;
    int sub_index = 0;

    while(sum < num)
    {
      sum += numbers[index + sub_index];
      sub_index += 1;
    }

    if(sum == num)
    {
      std::cout << "Found! " << std::endl;

      int min_val = numbers[index];
      int max_val = numbers[index];

      sum = 0;

      for(int i = index; i < index + sub_index; i++)
      {
        min_val = numbers[i] < min_val ? numbers[i] : min_val;
        max_val = numbers[i] > max_val ? numbers[i] : max_val;
        sum += numbers[i];
      }

      std::cout << "Index: " << index << ", " << "Sub-index: " << sub_index << std::endl;
      std::cout << "min: " << min_val << ", max: " << max_val << ", sum: " << sum << std::endl;


      std::cout << "Weakness: " << min_val + max_val << std::endl;
      done = 1;
    }
    else
    {
      index++;
      std::cout << "Index: " << index << std::endl;
    }
  }
}



int main()
{
  std::string line, token;
  std::ifstream input;
  input.open("input.txt");

  std::vector<int> numbers;

  do
  {
    std::getline(input, line, '\n');

    if(line.length() > 1)
    {
      numbers.push_back(atoi(line.c_str()));
    }

    if(numbers.size() > PREV_NUM+1)
    {

      std::vector<int> subvector(&numbers[numbers.size()-(PREV_NUM + 2)], &numbers[numbers.size()-2]);

      if(!is_valid(numbers[numbers.size()-2], subvector))
      {
        std::cout << "Invalid number: " << numbers[numbers.size() - 2] << std::endl;
        contiguous_find(numbers[numbers.size() - 2], numbers);

        break;
      }
    }
  }while(!input.eof());


  input.close();
}
