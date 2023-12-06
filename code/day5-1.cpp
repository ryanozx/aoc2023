#include <climits>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct range {
  long long destStart;
  long long sourceStart;
  long long rangeSize;
};

const int MAX_SZ = 64;

int readSeeds(long long seeds[], string &line);

int main() {
  string line;
  getline(cin, line);

  long long nums[MAX_SZ];
  int numSeeds = readSeeds(nums, line);

  range ranges[MAX_SZ];
  int rangeIdx = 0;

  // consume one empty line
  getline(cin, line);
  
  while (getline(cin, line)) {
    if (line.length() == 0) {
      for (int i = 0; i < numSeeds; ++i) {
        for (int j = 0; j < rangeIdx; ++j) {
          if (nums[i] >= ranges[j].sourceStart && nums[i] < ranges[j].sourceStart + ranges[j].rangeSize) {
            nums[i] = ranges[j].destStart + (nums[i] - ranges[j].sourceStart);
            break;
          }
        }
      }

      rangeIdx = 0;
    } else if (line[0] >= '0' && line[0] <= '9') {
      long long sstart, dstart, rsize;
      sscanf(line.c_str(), "%lld %lld %lld", &dstart, &sstart, &rsize);
      ranges[rangeIdx].sourceStart = sstart;
      ranges[rangeIdx].destStart = dstart;
      ranges[rangeIdx].rangeSize = rsize;
      ++rangeIdx;
    }
  }

  long long minLoc = LLONG_MAX; 
  for (int i = 0; i < numSeeds; ++i) {
    minLoc = min(minLoc, nums[i]);
  }
  printf("%lld\n", minLoc);
  return 0;
}

int readSeeds(long long seeds[], string & line) {
  int numSeeds = 0;
  istringstream ss(line);
  string token;
  // skip "seeds:"
  ss >> token;
  while (ss >> token) {
    *(seeds + numSeeds++) = stoll(token);
  }
  return numSeeds;
}
