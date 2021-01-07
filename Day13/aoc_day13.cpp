#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>

long long find_mod_inverse(long long val, long long mod)
{
  for(long long i = 0; i < mod; i++)
  {
    if(i*val % mod == 1)
      return i;
  }
  return 0;
}

int main()
{
  std::string line, token;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  std::vector<int> ids;
  std::vector<int> offsets;

  int way_y = 1, way_x = 10;
  int pos_y = 0, pos_x = 0, h = 90;

  std::getline(input, line, '\n');
  unsigned int timestamp = atoi(line.c_str());
  std::getline(input, line, '\n');

  unsigned int max_id = 0;
  unsigned int max_id_index = 0;

  std::istringstream line_stream(line.c_str());

  int offset = 0;

  do{
    std::getline(line_stream, token, ',');
    if(token[0] == 'x')
    {
      offset++;
      continue;
    }
    else
    {
      unsigned int id = atoi(token.c_str());
      ids.push_back(id);
      offsets.push_back(offset);
      if(max_id < id)
      {
        max_id = id;
        max_id_index = offset;
      }
      offset++;
    }
  }while(!line_stream.eof());

  //for(int i = 0; i < offsets.size(); i++)
  //{
  //  offsets[i] -= max_id_index;
  //  std::cout << "Id: " << ids[i] << ", offset: " << offsets[i] << std::endl;
  //}

  bool done = false;

  //CRT
  unsigned long long N = 1;
  for(int i = 0; i < ids.size(); i++)
  {
    N *= ids[i];
  }

  std::cout << "N: " << N << std::endl;

  std::vector<unsigned long long> Y, Z, W;

  unsigned long long val = 0;

  for(int i = 0; i < ids.size(); i++)
  {
    Z.push_back(N/ids[i]);
    Y.push_back(find_mod_inverse(Z[i], ids[i]));
    W.push_back(Y[i]*Z[i]);
    std::cout << "Z: " << Z[i] << ", Y: " << Y[i] << ", W: " << W[i] << std::endl;

    val += offsets[i]*W[i];
  }
std::cout << val << std::endl;
std::cout << N - (val % N) << std::endl;



/*
  unsigned long test_timestamp = 1;

  for(int i = 0; i < ids.size(); i++)
  {
    test_timestamp *= ids[i];
  }

  int progress = 0;

  while(!done)
  {
    done = true;
    for(int i = 0; i < offsets.size(); i++)
    {
      done &= (test_timestamp + offsets[i]) % ids[i] == 0;
    }
    if(!done)
    {
      test_timestamp -= max_id;
      progress++;
      if(progress > 1000000)
      {
        progress = 0;
        std::cout << test_timestamp << std::endl;
      }
    }
    else
    {
      std::cout << "Timestamp: " << test_timestamp - max_id_index << std::endl;
      break;
    }
  }
*/
  input.close();
}
