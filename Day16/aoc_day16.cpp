#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>
#include <sstream>

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int> > > rules;
  std::vector<std::vector<std::string> > possible_labels;

  do
  {
    std::getline(input, line, '\n');

    if(line.size() > 1)
    {
      std::istringstream line_stream(line.c_str());

      std::string field;
      std::getline(line_stream, field, ':');
      std::string rule;
      std::getline(line_stream, rule, ':');

      int low_1, high_1, low_2, high_2;

      sscanf(rule.c_str(), "%i-%i or %i-%i", &low_1, &high_1, &low_2, &high_2);
      rules[field].first.first = low_1;
      rules[field].first.second = high_1;
      rules[field].second.first = low_2;
      rules[field].second.second = high_2;
      std::cout << "Rule: " << field << ", " << low_1 << "-" << high_1 << " or " << low_2 << "-" << high_2 << std::endl;
    }
  }while(line.size() > 1);

  int state = 0;

  std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int> > >::iterator it;

  for(int i = 0; i < rules.size(); i++)
  {
    it = rules.begin();
    std::vector<std::string> possible_strings;

    while(it != rules.end())
    {
      possible_strings.push_back(it->first);
      it++;
    }
    possible_labels.push_back(possible_strings);
    possible_strings.clear();
  }

  std::istringstream my_ticket;

  int invalid = 0;

  do{
    std::getline(input, line, '\n');
    std::istringstream tmp_line_stream(line.c_str());
    std::string tmp;
    std::string invalid_rule;
    int tmp_val;
    bool is_valid;
    int invalid_val;
    int remove_index;
    int index;
    if(line.size() > 1)
    {
      switch(state)
      {
        case 0:
          state = line[0] == 'y' ? 1 : 0;
          break;
        case 1:
          state = 2;
          goto test_ticket;
          break;
        case 2:
          if(line[0] == 'n')
          {
            state = 3;
            break;
          }
          else
          {
            break;
          }
        case 3:
test_ticket :
          index = 0;
          do{
            std::getline(tmp_line_stream, tmp, ',');
            sscanf(tmp.c_str(), "%i", &tmp_val);
            it = rules.begin();
            std::cout << "Checking " << tmp << std::endl;
            is_valid = false;
            invalid_val = 0;
            int i;
            while(it != rules.end())
            {
              is_valid |= (((tmp_val >= it->second.first.first && tmp_val <= it->second.first.second) || (tmp_val >= it->second.second.first && tmp_val <= it->second.second.second)));
              it++;
            }
            if(!is_valid)
            {
              invalid += tmp_val;
            }
            else
            {
              it = rules.begin();
              while(it != rules.end())
              {
                if(!((tmp_val >= it->second.first.first && tmp_val <= it->second.first.second) || (tmp_val >= it->second.second.first && tmp_val <= it->second.second.second)))
                {
                  std::cout << "Removing " << it->first <<  " from index " << index << std::endl;

                  for(int l = 0; l < possible_labels[index].size(); l++)
                  {
                    std::cout << possible_labels[index][l] << ", ";
                  }

                  std::cout << std::endl;

                  i = 0;
                  while(i < possible_labels[index].size())
                  {
                    if(possible_labels[index][i] == it->first)
                    {
                      possible_labels[index].erase(possible_labels[index].begin() + i);
                    }
                    else
                    {
                      i++;
                    }
                  }

                  //std::remove(possible_labels[index].begin(), possible_labels[index].end(), it->first);

                  for(int l = 0; l < possible_labels[index].size(); l++)
                  {
                    std::cout << possible_labels[index][l] << ", ";
                  }
                  std::cout << std::endl;


                }
                it++;
              }
            }
            index++;
          }while(!tmp_line_stream.eof());

          break;
        }
    }
  }while(!input.eof());

  bool changed;

  do
  {
    changed = false;
    for(int i = 0; i < possible_labels.size(); i++)
    {
      if(possible_labels[i].size() == 1)
      {
        for(int j = 0; j < possible_labels.size(); j++)
        {
          if(i != j)
          {
            int k = 0;
            while(k < possible_labels[j].size())
            {
              if(possible_labels[j][k] == possible_labels[i][0])
              {
                possible_labels[j].erase(possible_labels[j].begin() + k);
                changed = true;
              }
              else
              {
                k++;
              }
            }
          }
        }
      }
    }
  }while(changed);

  for(int k = 0; k < possible_labels.size(); k++)
  {
    for(int l = 0; l < possible_labels[k].size(); l++)
    {
      std::cout << possible_labels[k][l] << ", ";
    }
    std::cout << std::endl;
  }
  input.close();
}
