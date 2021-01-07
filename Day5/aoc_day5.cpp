#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt");


  std::string user;

  bool first = true;

  int max_id = 0;

  bool seat_taken[999] = {false};

  do
  {
    std::getline(input, line, '\n');

    if(line.length() != 11)
      continue;

    int min_row = 0;
    int max_row = 127;
    int min_col = 0;
    int max_col = 7;

    int incr = 64;

    for(int i = 0; i < 7; i++)
    {
      if(line[i] == 'F')
      {
        max_row -= incr;
      }
      else
      {
        min_row += incr;
      }
      incr /= 2;
    }

    incr = 4;

    for(int i = 7; i < 10; i++)
    {
      if(line[i] == 'L')
      {
        max_col -= incr;
      }
      else
      {
        min_col += incr;
      }
      incr /= 2;
    }

    int id = min_row * 8 + min_col;

    seat_taken[id] = true;

    std::cout << "Row: " << min_row << ", Col: " << min_col << ", ID: " << id << std::endl;

    max_id = id > max_id ? id : max_id;

  }while(!input.eof());

  std::cout << "Max ID: " << max_id << std::endl;

  for(int i = 1; i < 998; i++)
  {
    if(!seat_taken[i] && seat_taken[i-1] && seat_taken[i+1])
    {
      std::cout << "Seat ID " << i << " not taken" << std::endl;
    }
  }


  input.close();
}
