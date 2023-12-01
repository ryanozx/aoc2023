#include <iostream>
#include <string>

using namespace std;

int main()
{
    string input;
    char firstDigit;
    char lastDigit;
    int total = 0;
    while (getline(cin, input))
    {
        firstDigit = 0;
        lastDigit = 0;
        for (char c : input) {
            if (c >= '0' && c <= '9') {
                if (firstDigit == 0) {
                    firstDigit = c;
                }
                lastDigit = c;
            }
        }
        total += (firstDigit - '0') * 10 + (lastDigit - '0');
    }
    printf("%d\n", total);
    return 0;
}
