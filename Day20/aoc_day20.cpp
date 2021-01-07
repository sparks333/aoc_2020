#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

#define SIZE 10

std::map<std::pair<int, int>, bool> image;

bool sea_monster[3][20] =
{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
  {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}
};

std::map<std::pair<int, int>, bool> flip(std::map<std::pair<int, int>, bool> img, int x, int y)
{
  std::map<std::pair<int, int>, bool> tmp;

  for(int i = 0; i < y; i++)
  {
    for(int j = 0; j < x; j++)
    {
      tmp[std::pair<int, int>(i, j)] = img[std::pair<int, int>(i, (x-j)-1)];
    }
  }
  return tmp;
}

std::map<std::pair<int, int>, bool> transpose(std::map<std::pair<int, int>, bool> img, int x, int y)
{
  std::map<std::pair<int, int>, bool> tmp;

  for(int i = 0; i < y; i++)
  {
    for(int j = 0; j < x; j++)
    {
      tmp[std::pair<int, int>(i, j)] = img[std::pair<int, int>(j, i)];
    }
  }
  return tmp;
}

std::map<std::pair<int, int>, bool> rotate(std::map<std::pair<int, int>, bool> img, int x, int y)
{
  return flip(transpose(img, x, y), x, y);
}

class Puzzle
{
public:
  long long unsigned int id;
  Puzzle * N;
  Puzzle * E;
  Puzzle * S;
  Puzzle * W;

  bool data[SIZE][SIZE] = {false};

  bool locked;

  Puzzle()
  {
    N = 0;
    E = 0;
    S = 0;
    W = 0;
  }

  bool is_corner()
  {
    return ((N==0) && (E==0)) || ((E==0) && (S == 0)) || ((S==0) && (W==0)) || ((W==0) && (N == 0));
  }

  bool is_sw_corner()
  {
    return ((S==0) && (W==0));
  }

  void print_board()
  {
    std::cout << "ID: " << id << std::endl;
    for(int i = 0; i < SIZE; i++)
    {
      for(int j = 0; j < SIZE; j++)
      {
        if(data[i][j])
          std::cout << "#";
        else
          std::cout << ".";
      }
      std::cout << std::endl;
    }
  }

  void flip()
  {
    if(locked)
      return;

    bool tmp[SIZE][SIZE];
    for(int i = 0; i < SIZE; i++)
    {
      for(int j = 0; j < SIZE; j++)
      {
        tmp[i][j] = data[i][(SIZE-1)-j];
      }
    }
    memcpy(data, tmp, SIZE*SIZE*sizeof(bool));
  }

  void transpose()
  {
    if(locked)
      return;

    bool tmp[SIZE][SIZE];
    for(int i = 0; i < SIZE; i++)
    {
      for(int j = 0; j < SIZE; j++)
      {
        tmp[i][j] = data[j][i];
      }
    }
    memcpy(data, tmp, SIZE*SIZE*sizeof(bool));
  }

  void rotate()
  {
    //print_board();
    transpose();
    flip();
    //print_board();
  }

  bool checkNBoundary(Puzzle * p)
  {
    if(N != 0)
      return false;

    bool matching = true;

    for(int k = 0; k < 2; k++)
    {
      for(int j = 0; j < 4; j++)
      {
        matching = true;
        for(int i = 0; i < SIZE; i++)
        {
          matching &= data[SIZE-1][i] == p->data[0][i];
        }
        if(matching)
          break;
        else
          p->rotate();
      }
      if(matching)
        break;
      else
        p->flip();
    }

    if(matching)
    {
      p->locked = true;
      N = p;
      p->S = this;
      //std::cout << "Matched " << id << " North to " << p->id << std::endl;
    }

    return matching;
  }

  bool checkEBoundary(Puzzle * p)
  {

    if(E != 0)
      return false;

    bool matching = true;

    for(int k = 0; k < 2; k++)
    {
      for(int j = 0; j < 4; j++)
      {
        matching=true;
        for(int i = 0; i < SIZE; i++)
        {
          matching &= data[i][SIZE-1] == p->data[i][0];
        }
        if(matching)
          break;
        else
          p->rotate();
      }
      if(matching)
        break;
      else
        p->flip();
    }

    if(matching)
    {
      p->locked = true;
      E = p;
      p->W = this;
      //std::cout << "Matched " << id << " East to " << p->id << std::endl;
    }
    return matching;
  }

  bool checkSBoundary(Puzzle * p)
  {
    if(S != 0)
      return false;

    bool matching = true;

    for(int k = 0; k < 2; k++)
    {
      for(int j = 0; j < 4; j++)
      {
        matching = true;
        for(int i = 0; i < SIZE; i++)
        {
          matching &= data[0][i] == p->data[(SIZE-1)][i];
        }
        if(matching)
          break;
        else
          p->rotate();
      }
      if(matching)
        break;
      else
        p->flip();
    }

    if(matching)
    {
      p->locked = true;
      S = p;
      p->N = this;
      //std::cout << "Matched " << id << " South to " << p->id << std::endl;
    }
    return matching;
  }

  bool checkWBoundary(Puzzle * p)
  {
    if(W != 0)
      return false;

    bool matching = true;

    for(int k = 0; k < 2; k++)
    {
      for(int j = 0; j < 4; j++)
      {
        matching = true;
        for(int i = 0; i < SIZE; i++)
        {
          matching &= data[i][0] == p->data[i][(SIZE-1)];
        }
        if(matching)
          break;
        else
          p->rotate();
      }
      if(matching)
        break;
      else
        p->flip();
    }

    if(matching)
    {
      p->locked = true;
      W = p;
      p->E = this;
      //std::cout << "Matched " << id << " West to " << p->id << std::endl;
    }
    return matching;
  }

  bool match(Puzzle * p)
  {
    if(checkNBoundary(p))
      return true;

    if(checkEBoundary(p))
      return true;

    if(checkSBoundary(p))
      return true;

    if(checkWBoundary(p))
      return true;

    return false;
  }
};


int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  std::vector<Puzzle *> pieces;
  std::vector<Puzzle *> board;
  Puzzle * ptr;
  int line_num = 0;

  do{
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      if(line_num == 0)
      {
        ptr = new Puzzle();
        pieces.push_back(ptr);
        sscanf(line.c_str(), "Tile %llu:", &(ptr->id));
        //std::cout << "Scanned " << ptr->id << std::endl;
        line_num = 1;
      }
      else
      {
        //std::cout << line << std::endl;
        for(int i = 0; i < SIZE; i++)
        {
          ptr->data[line_num-1][i] = line[i] == '#';
        }
        line_num = line_num == SIZE ? 0 : line_num + 1;
      }
    }
  }while(!input.eof());

  board.push_back(pieces[0]);
  board[0]->locked = true;
  pieces.erase(pieces.begin() + 0);

  while(pieces.size() > 0)
  {
      //std::cout << "Board: " << board.size() << ", Pieces: " << pieces.size() << std::endl;
      for(int i = 0; i < board.size(); i++)
      {
        for(int j = 0; j < pieces.size(); j++)
        {
          if(board[i]->match(pieces[j]))
          {
            board.push_back(pieces[j]);
            pieces.erase(pieces.begin() + j);
          }
        }
        for(int j = 0; j < board.size(); j++)
        {
          if(i != j)
            board[i]->match(board[j]);
        }
      }
  }

  // Create image

  Puzzle * col_start;
  Puzzle * current;
  int x = 0;
  int y = 0;

  for(int i = 0; i < board.size(); i++)
  {
    if(board[i]->is_sw_corner())
    {
      col_start = board[i];
      break;
    }
  }

  do{
    current = col_start;
    x = 0;
    do{
      for(int i = 0; i < SIZE-2; i++)
      {
        for(int j = 0; j < SIZE-2; j++)
        {
          image[std::pair<int, int>(y+i, x+j)] = current->data[i+1][j+1];
        }
      }
      x+=(SIZE-2);
      current = current->E;
    }while(current != 0);
    y+=(SIZE-2);
    col_start = col_start->N;
  }while(col_start != 0);
  std::cout << "X: " << x << ", Y: " << y << std::endl;


  int rough = 0;
  for(int i = 0; i < y; i++)
  {
    for(int j = 0; j < x; j++)
    {
      rough += image[std::pair<int, int>(i, j)] ? 1 : 0;
    }
  }


  int sea_monsters = 0;

  int iters = 0;

  do{

    for(int i = 0; i < y; i++)
    {
      for(int j = 0; j < x; j++)
      {
        bool found = true;

        for(int k = 0; k < 20; k++)
        {
          for(int l = 0; l < 3; l++)
          {
            if(sea_monster[l][k])
            {
              found &= image[std::pair<int, int>(i+l, j+k)];
            }
          }
        }
        if(found)
          sea_monsters++;
      }
    }

    if(iters < 4)
    {
      image = rotate(image, x, y);
      iters++;
    }
    else
    {
      image = flip(image, x, y);
      iters = 0;
    }
  }while(sea_monsters == 0);

  std::cout << sea_monsters << " sea monsters found" << std::endl;
  std::cout << "Rough Val: " << rough - (15*sea_monsters) << std::endl;

  long long unsigned int product = 1;

  for(int i = 0; i < board.size(); i++)
  {
    if(board[i]->is_corner())
      product *= board[i]->id;
    delete(board[i]);
  }
  std::cout << "Product: " << product << std::endl;
}
