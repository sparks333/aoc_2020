#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <deque>
#include <map>

#define VERBOSE 0

int play_hand(std::deque<int> d1, std::deque<int> d2, int game)
{

  std::map<std::pair<std::deque<int>, std::deque<int> >, bool> game_history;

#if VERBOSE
  std::cout << "=== Game " << game << " ===" << std::endl;
  std::cout << std::endl;
#endif
  int round = 1;

  while(d1.size() > 0 && d2.size() > 0)
  {
    if(game_history[std::pair<std::deque<int>, std::deque<int> >(d1, d2)])
    {
#if VERBOSE
        std::cout << "We've played this game before, Player 1 wins!" << std::endl;
#endif
        return 1;
    }
    game_history[std::pair<std::deque<int>, std::deque<int> >(d1, d2)] = true;

#if VERBOSE
    std::cout << "-- Round " << round << " (Game " << game << ") --" << std::endl;

    std::cout << "Player 1's deck: ";
    for(int i = 0; i < d1.size(); i++)
    {
      std::cout << d1[i];
      if(i == (d1.size()-1))
        std::cout << std::endl;
      else
        std::cout << ", ";
    }

    std::cout << "Player 2's deck: ";
    for(int i = 0; i < d2.size(); i++)
    {
      std::cout << d2[i];
      if(i == (d2.size()-1))
        std::cout << std::endl;
      else
        std::cout << ", ";
    }
#endif

    int card_1 = d1[0];
    d1.pop_front();
    int card_2 = d2[0];
    d2.pop_front();

#if VERBOSE
    std::cout << "Player 1 plays: " << card_1 << std::endl;
    std::cout << "Player 2 plays: " << card_2 << std::endl;
#endif

    if(d1.size() >= card_1 && d2.size() >= card_2)
    {
#if VERBOSE
      std::cout << "Playing a sub-game to determine the winner..." << std::endl;
      std::cout << std::endl;
#endif

      std::deque<int> sub_deck1(d1.begin(), d1.begin() + card_1);
      std::deque<int> sub_deck2(d2.begin(), d2.begin() + card_2);

      if(play_hand(sub_deck1, sub_deck2, game+1) == 1)
      {
#if VERBOSE
        std::cout << "Player 1 wins round " << round << " of game " << game << "!" << std::endl;
#endif
        d1.push_back(card_1);
        d1.push_back(card_2);
      }
      else
      {
#if VERBOSE
        std::cout << "Player 2 wins round " << round << " of game " << game << "!" << std::endl;
#endif
        d2.push_back(card_2);
        d2.push_back(card_1);
      }
    }
    else if(card_1 > card_2)
    {
#if VERBOSE
      std::cout << "Player 1 wins round " << round << " of game " << game << "!" << std::endl;
#endif
      d1.push_back(card_1);
      d1.push_back(card_2);
    }
    else
    {
#if VERBOSE
      std::cout << "Player 2 wins round " << round << " of game " << game << "!" << std::endl;
#endif
      d2.push_back(card_2);
      d2.push_back(card_1);
    }
    round++;
#if VERBOSE
    std::cout << std::endl;
#endif
  }
  if(d1.size() == 0)
  {
#if VERBOSE
    std::cout << "The winner of game " << game << " is player 2!" << std::endl;
#endif
    if(game > 1)
    {
#if VERBOSE
      std::cout << "...anyway, back to game " << game-1 << std::endl;
#endif
    }
    else
    {
      int score = 0;
#if VERBOSE
      std::cout << "Player 2 wins the game!" << std::endl;
      std::cout << "Player 2's deck: ";
#endif
      for(int i = 0; i < d2.size(); i++)
      {
#if VERBOSE
        std::cout << d2[i];
        if(i == (d2.size()-1))
          std::cout << std::endl;
        else
          std::cout << ", ";
#endif
        score += (i+1)*d2[(d2.size() - i) - 1];
      }
      std::cout << "Score: " << score << std::endl;
    }
#if VERBOSE
    std::cout << std::endl;
#endif
    return 2;
  }
  else
  {
#if VERBOSE
    std::cout << "The winner of game " << game << " is player 1!" << std::endl;
#endif
    if(game > 1)
    {
#if VERBOSE
      std::cout << "...anyway, back to game " << game-1 << std::endl;
#endif
    }
    else
    {
      int score = 0;
#if VERBOSE
      std::cout << "Player 1 wins the game!" << std::endl;
      std::cout << "Player 1's deck: ";
#endif
      for(int i = 0; i < d1.size(); i++)
      {
#if VERBOSE
        std::cout << d1[i];
        if(i == (d1.size()-1))
          std::cout << std::endl;
        else
          std::cout << ", ";
#endif
        score += (i+1)*d1[(d1.size() - i) - 1];
      }
      std::cout << "Score: " << score << std::endl;
    }
#if VERBOSE
    std::cout << std::endl;
#endif
    return 1;
  }
}

int main()
{
  std::string line;
  std::ifstream input;
  input.open("input.txt", std::ifstream::binary);

  std::deque<int> deck_1, deck_2;

  int state = 0;

  do{
    std::getline(input, line, '\n');
    if(line.size() > 1)
    {
      switch(state)
      {
        case 0:
          if(line[0] == 'P')
          {
            state = 1;
          }
          break;
        case 1:
          if(line[0] == 'P')
          {
            state = 2;
          }
          else
          {
            deck_1.push_back(stoi(line));
          }
          break;
        case 2:
            deck_2.push_back(stoi(line));
            break;
      }
    }
  }while(!input.eof());

  int winner = play_hand(deck_1, deck_2, 1);

}
