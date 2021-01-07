#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

int main()
{
  std::string line, token;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  std::getline(input, line, '\n');

  int width = line.size() - 1;

  std::cout << "Width: " << width << std::endl;

  input.seekg(0, input.end);
  int height = (input.tellg()) / (width+2);

  std::cout << "Height: " << height << std::endl;
  input.seekg(0, input.beg);

  unsigned int * arraymap = (unsigned int * ) malloc(height*width*sizeof(unsigned int));

  if(arraymap == NULL)
  {
    std::cout << "Error! Cannot allocate" << std::endl;
    return -1;
  }

  unsigned int * new_arraymap = (unsigned int * ) malloc(height*width*sizeof(unsigned int));
  if(new_arraymap == NULL)
  {
    std::cout << "Error! Cannot allocate" << std::endl;
    return -1;
  }

  int i = 0, j = 0;

  do
  {
    std::getline(input, line, '\n');

    if(line.length() > 1)
    {
      for(i = 0; i < line.length(); i++)
      {
        if(line[i] == '.')
        {
          arraymap[j*width + i] = 0;
        }
        if(line[i] == 'L')
        {
          arraymap[j*width + i] = 1;
        }
        if(line[j*width + i] == '#')
        {
          arraymap[j*width + i] = 2;
        }
      }
      j++;
    }
  }while(!input.eof());

  bool changes;
  int occupied;

  do
  {
    changes = false;
    occupied = 0;
    for(j = 0; j < height; j++)
    {
      for(i = 0; i < width; i++)
      {

        bool left_bound = (i-1) < 0;
        bool right_bound = (i+1) > (width-1);
        bool up_bound = (j-1) < 0;
        bool down_bound = (j+1) > (height-1);

        if(arraymap[j*width + i] == 0)
        {
          new_arraymap[j*width + i] = 0;
        }

        if(arraymap[j*width + i] == 1)
        {
          // Empty Seat
          int num_occupied = 0;
          bool search_done = false;

          int sub_i, sub_j;
          bool ul_visible = false;
          bool uc_visible = false;
          bool ur_visible = false;
          bool cl_visible = false;
          bool cr_visible = false;
          bool ll_visible = false;
          bool lc_visible = false;
          bool lr_visible = false;

          sub_i = i-1;
          sub_j = j-1;
          search_done = false;

          while(sub_i >= 0 && sub_j >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              ul_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i--;
              sub_j--;
          }

          sub_i = i;
          sub_j = j-1;
          search_done = false;

          while(sub_j >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              uc_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_j--;
          }

          sub_i = i+1;
          sub_j = j-1;
          search_done = false;

          while(sub_i < width && sub_j >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              ur_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i++;
              sub_j--;
          }

          sub_i = i-1;
          sub_j = j;
          search_done = false;

          while(sub_i >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              cl_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i--;
          }

          sub_i = i+1;
          sub_j = j;
          search_done = false;

          while(sub_i < width && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              cr_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i++;
          }

          sub_i = i-1;
          sub_j = j+1;
          search_done = false;

          while(sub_i >= 0 && sub_j < height && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              ll_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i--;
              sub_j++;
          }

          sub_i = i;
          sub_j = j+1;
          search_done = false;

          while(sub_j < height && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              lc_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_j++;
          }

          sub_i = i+1;
          sub_j = j+1;
          search_done = false;

          while(sub_i < width && sub_j < height && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              lr_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i++;
              sub_j++;
          }

          num_occupied += ul_visible ? 1 : 0;
          num_occupied += uc_visible ? 1 : 0;
          num_occupied += ur_visible ? 1 : 0;
          num_occupied += cl_visible ? 1 : 0;
          num_occupied += cr_visible ? 1 : 0;
          num_occupied += ll_visible ? 1 : 0;
          num_occupied += lc_visible ? 1 : 0;
          num_occupied += lr_visible ? 1 : 0;

          /* Part 1
          num_occupied += left_bound || up_bound ? 0 : arraymap[(j-1)*width + (i-1)] == 2 ? 1 : 0;
          num_occupied += up_bound ? 0 : arraymap[(j-1)*width + (i+0)] == 2 ? 1 : 0;
          num_occupied += right_bound || up_bound ? 0 : arraymap[(j-1)*width + (i+1)] == 2 ? 1 : 0;

          num_occupied += left_bound ? 0 : arraymap[(j+0)*width + (i-1)] == 2 ? 1 : 0;
          num_occupied += right_bound ? 0 : arraymap[(j+0)*width + (i+1)] == 2 ? 1 : 0;

          num_occupied += left_bound || down_bound ? 0 : arraymap[(j+1)*width + (i-1)] == 2 ? 1 : 0;
          num_occupied += down_bound ? 0 : arraymap[(j+1)*width + (i+0)] == 2 ? 1 : 0;
          num_occupied += right_bound || down_bound ? 0 : arraymap[(j+1)*width + (i+1)] == 2 ? 1 : 0;
          */
          if(num_occupied == 0)
          {
            new_arraymap[j*width + i] = 2;
            changes |= true;
            occupied++;
          }
          else
          {
            new_arraymap[j*width + i] = 1;
          }
        }

        if(arraymap[j*width + i] == 2)
        {
          int num_occupied = 0;

          int sub_i, sub_j;
          bool ul_visible = false;
          bool uc_visible = false;
          bool ur_visible = false;
          bool cl_visible = false;
          bool cr_visible = false;
          bool ll_visible = false;
          bool lc_visible = false;
          bool lr_visible = false;
          bool search_done = false;

          sub_i = i-1;
          sub_j = j-1;
          search_done = false;

          while(sub_i >= 0 && sub_j >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              ul_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i--;
              sub_j--;
          }

          sub_i = i;
          sub_j = j-1;
          search_done = false;

          while(sub_j >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              uc_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_j--;
          }

          sub_i = i+1;
          sub_j = j-1;
          search_done = false;

          while(sub_i < width && sub_j >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              ur_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i++;
              sub_j--;
          }

          sub_i = i-1;
          sub_j = j;
          search_done = false;

          while(sub_i >= 0 && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              cl_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i--;
          }

          sub_i = i+1;
          sub_j = j;
          search_done = false;

          while(sub_i < width && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              cr_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i++;
          }

          sub_i = i-1;
          sub_j = j+1;
          search_done = false;

          while(sub_i >= 0 && sub_j < height && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              ll_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i--;
              sub_j++;
          }

          sub_i = i;
          sub_j = j+1;
          search_done = false;

          while(sub_j < height && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              lc_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_j++;
          }

          sub_i = i+1;
          sub_j = j+1;
          search_done = false;

          while(sub_i < width && sub_j < height && !search_done)
          {
              search_done = arraymap[sub_j*width + sub_i] > 0;
              lr_visible = arraymap[sub_j*width + sub_i] == 2;
              sub_i++;
              sub_j++;
          }

          num_occupied += ul_visible ? 1 : 0;
          num_occupied += uc_visible ? 1 : 0;
          num_occupied += ur_visible ? 1 : 0;
          num_occupied += cl_visible ? 1 : 0;
          num_occupied += cr_visible ? 1 : 0;
          num_occupied += ll_visible ? 1 : 0;
          num_occupied += lc_visible ? 1 : 0;
          num_occupied += lr_visible ? 1 : 0;

          /* Part 1
          num_occupied += left_bound || up_bound ? 0 : arraymap[(j-1)*width + (i-1)] == 2 ? 1 : 0;
          num_occupied += up_bound ? 0 : arraymap[(j-1)*width + (i+0)] == 2 ? 1 : 0;
          num_occupied += right_bound || up_bound ? 0 : arraymap[(j-1)*width + (i+1)] == 2 ? 1 : 0;

          num_occupied += left_bound ? 0 : arraymap[(j+0)*width + (i-1)] == 2 ? 1 : 0;
          num_occupied += right_bound ? 0 : arraymap[(j+0)*width + (i+1)] == 2 ? 1 : 0;

          num_occupied += left_bound || down_bound ? 0 : arraymap[(j+1)*width + (i-1)] == 2 ? 1 : 0;
          num_occupied += down_bound ? 0 : arraymap[(j+1)*width + (i+0)] == 2 ? 1 : 0;
          num_occupied += right_bound || down_bound ? 0 : arraymap[(j+1)*width + (i+1)] == 2 ? 1 : 0;
          */

          if(num_occupied >= 5)
          {
            new_arraymap[j*width + i] = 1;
            changes |= true;
          }
          else
          {
            new_arraymap[j*width + i] = 2;
            occupied++;
          }
        }
      }
    }

    memcpy(arraymap, new_arraymap, width*height*sizeof(unsigned int));

    std::cout << "Step, " << occupied << " seats occupied" << std::endl;
   }
  while(changes);

  std::cout << "Done!" << std::endl;

  input.close();
}
