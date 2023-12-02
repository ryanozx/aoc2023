#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef pair<string, int> PSI;

bool isPossible(vector<PSI> &cubes);
string stripPunctuation(string &s);

map<string, int> CUBE_MAX_VAL = {{"red", 12},
                                 {"green", 13},
                                 {"blue", 14}};

int main() {
  string line;
  int idSum = 0;
  while (getline(cin, line)) {
    istringstream ss(line);
    string token;
    vector<PSI> cubes;
    
    int wordPos = 0;
    int gameID;
    int cubeNo;
    bool isValidSubsets = true;
    while ((ss >> token) && isValidSubsets) {
      if (wordPos == 1) {
        gameID = stoi(stripPunctuation(token));
      } else if (wordPos & 1) {
        string colour = stripPunctuation(token);
        cubes.emplace_back(colour, cubeNo);

        if (token.back() == ';') {
           isValidSubsets = isPossible(cubes);
           cubes.clear();
        }
      } else if ((wordPos & 1) == 0 && wordPos) {
        cubeNo = stoi(token);
      }

      ++wordPos;
    }

    if (isValidSubsets && isPossible(cubes)) {
      idSum += gameID;
    }
    ++gameID;
  }
  printf("%d\n", idSum);
}

bool isPossible(vector<PSI> &cubes) {
  for (auto &p : cubes) {
    if (!CUBE_MAX_VAL.count(p.first)) {
      return false;
    }
    if (CUBE_MAX_VAL[p.first] < p.second) {
      return false;
    }
  }
  return true;
}

string stripPunctuation(string & s) {
  if (s.back() == ';' || s.back() == ':' || s.back() == ',') {
    return s.substr(0, s.length() - 1);
  }
  return s;
}
