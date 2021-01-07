#include <iostream>
#include <fstream>
#include <cstring>

#define LINE_LENGTH 31

int num_trees_hit(int right, int down)
{
  std::string line;
  std::ifstream input;
  input.open("input.txt");

  int pos = 0;
  int tree_count = 0;

  do
  {
    std::getline(input, line, '\n');

    if(line[pos % LINE_LENGTH] == '#')
    {
      line[pos % LINE_LENGTH] = 'X';
      tree_count++;
    }
    else
    {
      line[pos % LINE_LENGTH] = 'O';
    }

    //std::cout << line << std::endl;


    for(int i = 1; i < down; i++)
    {
      std::getline(input, line, '\n');
      //std::cout << line << std::endl;
    }

    pos+=right;

  }while(!input.eof());

  std::cout << tree_count << " trees" << std::endl;

  input.close();

  return tree_count;
}

int main()
{
  int r1_d1 = num_trees_hit(1, 1);
  int r3_d1 = num_trees_hit(3, 1);
  int r5_d1 = num_trees_hit(5, 1);
  int r7_d1 = num_trees_hit(7, 1);
  int r1_d2 = num_trees_hit(1, 2);

  unsigned int total_trees = r1_d1 * r3_d1 * r5_d1 * r7_d1 * r1_d2;

  std::cout << "Product: " << total_trees << std::endl;

}
