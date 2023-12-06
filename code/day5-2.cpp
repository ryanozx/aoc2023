#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct range {
  long long rangeStart;
  long long rangeSize;

  bool operator<(const range& x) {
    return rangeStart < x.rangeStart;
  }
};

struct entry {
  long long destStart;
  long long sourceStart;
  long long rangeSize;

  bool operator<(const entry& x) {
    return sourceStart < x.sourceStart;
  }
};

const int MAX_SZ = 128;

int readSeeds(range seeds[], string &line);

int main() {
  string line;
  getline(cin, line);

  range nums[MAX_SZ];
  range nums2[MAX_SZ];
  int numRange = readSeeds(nums, line);
  sort(nums, nums + numRange);

  entry entries[MAX_SZ];
  int entryCount = 0;

  // consume one empty line
  getline(cin, line);
  
  while (getline(cin, line)) {
    if (line.length() == 0) {
      sort(entries, entries + entryCount);

      long long currNum = nums[0].rangeStart;
      int num1Pos = 0;
      int num2Pos = 0;
      int entryPos = 0;

      //printf("=========\n");
      while (num1Pos < numRange && entryPos < entryCount) {
        //printf("Processing source: (%lld, %lld) and entry: (%lld, %lld, %lld)\n", nums[num1Pos].rangeStart, nums[num1Pos].rangeStart + nums[num1Pos].rangeSize - 1, entries[entryPos].sourceStart, entries[entryPos].destStart, entries[entryPos].rangeSize);
        if (entries[entryPos].sourceStart + entries[entryPos].rangeSize - 1 < currNum) { 
          ++entryPos;
          //printf("Skipped to next entry\n");
        } else if (currNum < entries[entryPos].sourceStart) {
          nums[num2Pos].rangeStart = currNum;
          if (nums[num1Pos].rangeStart + nums[num1Pos].rangeSize - 1 < entries[entryPos].sourceStart) {
            nums[num2Pos].rangeSize = nums[num1Pos].rangeStart + nums[num1Pos].rangeSize - currNum;
            ++num1Pos;
            if (num1Pos < numRange) {
              currNum = nums[num1Pos].rangeStart;
            }
          } else {
            nums[num2Pos].rangeSize = entries[entryPos].sourceStart - currNum;
            currNum = entries[entryPos].sourceStart;
          }
          ++num2Pos;

          //printf("Mapped with no change to (%lld, %lld)\n", nums2.back().rangeStart, nums2.back().rangeStart + nums2.back().rangeSize - 1);
        } else {
          nums2[num2Pos].rangeStart = currNum - entries[entryPos].sourceStart + entries[entryPos].destStart;
          if (nums[num1Pos].rangeStart + nums[num1Pos].rangeSize <= entries[entryPos].sourceStart + entries[entryPos].rangeSize) {
            nums2[num2Pos].rangeSize = nums[num1Pos].rangeStart + nums[num1Pos].rangeSize - currNum;
            ++num1Pos;
            if (num1Pos < numRange) {
              currNum = nums[num1Pos].rangeStart;
            }
          } else {
            nums2[num2Pos].rangeSize = entries[entryPos].sourceStart + entries[entryPos].rangeSize - currNum;
            currNum = entries[entryPos].sourceStart + entries[entryPos].rangeSize;
          }

          ++num2Pos;
          //printf("Mapped to (%lld, %lld)\n", nums2.back().rangeStart, nums2.back().rangeStart + nums2.back().rangeSize - 1);
        }
      }

      while (num1Pos < numRange) {
        nums2[num2Pos].rangeStart = currNum;
        nums2[num2Pos].rangeSize = nums[num1Pos].rangeStart + nums[num1Pos].rangeSize - currNum;
        //printf("Mapped (%lld, %lld) to (%lld, %lld) (no entry)\n", currNum, nums[num1Pos].rangeStart + nums[num1Pos].rangeSize - 1, nums2.back().rangeStart, nums2.back().rangeStart + nums2.back().rangeSize - 1);
        ++num1Pos;
        ++num2Pos;
        if (num1Pos < numRange) {
          currNum = nums[num1Pos].rangeStart;
        }
      }

      sort(nums2, nums2 + num2Pos); 
      
      numRange = 0;
      for (int i = 0; i < num2Pos; ++i) {
        if (numRange && nums[numRange - 1].rangeStart + nums[numRange - 1].rangeSize == nums2[i].rangeStart) {
          nums[numRange - 1].rangeSize += nums2[i].rangeSize;
        } else {
          nums[numRange] = nums2[i];
          ++numRange;
        }
      }

      //printf("%d -> %d\n", num2Pos, numRange);

      entryCount = 0;
    } else if (line[0] >= '0' && line[0] <= '9') {
      long long sstart, dstart, rsize;
      sscanf(line.c_str(), "%lld %lld %lld", &dstart, &sstart, &rsize);
      entries[entryCount].sourceStart = sstart;
      entries[entryCount].destStart = dstart;
      entries[entryCount].rangeSize = rsize;
      ++entryCount;
    }
  }

  printf("%lld\n", nums[0].rangeStart);
  return 0;
}

int readSeeds(range seeds[], string & line) {
  istringstream ss(line);
  string token;
  // skip "seeds:"
  ss >> token;

  int pos = 0;
  long long rangeStart;
  while (ss >> token) {
    if (pos & 1) {
      long long rangeSize = stoll(token);
      seeds[pos >> 1].rangeStart = rangeStart;
      seeds[pos >> 1].rangeSize = rangeSize;
    } else {
      rangeStart = stoll(token);
    }
    ++pos;
  }
  return pos >> 1;
}
