#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <regex>

#define DEBUG

#define CYCLE_MAX 1000000

typedef struct
{
  bool is_bottom_type;
  std::vector<std::vector<int> > sub_rules;
  char c;
} rule;

std::map<int, rule> rules;

std::string generate_regex(std::string str, int rule_index)
{

  std::string ret;

  if(rules[rule_index].is_bottom_type)
  {
    ret.push_back(rules[rule_index].c);
    return ret;
  }
  else
  {
    ret.push_back('(');
    for(int i = 0; i < rules[rule_index].sub_rules.size(); i++)
    {
      for(int j = 0; j < rules[rule_index].sub_rules[i].size(); j++)
      {
        ret += (generate_regex(str, rules[rule_index].sub_rules[i][j]));
      }
      if(i == (rules[rule_index].sub_rules.size() - 1))
      {
        ret.push_back(')');
      }
      else
      {
        ret.push_back('|');
      }
    }
  }
  return ret;
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
  input.open("input.txt", std::ifstream::binary);
  std::string aoc_regex;
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
        if(aoc_regex.size() == 0)
        {
          aoc_regex = generate_regex(std::string(), 0);
          std::cout << aoc_regex << std::endl;
        }
        std::string clipped_line = line.substr(0, line.size() - 1);
        std::cout << clipped_line << std::endl;


        if(std::regex_match(clipped_line, std::regex(aoc_regex)))
        {
          std::cout << "Valid!" << std::endl;
          num_valid++;
        }

      }
    }
  }while(!input.eof());
  std::cout << num_valid << " valid messages" << std::endl;
}
