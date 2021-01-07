#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

int main()
{
  std::string line, token;
  std::ifstream input;
  input.open("test.txt", std::ifstream::binary);

  int way_y = 1, way_x = 10;
  int pos_y = 0, pos_x = 0, h = 90;

  do
  {
    std::getline(input, line, '\n');

    if(line.length() > 1)
    {
      char inst;
      int arg;
      sscanf(line.c_str(), "%c%i", &inst, &arg);

      int diff_x = way_x - pos_x;
      int diff_y = way_y - pos_y;

      if(inst == 'N')
      {
        way_y += arg;
      }
      if(inst == 'S')
      {
        way_y -= arg;
      }
      if(inst == 'E')
      {
        way_x += arg;
      }
      if(inst == 'W')
      {
        way_x -= arg;
      }
      if(inst == 'L')
      {
        if(arg == 90)
        {
            way_x = pos_x - diff_y;
            way_y = pos_y + diff_x;
        }
        if(arg == 180)
        {
          way_x = pos_x - diff_x;
          way_y = pos_y - diff_y;
        }
        if(arg == 270)
        {
          way_x = pos_x + diff_y;
          way_y = pos_y - diff_x;
        }
      }
      if(inst == 'R')
      {
        if(arg == 90)
        {
            way_x = pos_x + diff_y;
            way_y = pos_y - diff_x;
        }
        if(arg == 180)
        {
          way_x = pos_x - diff_x;
          way_y = pos_y - diff_y;
        }
        if(arg == 270)
        {
          way_x = pos_x - diff_y;
          way_y = pos_y + diff_x;
        }
      }
      if(inst == 'F')
      {
        pos_x += diff_x*arg;
        pos_y += diff_y*arg;
        way_x = pos_x + diff_x;
        way_y = pos_y + diff_y;
      }
    }
    std::cout << "Position: X:" << pos_x << ", Y: " << pos_y << ", Waypoint X: " << way_x << ", Waypoint Y: " << way_y << std::endl;

  }while(!input.eof());

  std::cout << "Distance: " << abs(pos_x) + abs(pos_y) << std::endl;

  input.close();
}
