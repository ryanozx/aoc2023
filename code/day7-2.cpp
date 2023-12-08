#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Hand {
public:
  Hand() {
    hand = "";
    bid = 0;
    type = 0;
  }

  Hand(const Hand& other) {
    this->hand = other.hand;
    this->bid = other.bid;
    this->type = other.type;
  }

  Hand(string &hand, int bid) {
    this->hand = hand;
    this->bid = bid;
    this->type = calculateType(hand);
  }

  bool operator< (const Hand &other) const {
    if (this->type < other.type) {
      return true;
    } else if (this->type == other.type) {
      for (int i = 0; i < NUM_CARDS; ++i) {
        int cardVal = getCardValue(this->hand[i]);
        int otherCardVal = getCardValue(other.hand[i]);
        if (cardVal == otherCardVal) {
          continue;
        }
        return cardVal < otherCardVal;
      }
      return true;
    }
    return false;
  }

  int getBid() {
    return bid;
  }

  short getType() {
    return type;
  }
    
private:
  string hand;
  short type;
  int bid;

  static const int NUM_CARD_TYPES = 13;
  static const int NUM_CARDS = 5;
  static const int J_POS = 0;

  static int getCardValue(char c) {
    switch(c) {
    case 'A':
      return 12;
    case 'K':
      return 11;
    case 'Q':
      return 10;
    case 'J':
      return 0;
    case 'T':
      return 9;
    default:
      if (c >= '2' && c <= '9') {
        return c - '2' + 1;
      }
    }
    return -1;
  }

  static short calculateType(string &hand) {
    short numCards[NUM_CARD_TYPES];
    memset(numCards, 0, sizeof(numCards));

    for (char c: hand) {
      int cardPos = getCardValue(c);
      if (cardPos != -1) {
        numCards[cardPos]++;
      }
    }

    if (isFiveKind(numCards)) {
      return 7;
    } else if (isFourKind(numCards)) {
      return 6;
    } else if (isFullHouse(numCards)) {
      return 5;
    } else if (isThreeKind(numCards)) {
      return 4;
    } else if (isTwoPair(numCards)) {
      return 3;
    } else if (isOnePair(numCards)) {
      return 2;
    } else {
      return 1;
    }
  }

  static bool isFiveKind(short numCards[]) {
    for (int i = 0; i < NUM_CARD_TYPES; ++i) {
      if (i == J_POS) {
        continue;
      }
      if (numCards[i] + numCards[J_POS] == 5) {
        return true;
      }
    }
    return false;
  }

  static bool isFourKind(short numCards[]) {
    for (int i = 0; i < NUM_CARD_TYPES; ++i) {
      if (i == J_POS) {
        continue;
      }
      if (numCards[i] + numCards[J_POS] == 4) {
        return true;
      }
    }
    return false;
  }

  static bool isFullHouse(short numCards[]) {
    bool hasThree = false;
    short twoCount = 0;
    for (int i = 0; i < NUM_CARD_TYPES; ++i) {
      if (i == J_POS) {
        continue;
      }
      if (numCards[i] == 3) {
        hasThree = true;
      } else if (numCards[i] == 2) {
        ++twoCount;
      }
    }
    return (hasThree && twoCount == 1)
      || (twoCount == 2 && numCards[J_POS] == 1);
  }

  static bool isThreeKind(short numCards[]) {
    bool hasThree = false;
    short oneCount = 0;
    for (int i = 0; i < NUM_CARD_TYPES; ++i) {
      if (i == J_POS) {
        continue;
      }
      if (numCards[i] == 3) {
        hasThree = true;
      } else if (numCards[i] == 1) {
        ++oneCount;
      }
    }
    return (hasThree && oneCount == 2)
      || (oneCount == 3 && numCards[J_POS] == 2)
      || (!hasThree && oneCount == 2 && numCards[J_POS] == 1);
  }

  static bool isTwoPair(short numCards[]) {
    short twoCount = 0;
    for (int i = 0; i < NUM_CARD_TYPES; ++i) {
      if (i == J_POS) {
        continue;
      }
      if (numCards[i] == 2) {
        ++twoCount;
      }
    }
    return twoCount == 2 && numCards[J_POS] == 0;
  }

  static bool isOnePair(short numCards[]) {
    short oneCount = 0;
    short twoCount = 0;
    for (int i = 0; i < NUM_CARD_TYPES; ++i) {
      if (i == J_POS) {
        continue;
      }
      if (numCards[i] == 2) {
        ++twoCount;
      } else if (numCards[i] == 1) {
        ++oneCount;
      }
    }
    return (twoCount == 1 && oneCount == 3)
      || (oneCount == 4 && numCards[J_POS] == 1);
  }
};

const int NUM_HANDS = 1000;

int main() {
  Hand hands[NUM_HANDS];
  int handCount = 0;
 
  string hand;
  int bid;
  while (cin >> hand >> bid) {
    hands[handCount++] = Hand(hand, bid);
  }

  sort(hands, hands + handCount);

  long long totalWinnings = 0LL;
  for (int i = 0; i < handCount; ++i) {
    //printf("%d: Type %d Bid %d\n", i + 1, hands[i].getType(), hands[i].getBid());
    totalWinnings += (i + 1) * hands[i].getBid();
  }
  printf("%lld\n", totalWinnings);
  return 0;
}
