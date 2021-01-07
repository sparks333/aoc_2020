#include <iostream>
#include <fstream>
#include <cstring>

char fields[8][4] = {
  "byr",
  "iyr",
  "eyr",
  "hgt",
  "hcl",
  "ecl",
  "pid",
  "cid"
};

char eye_color[7][4] = {
  "amb",
  "blu",
  "brn",
  "gry",
  "grn",
  "hzl",
  "oth"
};

int checkValid(std::string & user)
{
  bool valid[8] = {false, false, false, false, false, false, false, true};

  std::string entry;
  std::string field;
  std::string data;

  bool done = false;

  while(!done){

    if(user.find(' ') == std::string::npos)
    {
      done = true;
      entry = user;
    }
    else
    {
      entry = user.substr(0, user.find(' '));
    }

    field = entry.substr(0, entry.find(':'));
    data = entry.substr(entry.find(':')+1, std::string::npos);

    std::cout << "Field: " << field << std::endl;
    std::cout << "Data: " << data << std::endl;

    if(strncmp(fields[0], field.c_str(), 3) == 0)
    {
      int yr;
      if(sscanf(data.c_str(), "%i", &yr) == 1 && yr >= 1920 && yr <= 2002)
        valid[0] = true;
      else
        std::cout << "Invalid" << std::endl;
    }
    else if(strncmp(fields[1], field.c_str(), 3) == 0)
    {
      int yr;
      if(sscanf(data.c_str(), "%i", &yr) == 1 && yr >= 2010 && yr <= 2020)
        valid[1] = true;
      else
        std::cout << "Invalid" << std::endl;
    }
    else if(strncmp(fields[2], field.c_str(), 3) == 0)
    {
      int yr;
      if(sscanf(data.c_str(), "%i", &yr) == 1 && yr >= 2020 && yr <= 2030)
        valid[2] = true;
      else
        std::cout << "Invalid" << std::endl;
    }
    else if(strncmp(fields[3], field.c_str(), 3) == 0)
    {
      int height = 0;
      if(data[3] == 'c' && data[4] == 'm')
      {
        valid[3] = sscanf(data.c_str(), "%i", &height) == 1 && height >= 150 && height <= 193;
        std::cout << "Height: " << height << " cm" << std::endl;
      }
      else if(data[2] == 'i' && data[3] == 'n' || data[3] == 'i' && data[4] == 'n')
      {
        valid[3] = sscanf(data.c_str(), "%i", &height) == 1 && height >= 59 && height <= 76;
        std::cout << "Height: " << height << " in" << std::endl;
      }

      if(!valid[3])
        std::cout << "Invalid" << std::endl;
    }
    else if(strncmp(fields[4], field.c_str(), 3) == 0)
    {
      char hcl[16];
      if(data[0] == '#' && sscanf(data.c_str(), "#%s", hcl) == 1 && strlen(hcl) == 6)
      {

        bool sub_valid = true;

        for(int i = 0; i < 6; i++)
        {
          sub_valid &= ((hcl[i] >= 48 && hcl[i] <= 57) || (hcl[i] >= 97 && hcl[i] <= 102));
        }
        valid[4] = sub_valid;
      }

      if(!valid[4])
        std::cout << "Invalid" << std::endl;
    }
    else if(strncmp(fields[5], field.c_str(), 3) == 0)
    {
      bool sub_valid = false;
      for(int i = 0; i < 7; i++)
      {
        sub_valid |= (strncmp(data.c_str(), eye_color[i], 3) == 0);
      }
      if(sub_valid)
        valid[5] = true;
      else
        std::cout << "Invalid" << std::endl;
    }
    else if(strncmp(fields[6], field.c_str(), 3) == 0)
    {
      char pid[16];
      bool sub_valid = true;

      if(sscanf(data.c_str(), "%s", pid) == 1)
      {
        for(int i = 0; i < 9; i++)
        {
          sub_valid &= (pid[i] >= '0' && pid[i] <= '9');
        }
          valid[6] = sub_valid && strlen(pid) == 9;
      }
      if(!valid[6])
        std::cout << "Invalid" << std::endl;
    }
    user = user.substr(user.find(' ') + 1, std::string::npos);
  };

  bool total_valid = true;

  for(int i = 0; i < 8; i++)
  {
    if(valid[i] == false)
      std::cout << "Invalid: Error in " << fields[i] << std::endl;
    total_valid &= valid[i];
  }

  std::cout << "Valid: " << total_valid << std::endl;
  std::cout << std::endl;

  return total_valid;
}

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt");

  unsigned int n_valid = 0;
  unsigned int n_invalid = 0;

  std::string user;

  bool first = true;

  do
  {
    std::getline(input, line, '\n');
    if(line.length() < 3)
    {
      if(checkValid(user))
        n_valid++;
      else
        n_invalid++;
      user.clear();
      first = true;
    }
    else
    {
      if(first)
      {
        user = line;
        first = false;
      }
      else
      {
        user = user.substr(0, user.length() - 1) + " " + line;
      }
    }
  }while(!input.eof());

  std::cout << "Valid: " << n_valid << ", Invalid: " << n_invalid << std::endl;

  input.close();
}
