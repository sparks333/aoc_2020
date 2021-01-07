#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>

std::string evaluate(std::string input)
{

  std::string tmp_string = input;

  std::cout << tmp_string << std::endl;

  auto end_parends = tmp_string.find(')');

  if(end_parends != std::string::npos)
  {
    auto start_parends = tmp_string.rfind('(', end_parends);
    std::string replace = evaluate(tmp_string.substr(start_parends+1, (end_parends-start_parends) - 1));
    tmp_string.erase(start_parends, end_parends-start_parends+1);
    tmp_string.insert(start_parends, replace);
    tmp_string = evaluate(tmp_string);
  }

  long long int arg1, arg2;
  char op = '?';

  long long int result;
  int string_length = 0;
  int index = 0;
  int prev_index = 0;
  int prev_prev_index = 0;
  int num_populated = 0;

  do{
    op = '?';
    //std::cout << "Checking " << tmp_string.substr(index, std::string::npos) << std::endl;
    num_populated = sscanf(tmp_string.substr(index, std::string::npos).c_str(), "%lld %c%n", &arg1, &op, &string_length);
    prev_prev_index = prev_index;
    prev_index = index;
    index += string_length + 1;
    //std::cout << "String Length: " << string_length << ", Index: " << index << ", OP: " << op << ", num_populated: " << num_populated << std::endl;

  }while(op == '*' && num_populated == 2);

  //std::cout << "Done searching" << std::endl;

  if(op == '+')
  {
    prev_prev_index = prev_index;
  }

  //std::cout << "Searching at " << prev_prev_index << std::endl;
  sscanf(tmp_string.substr(prev_prev_index, std::string::npos).c_str(), "%lld %c %lld%n", &arg1, &op, &arg2, &string_length);

  //std::cout << "Got OP " << op << std::endl;

  if(op != '?')
  {
    switch(op)
    {
      case '+':
        result = arg1 + arg2;
        break;
      case '*':
        result = arg1 * arg2;
        break;
    }
    tmp_string.erase(prev_prev_index, string_length);
    tmp_string.insert(prev_prev_index, std::to_string(result));
    tmp_string = evaluate(tmp_string);
  }
  return tmp_string;
}

long long int total_answer = 0;
long long int prev_total_answer = 0;


int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  do{
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      long long int answer = std::stoll(evaluate(line));
      total_answer += answer;
      if(prev_total_answer > total_answer)
      {
        std::cout << "Overflow!" << std::endl;
        while(1);
      }
      prev_total_answer = total_answer;
      std::cout << "Answer: " << answer << std::endl;
    }
  }while(!input.eof());

  std::cout << "Total answer: " << total_answer << std::endl;

}
