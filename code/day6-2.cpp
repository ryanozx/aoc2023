#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

typedef pair<long double, long double> PDD;

const int MAX_ARR_SIZE = 4;

long long readVal();

PDD solveQuad(long long a, long long b, long long c);

int main() {
  long long time = readVal();
  long long dist = readVal();

  PDD roots = solveQuad(-1, time, -dist);
  long double root1 = min(roots.first, roots.second);
  long double root2 = max(roots.first, roots.second);
  long long minTime = ceill(root1);
  long long maxTime = floorl(root2);

  long long numWays = maxTime - minTime + 1;
  printf("%lld\n", numWays);
  return 0;
}

long long readVal() {
  string line;
  getline(cin, line);

  string token;
  int numValues = 0;

  string arr[MAX_ARR_SIZE];
  istringstream ss(line);
  while ((ss >> token) && numValues < MAX_ARR_SIZE) {
    if (token[0] < '0' || token[0] > '9') {
      continue;
    }
    arr[numValues++] = token;
  }

  string concatStr = "";
  for (int i = 0; i < numValues; ++i) {
    concatStr += arr[i];
  }

  return stoll(concatStr);
}

PDD solveQuad(long long a, long long b, long long c) {
  long double discSquared = b * b - 4 * a * c;
  long double disc = sqrt(discSquared);

  long double root1 = (-b - disc) / (2 * a);
  long double root2 = (-b + disc) / (2 * a);

  return PDD{root1, root2};
}

