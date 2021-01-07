#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

long int num_combos;

void jolt_search(int curr_rating, int final_rating, std::vector<int> available_adapters)
{

  //std::cout << "Current rating: " << curr_rating << ", Final Rating: " << final_rating << std::endl;

  if((curr_rating + 3) == final_rating)
  {
    num_combos++;
    return;
  }
  else if(available_adapters.size() == 0)
  {
    return;
  }


  for(int i = 0; i < available_adapters.size(); i++)
  {
    if(available_adapters[i] <= (curr_rating + 3) && available_adapters[i] >= (curr_rating + 1))
    {
      std::vector<int> new_adapters(available_adapters.begin() + i + 1, available_adapters.end());
      jolt_search(available_adapters[i], final_rating, new_adapters);
    }
  }
  return;
}

void diff_search(std::vector<int> adapters)
{

  num_combos = 1;

  std::vector<int> diff(adapters.size());

  int ones_run = 0;

  for(int i = 0; i < adapters.size(); i++)
  {
    if(i == 0)
    {
      diff[i] = adapters[i];
    }
    else
    {
      diff[i] = adapters[i] - adapters[i-1];
    }

    if(diff[i] == 1)
    {
      ones_run++;
    }

    if(diff[i] != 1 || (i == adapters.size() - 1))
    {
      std::cout << "Ones run: " << ones_run << std::endl;
      if(ones_run == 0)
      {
        num_combos *= 1;
      }
      else if(ones_run == 1)
      {
        num_combos *= 1;
      }
      else if(ones_run == 2)
      {
        num_combos *= 2;
      }
      else if(ones_run == 3)
      {
        num_combos *= 4;
      }
      else if(ones_run == 4)
      {
        num_combos *= 7;
      }
      else
      {
        std::cout << "Something unexpected happened" << std::endl;
        return;
      }
      ones_run = 0;
    }


    std::cout << diff[i] << ", ";
  }



  std::cout << std::endl;

}


int main()
{
  std::string line, token;
  std::ifstream input;
  input.open("input.txt");

  std::vector<int> adapters;

  int outlet_rating = 0;
  int phone_rating = 0;

  num_combos = 0;

  do
  {
    std::getline(input, line, '\n');

    if(line.length() > 1)
    {
      adapters.push_back(atoi(line.c_str()));
      if(adapters[adapters.size() - 1] > (phone_rating - 3))
      {
        phone_rating = adapters[adapters.size() - 1] + 3;
      }
    }
  }while(!input.eof());

  std::sort(adapters.begin(), adapters.end());

  diff_search(adapters);

  //jolt_search(outlet_rating, phone_rating, adapters);

  std::cout << "Num combos: " << num_combos << std::endl;

  input.close();
}
