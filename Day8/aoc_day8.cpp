#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

bool does_terminate(std::vector<std::pair<std::string, int> > &program)
{
  std::vector<bool> visited(program.size(), false);
  unsigned int pc = 0;
  int accumulator = 0;
  while(visited[pc] == false && pc < program.size())
  {
    visited[pc] = true;
    if(program[pc].first == "nop")
    {
      pc++;
    }
    else if(program[pc].first == "acc")
    {
      accumulator += program[pc].second;
      pc++;
    }
    else if(program[pc].first == "jmp")
    {
      pc += program[pc].second;
    }
    else
    {
      std::cout << "Error: Unknown instruction " << program[pc].first << std::endl;
      break;
    }
  }

  if(pc == program.size())
  {
    std::cout << "Accumulator: " << accumulator << std::endl;
    return true;

  }
  else
    return false;

}

int main()
{
  std::string line, token;
  std::ifstream input;
  input.open("input.txt");

  std::vector<std::pair<std::string, int> > program;

  do
  {
    std::getline(input, line, '\n');

    if(line.length() > 3)
    {
      std::string instruction = line.substr(0, 3);
      int argument = atoi(line.substr(3, std::string::npos).c_str());
      program.push_back(std::pair<std::string, int>(instruction, argument));
    }
  }while(!input.eof());

  int tests = 0;

  std::vector<std::pair<std::string, int> > test_program;

  do{

    test_program = program;

    for(int i = tests; i < program.size(); i++)
    {
      if(program[i].first == "jmp")
      {
        test_program[i].first = "nop";
        tests = i+1;
        break;
      }
      else if(program[i].first == "nop")
      {
        test_program[i].first = "jmp";
        tests = i+1;
        break;
      }
    }

    std::cout << tests << std::endl;

  }while(!does_terminate(test_program));


  input.close();
}
