#include <array>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <exception>

const int kCntOfPiles = 8;
const int kCardsInPile = 9;

const std::array<char, kCardsInPile> kCards = // backwardTransform
  {'6', '7', '8', '9', 't', 'J', 'Q', 'K', 'A'};
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
  std::cout << "Input Game:" << std::endl;
  TState data(kCntOfPiles);

  char priority;
  std::map<char, int> cntOfCards;
  for (int i = 0; i < kCntOfPiles; ++i) {
    for (int j = 0; j < kCardsInPile; ++j) {
      std::cin >> priority;  
      if (std::find(kCards.begin(), kCards.end(), priority) == kCards.end()) {
        throw std::logic_error("Invalid Input: Bad Character");
      }
      ++cntOfCards[priority];
      
      priority = forwardTransform[priority];
      data[i].push_back(priority);
    }
  }

  for(auto kv : cntOfCards) {
    if (kv.second != 8) {
      throw std::logic_error("Invalid Input: Bad Cnt of Cards");
    }
  }

  std::cout << "Input End" << std::endl;

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

  std::cout << "Print State:" << std::endl;
  for(int i = 0; i < kCntOfPiles; ++i) {
    for(int j = 0; j < state[i].size(); ++j) {
      std::cout << kCards[state[i][j]];
    }
    std::cout << std::endl;
  }
  std::cout << "End of State" << std::endl;
}

int tryFindAns(const TState& start) {
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
          return iteratation;
        }

        if (!achievable.contains(cur)) {
          achievable.insert(cur);
          qCur.push(std::move(cur));
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
              qNext.push(std::move(newState));
            }
          }
        }
      }
    }

    ++iteratation;
    std::swap(qCur, qNext);
  }

  return -1;
}

int main() {
  TState start = readData();

  printState(start);
  

  auto ans = tryFindAns(start);
  if (ans == -1) {
    std::cout << "No Solution!!!";
  } else {
    if (ans == 0) {
      std::cout << "It's already been solved" << std::endl;
    }
    std::cout << "Can Solve by " << ans << " step";
    if (ans != 1) {
      std::cout << 's';
    }
  }

}