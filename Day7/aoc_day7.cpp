#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include <sstream>

int contain_search(std::string index, std::map<std::string, std::vector<std::pair<int, std::string> > >& rules)
{
  if(rules[index].empty())
    return 1;
  else
  {
    std::vector<std::pair<int, std::string> >::iterator it = rules[index].begin();

    int num_bags = 1;
    while(it != rules[index].end())
    {
      for(int i = 0; i < it->first; i++)
      {
        std::cout << it->second << std::endl;
        num_bags += contain_search(it->second, rules);
      }
      it++;
    }
    return num_bags;
  }
}

int main()
{
  std::string line, token;
  std::ifstream input;
  input.open("input.txt");

  std::map<std::string, std::vector<std::pair<int, std::string> > > rules;

  do
  {
    std::getline(input, line, '\n');

    if(line.length() > 1)
    {
      std::istringstream rule_string(line.substr(0, line.length() - 1));

      std::string index, rule;

      // Colors
      getline(rule_string, token, ' ');
      index = token;
      getline(rule_string, token, ' ');
      index += token;

      // bags
      getline(rule_string, token, ' ');

      // contain
      getline(rule_string, token, ' ');

      bool done = false;

      // Number
      while(!done)
      {
        // number
        getline(rule_string, token, ' ');

        if(token == "no")
        {
          rule_string = std::istringstream();
          done = true;
          break;
        }

        int number;
        sscanf(token.c_str(), "%i", &number);

        // color
        getline(rule_string, token, ' ');
        rule = token;

        getline(rule_string, token, ' ');
        rule += token;

        // bags
        getline(rule_string, token, ' ');

        done = token[token.length() - 1] == '.';

        rules[index].push_back(std::pair<int, std::string>(number, rule));
      }
    }
  }while(!input.eof());

  std::map<std::string, std::vector<std::pair<int, std::string> > >::iterator it = rules.begin();

  int possibilities = contain_search("shinygold", rules);

  std::cout << "possibilities: " << possibilities - 1<< std::endl;

  input.close();
}
