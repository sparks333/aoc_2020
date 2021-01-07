#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <deque>
#include <map>

#define VERBOSE 0

std::map<std::tuple<int, int, int>, bool> tiles;

int num_black_neighbors(int x, int y, int z)
{
      int nbn =  tiles[std::tuple<int, int, int>(x-1, y+1, z+0)] ? 1: 0; //E
          nbn += tiles[std::tuple<int, int, int>(x-1, y+0, z+1)] ? 1: 0; //SE
          nbn += tiles[std::tuple<int, int, int>(x+0, y-1, z+1)] ? 1: 0; //SW
          nbn += tiles[std::tuple<int, int, int>(x+1, y-1, z+0)] ? 1: 0; //W
          nbn += tiles[std::tuple<int, int, int>(x+1, y+0, z-1)] ? 1: 0; //NW
          nbn += tiles[std::tuple<int, int, int>(x+0, y+1, z-1)] ? 1: 0; //NE
          return nbn;
}

int count_black_tiles()
{
  int num_black_tiles = 0;
  auto it = tiles.begin();
  while(it != tiles.end())
  {
    if(it->second == true)
    {
      num_black_tiles++;
    }
    it++;
  }
  return num_black_tiles;
}

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);
  do
  {
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      int index = 0;
      int x = 0; int y = 0; int z = 0;
      while(index < line.size())
      {
        if(line[index] == 'e')
        {
          //std::cout << "Moving E" << std::endl;
          index += 1;
          x--;
          y++;
        }
        else if(line[index] == 's' && line[index+1] == 'e')
        {
          //std::cout << "Moving SE" << std::endl;
          index += 2;
          x--;
          z++;
        }
        else if(line[index] == 's' && line[index+1] == 'w')
        {
          //std::cout << "Moving SW" << std::endl;
          index += 2;
          y--;
          z++;
        }
        else if(line[index] == 'w')
        {
          //std::cout << "Moving W" << std::endl;
          index += 1;
          x++;
          y--;
        }
        else if(line[index] == 'n' && line[index+1] == 'w')
        {
          //std::cout << "Moving NW" << std::endl;
          index += 2;
          x++;
          z--;
        }
        else if(line[index] == 'n' && line[index+1] == 'e')
        {
          //std::cout << "Moving NE" << std::endl;
          index += 2;
          y++;
          z--;
        }
        else
        {
          break;
        }
      }
      if(tiles[std::tuple<int, int, int>(x, y, z)])
      {
        std::cout << "Flipping (" << x << ", " << y << ", " << z << ") from black to white" << std::endl;
      }
      else
      {
        std::cout << "Flipping (" << x << ", " << y << ", " << z << ") from white to black" << std::endl;
      }
      tiles[std::tuple<int, int, int>(x, y, z)] = !tiles[std::tuple<int, int, int>(x, y, z)];
    }
  }while(!input.eof());

  for(int i = 0; i < 100; i++)
  {
    std::map<std::tuple<int, int, int>, bool> new_tiles;

    auto it = tiles.begin();
    while(it != tiles.end())
    {
      if(it->second == true)
      {
        int x = std::get<0>(it->first);
        int y = std::get<1>(it->first);
        int z = std::get<2>(it->first);

        //std::cout << "Black tile at ("<< x << ", " << y << ", " << z << ")" << std::endl;

        // Step 1: Check the number of neighbors this tile has
        int nbn = num_black_neighbors(x, y, z);
        if(nbn == 0 || nbn > 2)
        {
          new_tiles[std::tuple<int, int, int>(x, y, z)] = false;
        }
        else
        {
          new_tiles[std::tuple<int, int, int>(x, y, z)] = true;
        }

        // Step 2: Check the white tiles around the black tile
        if(tiles[std::tuple<int, int, int>(x-1, y+1, z+0)] == false && num_black_neighbors(x-1, y+1, z+0) == 2)
        {
          new_tiles[std::tuple<int, int, int>(x-1, y+1, z+0)] = true;
        }

        if(tiles[std::tuple<int, int, int>(x-1, y+0, z+1)] == false && num_black_neighbors(x-1, y+0, z+1) == 2)
        {
          new_tiles[std::tuple<int, int, int>(x-1, y+0, z+1)] = true;
        }

        if(tiles[std::tuple<int, int, int>(x+0, y-1, z+1)] == false && num_black_neighbors(x+0, y-1, z+1) == 2)
        {
          new_tiles[std::tuple<int, int, int>(x+0, y-1, z+1)] = true;
        }

        if(tiles[std::tuple<int, int, int>(x+1, y-1, z+0)] == false && num_black_neighbors(x+1, y-1, z+0) == 2)
        {
          new_tiles[std::tuple<int, int, int>(x+1, y-1, z+0)] = true;
        }

        if(tiles[std::tuple<int, int, int>(x+1, y+0, z-1)] == false && num_black_neighbors(x+1, y+0, z-1) == 2)
        {
          new_tiles[std::tuple<int, int, int>(x+1, y+0, z-1)] = true;
        }

        if(tiles[std::tuple<int, int, int>(x+0, y+1, z-1)] == false && num_black_neighbors(x+0, y+1, z-1) == 2)
        {
          new_tiles[std::tuple<int, int, int>(x+0, y+1, z-1)] = true;
        }
      }
      it++;
    }
    tiles = new_tiles;
    std::cout << "Day " << i+1 << ": " << count_black_tiles() << std::endl;
  }
}
