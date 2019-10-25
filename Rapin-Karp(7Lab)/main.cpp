/**
 * 2nd Course K-29
 * Lab 7.
 * Task: Rabin-Karp algorithm for the matrix
 *
 *@author Vitaliy Datsiuk
 *@version 1.0 25/10/19
 */


#include <iostream>

using namespace std;

char** create_arr(int n){
    char ** arr;
    arr = new char* [n];
    for(int i = 0; i < n; i++)
        arr[i] = new char[n];
    return arr;
}                           //allocating memory for the array

void print_arr(char** arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout <<"---------------------------" << endl;
}                  //printing the array

void Rabin_Karp(char** pat, int m, char** txt, int n, int q){
    if (n < m){
        cout << "Wrong values of the function. WARNING: swaps the strings and finds the patterns"
             << endl;
        char** a = pat;
        pat = txt;
        txt = a;
    }

    bool found = 0;
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1; // used in formulae

    /* 0 0 0
     * 0 0 0
     * 0 0 0 */


    // The value of h would be "pow(256, M-1) % q"
    for (i = 0; i < m * m - 1; i++)
        h = (h * 256) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < m ; i++){
        for(j = 0; j < m; j++) {
            p = (256 * p + pat[j][i]) % q;
            t = (256 * t + txt[j][i]) % q;
        }
    }

    int j1, j2;                                     //iterator
    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j <= n - m; j++) {

            /* Check the hash values of current window of text and pattern.If the hash values match
               then only check for characters on by one */
            if (p == t) {
                int sum = 0;
                // Check for characters one by one
                for (j1 = 0; j1 < m; j1++){
                    for(j2 = 0; j2 < m; j2++) {
                        if (txt[i + j1][j + j2] != pat[j1][j2])
                            break;
                        sum++;
                    }
                }
                if (sum == m * m) {
                    cout << "Pattern found at index " << i <<"," << j << endl;
                    found = 1;
                }
            }
            // Calculate hash value for next window of text
            if (i <= n - m){
                if (j <= n - m){
                    int k = i;
                    int s = 0;
                    while (s < m){
                        // t = (256*(t - txt[i]*h) + txt[i+M])%q;
                        t = (256 * (t - txt[k][j] * h) + txt[k][j + m]) % q;
                        s++;
                        k++;
                    }
                    // We might get negative value of t, converting it to positive
                    if (t < 0)
                        t = (t + q);
                }
            }
        }
        t = 0;
        if(i < n - m) {
            for (int i3 = 0; i3 < m; i3++) {
                for (int j3 = i + 1; j3 < i + m + 1; j3++) {
                    t = (256 * t + txt[j3][i3]) % q;
                }
            }
        }
    }
    if(found == 0)
        cout << "No pattern for these strings." << endl;
}

int main() {

    char **arr = create_arr(3);
    char **pat = create_arr(2);
    pat[0][0] = 'b';
    pat[0][1] = 'a';
    pat[1][0] = 'b';
    pat[1][1] = 'a';

    arr[0][0] = 'b';
    arr[0][1] = 'b';
    arr[0][2] = 'b';
    arr[1][0] = 'b';
    arr[1][1] = 'a';
    arr[1][2] = 'a';
    arr[2][0] = 'b';
    arr[2][1] = 'a';
    arr[2][2] = 'a';

    print_arr(pat,2);
    print_arr(arr,3);

    cout << "We are searching the pattern 2*2 in our matrix 3*3: " << endl;

    Rabin_Karp(pat, 2, arr, 3, 101);

    return 0;
}