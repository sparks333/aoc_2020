#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <thread>
#include <map>

#define VERBOSE 0
#define MAX_RUNS 10000000
#define N_CUPS 1000000

struct cup
{
  cup * cw;
  cup * ccw;
  int value;
};

std::map<int, cup *> search_map;

void print_board(cup * current)
{
  cup * local = current;
  std::cout << "Cups: ";
  do{
    std::cout << local->value << " ";
    local = local->cw;
  }while(local != current);
  std::cout << std::endl;
}

cup * add_cup(cup * current, cup * new_cup)
{
  cup * cw_cup = current->cw;
  cup * ccw_cup = current->ccw;
  current->cw = new_cup;
  new_cup->cw = cw_cup;
  new_cup->ccw = current;
  cw_cup->ccw = new_cup;
  return new_cup;
}

cup * remove_cup(cup * current)
{
  current->cw->ccw = current->ccw;
  current->ccw->cw = current->cw;
  int val = current->value;
  current->cw = 0;
  current->ccw = 0;
  return current;
}

int main()
{
  int cups[] = {7, 8, 9, 4, 6, 5, 1, 2, 3};

  cup * current = new cup;
  cup * head = current;
  current->value = cups[0];

  search_map[cups[0]] = current;

  for(int i = 1; i < sizeof(cups)/sizeof(int); i++)
  {
    cup * prev = current;
    current = new cup;

    prev->cw = current;
    current->ccw = prev;
    current->value = cups[i];
    search_map[cups[i]] = current;
  }

  int value = (sizeof(cups)/sizeof(int)) + 1;

  for(int i = sizeof(cups)/sizeof(int); i < N_CUPS; i++)
  {
    cup * prev = current;
    current = new cup;

    prev->cw = current;
    current->ccw = prev;
    current->value = value;
    search_map[value] = current;
    value++;
  }

  current->cw = head;
  head->ccw = current;

  current = head;

  for(int i = 0; i < MAX_RUNS; i++)
  {
#if VERBOSE
    std::cout << std::endl << "-- move " << i+1 << " --" << std::endl;
    print_board(current);
#endif
    cup * cup_1 = remove_cup(current->cw);
    cup * cup_2 = remove_cup(current->cw);
    cup * cup_3 = remove_cup(current->cw);

#if VERBOSE
    std::cout << "Pick up: " << cup_1->value << " " << cup_2->value << " " << cup_3->value << std::endl;
#endif
    int target_val = ((current->value - 1) < 1) ? N_CUPS : current->value - 1;

    cup * search_cup;
    bool done = false;
    while(!done)
    {
      if(target_val == cup_1->value || target_val == cup_2->value || target_val == cup_3->value)
      {
        target_val = ((target_val - 1) < 1) ? N_CUPS : target_val - 1;
      }
      else
      {
        search_cup = search_map[target_val];
        search_cup = add_cup(search_cup, cup_1);
        search_cup = add_cup(search_cup, cup_2);
        search_cup = add_cup(search_cup, cup_3);
        done = true;
      }
    }
    current = current->cw;
  }
#if VERBOSE
  std::cout << std::endl;
  std::cout << "-- final --" << std::endl;
  print_board(current);
#endif

  while(current->value != 1)
  {
    current = current->cw;
  }

  cup * cw_1 = current->cw;
  cup * cw_2 = cw_1->cw;

#if VERBOSE
  print_board(current->cw);
#endif

  unsigned long long val1 = (cw_1->value);
  unsigned long long val2 = (cw_2->value);

  std::cout << "Val1: " << val1 << ", Val2: " << val2 << ", Final value: " <<  val1 * val2 << std::endl;

}
