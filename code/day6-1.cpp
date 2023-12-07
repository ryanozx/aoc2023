#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_ARR_SIZE = 4;

int readVals(int arr[], int arrSize);

int main() {
  int time[MAX_ARR_SIZE];
  int numTime = readVals(time, MAX_ARR_SIZE);
  int distance[MAX_ARR_SIZE];
  int numDistance = readVals(distance, MAX_ARR_SIZE);

  long long mult = 0LL;
  
  for (int i = 0; i < numTime; ++i) {
    int minTime = 0;
    for (int j = 1; j < time[i]; ++j) {
      if (j * (time[i] - j) > distance[i]) {
        minTime = j;
        break;
      }
    }

    if (minTime == 0) {
      mult *= 0;
      break;
    }

    int maxTime;
    for (int j = time[i] - 1; j >= minTime; --j) {
      if (j * (time[i] - j) > distance[i]) {
        maxTime = j;
        break;
      }
    }

    if (mult == 0LL) {
      mult = 1LL;
    }

    mult *= (maxTime - minTime + 1);
  }
  printf("%lld\n", mult);
  return 0;
}

int readVals(int arr[], int arrSize) {
  string line;
  getline(cin, line);

  string token;
  int numValues = 0;

  istringstream ss(line);
  while ((ss >> token) && numValues < arrSize) {
    if (token[0] < '0' || token[0] > '9') {
      continue;
    }
    int val = stoi(token);
    arr[numValues++] = val;
  }

  return numValues;
}
