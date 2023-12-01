#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, int> nums = {{"one", 1},
			 {"two", 2},
			 {"three", 3},
			 {"four", 4},
			 {"five", 5},
			 {"six", 6},
			 {"seven", 7},
			 {"eight", 8},
			 {"nine", 9}};

int stringToNum(int pos, string & s);
int numInMap(string & s);

int main() {
    string input;
    int total = 0;
    while (getline(cin, input)) {
        int firstDigit = 0;
        int lastDigit = 0;
	for (int i = 0; i < input.length(); ++i) {
	    char c = input[i];
            if (c >= '0' && c <= '9') {
                if (firstDigit == 0) {
                    firstDigit = c - '0';
                }
                lastDigit = c - '0';
		continue;
            }

	    int convertNum = stringToNum(i, input);  
 	    if (convertNum != -1) {
		if (firstDigit == 0) {
		    firstDigit = convertNum;
		}
		lastDigit = convertNum;
	    }	    
        }
        total += firstDigit * 10 + lastDigit; 
    }
    printf("%d\n", total);
    return 0;
}

int stringToNum(int pos, string & s) {
    string threeLetter = s.substr(pos, 3);
    string fourLetter = s.substr(pos, 4);
    string fiveLetter = s.substr(pos, 5);

    return max(-1, max(numInMap(threeLetter),
	max(numInMap(fourLetter), numInMap(fiveLetter))));
}

int numInMap(string & s) {
    if (nums.count(s)) {
	return nums[s];
    }
    return -1;
}
