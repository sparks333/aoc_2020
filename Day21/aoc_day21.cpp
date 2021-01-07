#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

std::vector<std::pair<std::vector<std::string>, std::vector<std::string> > > ingredients;

void print_state()
{
  for(int i = 0; i < ingredients.size(); i++)
  {
    for(int j = 0; j < ingredients[i].first.size(); j++)
    {
      std::cout << ingredients[i].first[j] << " ";
    }
    std::cout << " : ";
    for(int j = 0; j < ingredients[i].second.size(); j++)
    {
      std::cout << ingredients[i].second[j] << " ";
    }
    std::cout << std::endl;
  }
}

int isPunct(int c)
{
  return (c == '(') || (c == ')') || (c == ' ') || (c == ',') || (c == '\n') || (c == '\r');
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

  std::vector<std::pair<std::string, std::string> > dangerous_string;

  do{
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      auto tokenized = tokenize(line, ' ');
      int contains_index;

      for(contains_index = tokenized.size()-1; contains_index >= 0; contains_index--)
      {
        if(tokenized[contains_index] == "contains")
          break;
      }
      std::vector<std::string> foods(tokenized.begin(), tokenized.begin() + contains_index);
      std::sort(foods.begin(), foods.end());
      std::vector<std::string> allergens(tokenized.begin() + contains_index + 1, tokenized.end());
      std::sort(allergens.begin(), allergens.end());
      ingredients.push_back(std::pair<std::vector<std::string>, std::vector<std::string> >(foods, allergens));
    }
  }while(!input.eof());

  bool done = false;

  while(!done)
  {

    done = true;
//    print_state();

    for(int i = 0; i < ingredients.size(); i++)
    {
      for(int j = 0; j < ingredients[i].second.size(); j++)
      {
        std::vector<std::string> data = ingredients[i].first;
        std::string allergen = ingredients[i].second[j];
//        std::cout << "Ingredients: ";
//        for(int l = 0; l < data.size(); l++)
//        {
//          std::cout << data[l] << " ";
//        }
//        std::cout << std::endl;
        for(int k = 0; k < ingredients.size(); k++)
        {
          if(k != i)
          {
            if(data.size() == 0)
              break;

            if(data.size() == 1)
            {
              dangerous_string.push_back(std::pair<std::string, std::string>(data[0], allergen));
              for(int erase_index = 0; erase_index < ingredients.size(); erase_index++)
              {
                std::string dangerous_ingredient, dangerous_allergen;

                auto tmp_find = std::find(ingredients[erase_index].first.begin(), ingredients[erase_index].first.end(), data[0]);
                if(tmp_find != ingredients[erase_index].first.end())
                {
//                  std::cout << "Erasing " << data[0] << std::endl;
                  ingredients[erase_index].first.erase(tmp_find);
                }
                auto tmp_find_allergen = std::find(ingredients[erase_index].second.begin(), ingredients[erase_index].second.end(), allergen);
                if(tmp_find_allergen != ingredients[erase_index].second.end())
                {
//                  std::cout << "Erasing " << allergen << std::endl;
                  ingredients[erase_index].second.erase(tmp_find_allergen);
                }
              }
              done = false;
            }

            if(find(ingredients[k].second.begin(), ingredients[k].second.end(), allergen) != ingredients[k].second.end())
            {
//              std::cout << "Found another line with " << allergen << std::endl;
              std::vector<std::string> tmp(data.size());
              auto intersect_it = std::set_intersection(data.begin(), data.end(), ingredients[k].first.begin(), ingredients[k].first.end(), tmp.begin());
              tmp.resize(intersect_it-tmp.begin());
              data = tmp;
            }
          }
        }
      }
    }
  }

  int num_no_allergens = 0;

  for(int i = 0; i < ingredients.size(); i++)
  {
    num_no_allergens += ingredients[i].first.size();
  }

  std::cout << num_no_allergens << " non-allergenic ingredients appear" << std::endl;

  std::sort(dangerous_string.begin(), dangerous_string.end(), [](auto &left, auto &right) {
      return left.second < right.second;
  });

  auto last = std::unique(dangerous_string.begin(), dangerous_string.end(), [](auto &left, auto &right) {
      return left.first == right.first;
  });

  dangerous_string.erase(last, dangerous_string.end());

  for(int i = 0; i < dangerous_string.size(); i++)
  {
        std::cout << dangerous_string[i].first;
        if(i != dangerous_string.size() - 1)
          std::cout << ",";
        else
          std::cout << std::endl;
  }
}
