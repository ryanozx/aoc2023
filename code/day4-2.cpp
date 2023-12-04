#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

const int NUM_WIN_NO = 10;
const int NUM_CARD_NO = 25;
const int MAX_CARD = 100;
const int MAX_CARD_COUNT = 214;

bool isWinningCards[MAX_CARD];
long long cardCountDeductions[MAX_CARD_COUNT];

int countMatch(int winningNo[], int cardNums[], int winCount, int numCount);

int main() {
  memset(isWinningCards, 0, sizeof(isWinningCards));
  memset(cardCountDeductions, 0, sizeof(cardCountDeductions));
  string line;

  long long totalCards = 0LL;
  long long currCopyCount = 1LL;
  int cardIdx = 0;

  while (getline(cin, line)) {
    istringstream ss(line);
    string token;

    // clear "Card X:" from the stream
    for (int i = 0; i < 2; ++i) {
      ss >> token;
    }

    int winningNo[NUM_WIN_NO];
    int cardNums[NUM_CARD_NO];
    int winPos = 0;
    int cardPos = 0;
    bool isCardNum = false;

    while (ss >> token) {
      if (token[0] == '|') {
        isCardNum = true;
      } else {
        int readNum = stoi(token);
        if (isCardNum) {
          cardNums[cardPos++] = readNum;
        } else {
          winningNo[winPos++] = readNum;
        }
      }
    }
    
    totalCards += currCopyCount;
    int numMatches = countMatch(winningNo, cardNums, winPos, cardPos);

    if (!numMatches) {
      currCopyCount -= cardCountDeductions[cardIdx];
    } else {
      if (cardIdx + numMatches < MAX_CARD_COUNT) {
        cardCountDeductions[cardIdx + numMatches] += currCopyCount;
      }

      currCopyCount <<= 1;
      currCopyCount -= cardCountDeductions[cardIdx];
    }
    ++cardIdx;
  }
  
  printf("%lld\n", totalCards);
  return 0;
}

int countMatch(int winningNo[], int cardNums[], int winCount, int cardCount) {
  for (int i = 0; i < winCount; ++i) {
    isWinningCards[winningNo[i]] = true;
  }

  int wins = 0;
  for (int i = 0; i < cardCount; ++i) {
    wins += isWinningCards[cardNums[i]];
  }

  // cleanup
  for (int i = 0; i < winCount; ++i) {
    isWinningCards[winningNo[i]] = false;
  }

  return wins;
}
