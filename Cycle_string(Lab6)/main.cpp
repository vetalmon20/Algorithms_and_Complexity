/**
 * 2nd Course K-29
 * Lab 6.
 * Task:perform the algorirthm that will check if the string A is a cycle shifted string B
 *
 *@author Vitaliy Datsiuk
 *@version 1.0 19/10/19
 */

#include <iostream>

using namespace std;

//returns 1 if they are cycled, and 0 otherwise
bool isCycled(string a, string b){

    if (a.length() != b.length())
        return false;

    int n = a.length();

    // create lps[] that will hold the longest
    // prefix suffix values for pattern
    int lps[n];

    // length of the previous longest prefix suffix
    int len = 0;
    int i = 1;
    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to n-1
    while (i < n) {
        if (a[i] == b[len]) {
            lps[i] = ++len;
            ++i;
        } else {
            if (len == 0) {
                lps[i] = 0;
                ++i;
            } else {
                 len = lps[len - 1];
            }
        }
    }

    i = 0;
    // match from that rotating point
    for (int k = lps[n - 1]; k < n; ++k) {
        if (b[k] != a[i++])
            return false;
    }
        return true;
}


int main() {


    string q1 = "ABACE";
    string q2 = "CDABA";
    cout << isCycled(q1, q2) << endl;

    string q3 = "ABACD";
    string q4 = "CDABA";
    cout << isCycled(q3, q4);

    return 0;
}