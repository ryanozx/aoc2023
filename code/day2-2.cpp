#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

typedef pair<string, int> PSI;

void updateMinimum(map<string, int> &minCubes, PSI &cubePair);
string stripPunctuation(string &s);
long long calcCubePower(map<string, int> &minCubes);

int main() {
  string line;
  long long cubePowerSum = 0LL;
  while (getline(cin, line)) {
    istringstream ss(line);
    string token;
    map<string, int> minCubes;
    
    int wordPos = 0;
    int gameID;
    int cubeNo;
    bool isValidSubsets = true;
    while ((ss >> token) && isValidSubsets) {
      if (wordPos == 1) {
        gameID = stoi(stripPunctuation(token));
      } else if (wordPos & 1) {
        string colour = stripPunctuation(token);
        PSI cubePair = {colour, cubeNo};
        updateMinimum(minCubes, cubePair);
      } else if ((wordPos & 1) == 0 && wordPos) {
        cubeNo = stoi(token);
      }

      ++wordPos;
    }
    
    cubePowerSum += calcCubePower(minCubes);
    ++gameID;
  }
  printf("%lld\n", cubePowerSum);
}

void updateMinimum(map<string, int> & minCubes, PSI &cubePair) {
  if (minCubes.count(cubePair.first)) {
    minCubes[cubePair.first] = max(minCubes[cubePair.first], cubePair.second);
  } else {
    minCubes[cubePair.first] = cubePair.second;
  }
}

string stripPunctuation(string & s) {
  if (s.back() == ';' || s.back() == ':' || s.back() == ',') {
    return s.substr(0, s.length() - 1);
  }
  return s;
}

long long calcCubePower(map<string, int> &minCubes) {
  long long power = 1LL;
  for (auto const &p: minCubes) {
    power *= p.second;
  }
  return power;
}
