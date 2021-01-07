#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

#define N_SIZE 8
#define N_CYCLES 6

#define MAX_SIZE (N_SIZE + 2*N_CYCLES + 2)

bool cubes[MAX_SIZE][MAX_SIZE][MAX_SIZE][MAX_SIZE] = {false};
bool cubes_new[MAX_SIZE][MAX_SIZE][MAX_SIZE][MAX_SIZE] = {false};

void print_cube()
{
  for(int w = 1; w < MAX_SIZE - 1; w++)
  {
    for(int z = 1; z < MAX_SIZE - 1; z++)
    {
      std::cout << "z=" << z - (MAX_SIZE/2) << ", w=" << w - (MAX_SIZE/2) << std::endl;
      for(int y = 1; y < MAX_SIZE - 1; y++)
      {
        for(int x = 1; x < MAX_SIZE - 1; x++)
        {
          if(cubes[x][y][z][w])
            std::cout << "#";
          else
            std::cout << ".";
        }
        std::cout << std::endl;
      }
    }
    std::cout << std::endl << std::endl;
  }
}

int count_active_neighbors(int x, int y, int z, int w)
{
  int neighbors = 0;

  for(int h = w-1; h <= w+1; h++)
  {
    for(int i = z-1; i <= z+1; i++)
    {
      for(int j = y-1; j <= y+1; j++)
      {
        for(int k = x-1; k <= x+1; k++)
        {
          if(!(i == z && j == y && k == x && h == w))
            neighbors += cubes[k][j][i][h] == 1 ? 1 : 0;
        }
      }
    }
  }
  //std::cout << "At " << x << " " << y << " " << z << ", " << neighbors << " neighbors" << std::endl;
  return neighbors;
}

int count_active()
{
  int active = 0;

  for(int w = 1; w < MAX_SIZE - 1; w++)
  {
    for(int z = 1; z < MAX_SIZE - 1; z++)
    {
      for(int y = 1; y < MAX_SIZE - 1; y++)
      {
        for(int x = 1; x < MAX_SIZE - 1; x++)
        {
          active += cubes[x][y][z][w] ? 1 : 0;
        }
      }
    }
  }
  return active;
}

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  for(int y = (MAX_SIZE - N_SIZE)/2; y < ((MAX_SIZE - N_SIZE)/2) + N_SIZE; y++)
  {
    std::getline(input, line, '\n');
    for(int x = (MAX_SIZE - N_SIZE)/2; x < ((MAX_SIZE - N_SIZE)/2) + N_SIZE; x++)
    {
      cubes[x][y][(MAX_SIZE/2)][(MAX_SIZE/2)] = (line[x-(MAX_SIZE - N_SIZE)/2] == '#');
    }
  }

  //print_cube();

  for(int iters = 0; iters < N_CYCLES; iters++)
  {
    for(int w = 1; w < MAX_SIZE-1; w++)
    {
      for(int z = 1; z < MAX_SIZE-1; z++)
      {
        for(int y = 1; y < MAX_SIZE-1; y++)
        {
          for(int x = 1; x < MAX_SIZE-1; x++)
          {
            int active_neighbors = count_active_neighbors(x, y, z, w);
            if(cubes[x][y][z][w])
            {
              cubes_new[x][y][z][w] = ((active_neighbors == 2) || (active_neighbors == 3));
            }
            else
            {
              cubes_new[x][y][z][w] = active_neighbors == 3;
            }
          }
        }
      }
    }
    memcpy(cubes, cubes_new, MAX_SIZE * MAX_SIZE * MAX_SIZE * MAX_SIZE * sizeof(bool));
    std::cout << "Iteration " << iters + 1 << std::endl;;
    //print_cube();
  }

  std::cout << count_active() << " active" << std::endl;//
}
