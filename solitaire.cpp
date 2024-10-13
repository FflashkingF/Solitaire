#include <array>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>

const int kCntOfPiles = 8;
const int kCardsInPile = 9;

std::map<char, char> forwardTransform = 
  { {'6', 0}, {'7', 1}, {'8', 2}, {'9', 3}, {'t', 4}, {'J', 5}, {'Q', 6}, {'K', 7}, {'A', 8}};

using TPile = std::string;
using TState = std::vector<TPile>;

bool isGood(const TState& state, int indexOfPile) {
  if (state[indexOfPile].size() < kCardsInPile) {
    return false;
  }
  for (int i = 0; i < kCardsInPile; ++i) {
    if (state[indexOfPile][state[indexOfPile].size() - i - 1] != i) {
      return false;
    }
  }

  return true;
}

TState readData() {
  TState data(kCntOfPiles);

  char priority;
  for (int i = 0; i < kCntOfPiles; ++i) {
    for (int j = 0; j < kCardsInPile; ++j) {
      std::cin >> priority;  
      // TODO check correctness
      
      priority = forwardTransform[priority];
      data[i].push_back(priority);
    }
  }

  return data;
}

bool isWin(const TState& state) {
  for (int i = 0; i < kCntOfPiles; ++i) {
    if (!state[i].empty()) {
      return false;
    }
  }

  return true;
}

int getCntOfCards(const TState& state) {
  int cntOfCards = 0;
  for (int i = 0; i < kCntOfPiles; ++i) {
    cntOfCards += state[i].size();
  }

  return cntOfCards;
}

int getCntOfNines(const TState& state) {
  return getCntOfCards(state) / 9;
}

void printState(const TState& state) {
  const std::array<char, kCardsInPile> kCards = // backwardTransform
   {'6', '7', '8', '9', 't', 'J', 'Q', 'K', 'A'};

  std::cout << "Print State:" << std::endl;
  for(int i = 0; i < kCntOfPiles; ++i) {
    for(int j = 0; j < state[i].size(); ++j) {
      std::cout << kCards[state[i][j]];
    }
    std::cout << std::endl;
  }
  std::cout << "End of State" << std::endl;
}

std::pair<bool, int> IsCan(const TState& start) {
  std::queue<TState> qCur, qNext;
  qCur.push(start);
  std::set<TState> achievable;

  int iteratation = 0;
  while(!qCur.empty()) {
    while(!qCur.empty()) {
      TState cur = qCur.front();
      // printState(cur);
      qCur.pop();

      bool canOptimize = false;
      for (int i = 0; i < kCntOfPiles; ++i) {
        if (isGood(cur, i)) {
          cur[i].resize(cur[i].size() - kCardsInPile);
          canOptimize = true;
        }
      }
      if(canOptimize) {
        // printState(cur);
        if (isWin(cur)) {
          return {true, iteratation};
        }

        if (!achievable.contains(cur)) {
          achievable.insert(cur);
          qCur.push(cur);
        }

        continue;
      }

      for (int indFrom = 0; indFrom < kCntOfPiles; ++indFrom) {
        if (cur[indFrom].empty()) {
          continue;
        }

      
        for (int indTo = 0; indTo < kCntOfPiles; ++indTo) {
          if (cur[indTo].empty() || cur[indFrom].back() < cur[indTo].back()) {
            TState newState = cur;
            newState[indTo].push_back(cur[indFrom].back());
            newState[indFrom].pop_back();

            if (!achievable.contains(newState)) {
              achievable.insert(newState);
              qNext.push(newState);
            }
          }
        }
      }
    }

    ++iteratation;
    std::swap(qCur, qNext);
  }

  return {false, -1};
}

int main() {
  TState start = readData();

  printState(start);
  

  auto ans = IsCan(start);
  std::cout << ans.first << '\n' << ans.second;
}