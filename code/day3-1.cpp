#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int M = 150;

typedef pair<int, int> PII;

void markBoard(string schematic[], bool board[][M], int lineCount, queue<PII> & symbols);

long long addPartNums(string schematic[], bool board[][M], int lineCount);

int main() {
  string schematic[M];
  string input;
  int lineCount = 0;
  while (getline(cin, input)) {
    schematic[lineCount++] = input;
  }

  bool board[M][M];
  memset(board, 0, sizeof(board));

  queue<PII> symbols;
  for (int r = 0; r < lineCount; ++r) {
    for (int c = 0; c < lineCount; ++c) {
      if (schematic[r][c] != '.' && schematic[r][c] < '0' || schematic[r][c] > '9') {
        symbols.emplace(r, c);
      }
    }
  }

  markBoard(schematic, board, lineCount, symbols);
  long long output = addPartNums(schematic, board, lineCount);
  printf("%lld\n", output);
  return 0;
}

void markBoard(string schematic[], bool board[][M], int lineCount, queue<PII> &symbols) {
  int xOffset[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
  int yOffset[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

  while (!symbols.empty()) {
    PII currSym = symbols.front();
    symbols.pop();
    for (int i = 0; i < 8; ++i) {
      int newC = currSym.second + xOffset[i];
      int newR = currSym.first + yOffset[i];

      if (schematic[newR][newC] >= '0' && schematic[newR][newC] <= '9' && !board[newR][newC]) {
        for (int c = newC; c >= 0; --c) {
          if (schematic[newR][c] < '0' || schematic[newR][c] > '9') {
            break;
          }
          board[newR][c] = true;
        }

        for (int c = newC; c < lineCount; ++c) {
          if (schematic[newR][c] < '0' || schematic[newR][c] > '9') {
            break;
          }
          board[newR][c] = true;
        }
      }
    }
  }
}

long long addPartNums(string schematic[], bool board[][M], int lineCount) {
  long long ans = 0LL;
  long long currNum = 0LL;
  for (int r = 0; r < lineCount; ++r) {
    for (int c = 0; c < lineCount; ++c) {
      if (!board[r][c] && currNum) {
        ans += currNum;
        currNum = 0LL;
      } else if (board[r][c]) {
        currNum = currNum * 10 + (schematic[r][c] - '0');
      }
    }

    ans += currNum;
    currNum = 0LL;
  }

  return ans;
}
