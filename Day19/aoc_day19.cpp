#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

#define DEBUG

#define CYCLE_MAX 1000000

typedef struct
{
  bool is_bottom_type;
  std::vector<std::vector<int> > sub_rules;
  char c;
} rule;

std::map<int, rule> rules;

int cycles;

int check_string(std::string string, int rule_index, int string_index, std::vector<int> path, bool alt, int implied_length)
{
  cycles++;

  if(cycles > CYCLE_MAX)
  {
#ifdef DEBUG
    for(int i = 0; i < path.size(); i++)
    {
      std::cout << path[i] << ": ";
    }
    std::cout << "Runtime_Fail" << std::endl;
#endif
    return -1;
  }

  if(implied_length > string.size())
  {
#ifdef DEBUG
    for(int i = 0; i < path.size(); i++)
    {
      std::cout << path[i] << ": ";
    }
    std::cout << "Implied_Fail" << std::endl;
#endif
    return -1;
  }

  if(string_index >= string.size())
  {
#ifdef DEBUG
    for(int i = 0; i < path.size(); i++)
    {
      std::cout << path[i] << ": ";
    }
    std::cout << "EOS_Fail" << std::endl;
#endif
    return -1;
  }

  if(rules[rule_index].is_bottom_type)
  {
#ifdef DEBUG
    for(int i = 0; i < path.size(); i++)
    {
      std::cout << path[i] << ": ";
    }
    std::cout << string.substr(0, string_index) << rules[rule_index].c << ": ";
#endif

    if(string[string_index] == rules[rule_index].c)
    {
#ifdef DEBUG
      std::cout << "Match_Pass" << std::endl;
#endif
      return 1;
    }
    else
    {
#ifdef DEBUG
      std::cout << "Match_Fail" << std::endl;
#endif
      return -1;
    }
  }
  else
  {
    std::vector<std::pair<int, int> > tmp;
    int max_incr = -1;
    std::vector<int> possibilities;
    int max_increment = -1;

    for(int i = 0; i < rules[rule_index].sub_rules.size(); i++)
    {
      for(int iters = 0; iters < 2; iters++)
      {
        bool found = true;
        int increment = 0;
        for(int j = 0; j < rules[rule_index].sub_rules[i].size(); j++)
        {
          std::vector<int> new_path = path;
          new_path.push_back(rules[rule_index].sub_rules[i][j]);
          int test_increment = check_string(string,rules[rule_index].sub_rules[i][j], string_index + increment, new_path, iters > 0, implied_length + rules[rule_index].sub_rules[i].size() - 1);
          if(test_increment < 0)
          {
            found = false;
            break;
          }
          else
          {
            increment += test_increment;
          }
        }
        if(found)
        {
          if(!alt)
          {
#ifdef DEBUG
            for(int k = 0; k < path.size(); k++)
            {
              std::cout << path[k] << ": ";
            }
            std::cout << "Rule Success" << std::endl;
#endif
            return increment;
          }
          else
            max_increment = increment;
        }
      }
    }
    if(max_increment == -1)
    {
#ifdef DEBUG
    for(int i = 0; i < path.size(); i++)
    {
      std::cout << path[i] << ": ";
    }
    std::cout << "Rule Fail" << std::endl;
#endif
      return -1;
    }
    else
    {
#ifdef DEBUG
      for(int k = 0; k < path.size(); k++)
      {
        std::cout << path[k] << ": ";
      }
      std::cout << "Rule Success" << std::endl;
#endif
      return max_increment;
    }
  }
}

bool isDigit(std::string str)
{
  return (str[0] >= '0' && str[0] <= '9');
}

int isPunct(int c)
{
  return (c == ':') || (c == '"');
}

std::vector<std::string> tokenize(std::string str, char token)
{
  std::istringstream is(str);
  std::string part;
  std::vector<std::string> vec;
  while(getline(is, part, token))
  {
    std::string trimmed;
    std::remove_copy_if(part.begin(), part.end(),
                        std::back_inserter(trimmed), //Store output
                        std::ptr_fun<int, int>(&isPunct)
                       );

    vec.push_back(trimmed);
  }
  return vec;
}

int main()
{
  std::string line;
  std::ifstream input;
  input.open("test.txt", std::ifstream::binary);

  int num_valid = 0;

  do{
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      std::vector<std::string> tokenized = tokenize(line, ' ');
      if(isDigit(tokenized[0]))
      {
        int rule_num = stoi(tokenized[0]);
        if(isDigit(tokenized[1]))
        {
          rules[rule_num].is_bottom_type = false;
          int sub_index = 0;
          std::vector<int> sub_rule_vec;
          for(int i = 1; i < tokenized.size(); i++)
          {
            if(tokenized[i][0] == '|')
            {
              rules[rule_num].sub_rules.push_back(sub_rule_vec);
              sub_rule_vec.clear();
            }
            else
            {
              sub_rule_vec.push_back(stoi(tokenized[i]));
            }
          }
          rules[rule_num].sub_rules.push_back(sub_rule_vec);
        }
        else
        {
          rules[rule_num].is_bottom_type = true;
          rules[rule_num].c = tokenized[1][0];
        }
#ifdef DEBUG
        std::cout << "Rule " << rule_num;
        if(rules[rule_num].is_bottom_type)
        {
          std::cout << " is a bottom type, character " << rules[rule_num].c << std::endl;
        }
        else
        {
          std::cout << " is not a bottom type, accepts ";
          for(int i = 0; i < rules[rule_num].sub_rules.size(); i++)
          {
            for(int j = 0; j < rules[rule_num].sub_rules[i].size(); j++)
            {
              std:: cout << rules[rule_num].sub_rules[i][j] << " ";
            }
            if(i != rules[rule_num].sub_rules.size() - 1)
            {
              std:: cout << "or ";
            }
          }
          std::cout << std::endl;
        }
#endif
      }
      else
      {
        cycles = 0;
        std::string clipped_line = line.substr(0, line.size() - 1);
        std::cout << clipped_line << std::endl;
        int length = check_string(clipped_line, 0, 0, std::vector<int>({0}), false, 0);
        std::cout << "check_string length: " << length << ", string_length: " << clipped_line.size() << std::endl;
        if(clipped_line.size() == length)
        {
          std::cout << clipped_line << std::endl;
          num_valid++;
        }
      }
    }
  }while(!input.eof());
  std::cout << num_valid << " valid messages" << std::endl;
}
