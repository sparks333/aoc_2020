#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <deque>
#include <map>

#define VERBOSE 1

#define SUBJECT_NUM
#define LOOP_SIZE
#define MAGIC_NUM 20201227ULL

#define CARD_PUBLIC_KEY 8421034
#define DOOR_PUBLIC_KEY 15993936

#define CARD_SUBJECT_NUM  7
#define DOOR_SUBJECT_NUM  7

int transform(long long int subject_num, long long int loop_size)
{
  long long int value = 1;
  for(int i = 0; i < loop_size; i++)
  {
    value *= subject_num;
    value %= MAGIC_NUM;
  }
  return value;
}

int main()
{
  long long int card_subject_num = CARD_SUBJECT_NUM;
  long long int card_value = 1;
  long long int card_loop_size = 0;
  while(card_value != CARD_PUBLIC_KEY)
  {
    card_value *= card_subject_num;
    card_value %= MAGIC_NUM;
    card_loop_size++;
  }

  long long int door_subject_num = CARD_SUBJECT_NUM;
  long long int door_value = 1;
  long long int door_loop_size = 0;
  while(door_value != CARD_PUBLIC_KEY)
  {
    door_value *= door_subject_num;
    door_value %= MAGIC_NUM;
    door_loop_size++;
  }

  std::cout << "Door Encryption Key: " << transform(DOOR_PUBLIC_KEY, card_loop_size) << std::endl;

}
