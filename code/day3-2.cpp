#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int M = 150;

typedef pair<int, int> PII;

long long addGears(string schematic[], short board[][M], int lineCount, queue<PII> & symbols);

int main() {
  string schematic[M];
  string input;
  int lineCount = 0;
  while (getline(cin, input)) {
    schematic[lineCount++] = input;
  }

  short board[M][M];
  memset(board, 0, sizeof(board));

  queue<PII> symbols;
  for (int r = 0; r < lineCount; ++r) {
    for (int c = 0; c < lineCount; ++c) {
      if (schematic[r][c] != '.' && schematic[r][c] < '0' || schematic[r][c] > '9') {
        symbols.emplace(r, c);
      }
    }
  }

  long long output = addGears(schematic, board, lineCount, symbols);
  printf("%lld\n", output);
  return 0;
}

long long addGears(string schematic[], short board[][M], int lineCount, queue<PII> &symbols) {
  int xOffset[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
  int yOffset[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

  long long gearSum = 0LL;
  long long gearRatios[8];

  while (!symbols.empty()) {
    PII currSym = symbols.front();
    symbols.pop();

    for (int i = 0; i < 8; ++i) {
      int newC = currSym.second + xOffset[i];
      int newR = currSym.first + yOffset[i];

      if (schematic[newR][newC] >= '0' && schematic[newR][newC] <= '9' && !board[newR][newC]) {
        int startC;
        int endC;
        for (int c = newC; c >= 0 && schematic[newR][c] >= '0' && schematic[newR][c] <= '9'; --c) {
          if (c >= currSym.second - 1 && c <= currSym.second + 1) {
            board[newR][c] = 1;
          }
          startC = c;
        }

        for (int c = newC; c < lineCount && schematic[newR][c] >= '0' && schematic[newR][c] <= '9'; ++c) {
          if (c >= currSym.second - 1 && c <= currSym.second + 1) {
            board[newR][c] = 1;
          }
          endC = c;
        }

        long long currVal = 0LL;
        for (int i = startC; i <= endC; ++i) {
          currVal = currVal * 10 + schematic[newR][i] - '0';
        }
        gearRatios[board[currSym.first][currSym.second]++] = currVal;
      }
    }

    if (board[currSym.first][currSym.second] == 2) {
      gearSum += gearRatios[0] * gearRatios[1];
    }
  
    for (int i = 0; i < 8; ++i) {
      board[currSym.first + yOffset[i]][currSym.second + xOffset[i]] = 0;
    }
  }

  return gearSum;
}
