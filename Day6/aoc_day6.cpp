#include <iostream>
#include <fstream>
#include <cstring>
#include <bitset>

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt");

  int sum = 0;

  unsigned int answered = 0;
  bool first = true;
  unsigned int group_num = 1;

  do
  {
    std::getline(input, line, '\n');

    if(line.length() <= 1)
    {
      std::cout << "Group Number " << group_num << std::endl;
      group_num++;
      for(int i = 0; i < 26; i++)
      {
        if((answered & (1 << i)) != 0)
        {
          std::cout << "Answered: " << (char) (i+'a') << std::endl;
          sum += 1;
        }
      }
      answered = 0;
      first = true;
    }
    else
    {
      unsigned int sub_answered = 0;
      for(int i = 0; i < line.length()-1; i++)
      {
        sub_answered |= (1 << (line[i] - 'a'));
      }
      if(first)
      {
        answered = sub_answered;
        first = false;
      }
      else
      {
        answered &= sub_answered;
      }
    }

  }while(!input.eof());

  std::cout << "Sum: " << sum << std::endl;

  input.close();
}
