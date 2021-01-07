#include <iostream>
#include <fstream>
#include <cstring>

int main()
{

  std::string line;
  std::ifstream input;
  input.open("input.txt");

  int min;
  int max;
  char character;
  char pw[256];

  int valid = 0;

  do
  {
    std::getline(input, line, '\n');

    sscanf(line.c_str(), "%i-%i %c: %s", &min, &max, &character, pw);

    if(strlen(pw) >= max && (pw[min-1] == character ^ pw[max-1] == character))
    {
      valid++;
    }


  }while(!input.eof());

  std::cout << valid << " valid passwords" << std::endl;

  input.close();
}
