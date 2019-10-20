/**
 * 2nd Course K-29
 * Lab 8.
 * Task:perform algorithms of finding of substring in the string
 *
 *@author Vitaliy Datsiuk
 *@version 1.0 22/10/19
 */


#include <iostream>
#include <time.h>

using namespace std;

void naive(string ex, string pat){

    int m = pat.length();
    int n = ex.length();

    if(ex.length() < pat.length()){
        cout << "Wrong values of the function. WARNING: swaps the strings and finds the patterns"
        << endl;
        string c = pat;
        pat = ex;
        ex = c;
    }


    bool found = 0;

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= n - m; i++) {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < m; j++)
            if (ex[i + j] != pat[j])
                break;

        if (j == m) {// if pat[0...M-1] = txt[i, i+1, ...i+M-1]
            cout << "Pattern found at index " << i << endl;
            found = 1;
        }
    }
    if (found == 0)
        cout << "No patterns for these strings" << endl;
}

void KMP(string S1, string S2){

    bool found = 0;                     //used to detect if we found at least 1 pattern

    if(S1.length() > S2.length()){
        cout << "Wrong values fo the function.WARNING: swaps the strings and finds the patterns"
                << endl;
        string c = S1;
        S1 = S2;
        S2 = c;
    }

    string S = S1 + '@' + S2;

    //filling the auxiliary array
    int P[S.length()];
    for(int i = 0; i < S.length(); i++)
        P[i] = 0;

    //actually the algorithm
    for(int i = 1; i < S.length() ; i++){
        int j = P[i - 1];
        while((j > 0) && (S[i] != S[j]))
            j = P[j - 1];
        if (S[i] == S[j])
            j++;
        P[i] = j;
        if(j == S1.length()){
            cout << "Pattern found at index " << i - S1.length() - j << endl;
            found = 1;
        }
    }
    if(found == 0)
        cout << "No patterns for these strings" << endl;

}

void Horspool(string ex, string pat){

    if (ex.length() < pat.length()){
        cout << "Wrong values of the function. WARNING: swaps the strings and finds the patterns"
             << endl;
        string c = pat;
        pat = ex;
        ex = c;
    }

    bool found = 0;
    int table[pat.length()];                      //table of shifts
    table[pat.length() - 1] = pat.length();       //the last is always equals the length of the pat
    for (int i = pat.length() - 2; i >= 0; i--){
        int j = pat.length() - 1 - pat.rfind(pat[i]);
        table[i] = max(1, j);
    }

    int k = pat.length() - 1;
    int i = k;
    int j = i;

    while (i < ex.length()){

        if(ex[i] == pat[k]){
            i--;
            k--;
        } else {
            int pos;
            if (pat.find(ex[i]) > pat.length())
                pos = pat.length();
            else
                pos = table[pat.find(ex[i])];
            k = pat.length() - 1;
            //i = i + pos;
            i = j + pos;
            j = i;
        }
        if(k < 0){
            cout << "Pattern found at index " << i + 1 << endl;
            found = 1;
        }
    }
    if(found == 0)
        cout << "No pattern for these strings." << endl;
}

void Rabin_Karp(string pat, string txt, int q){
    if (txt.length() < pat.length()){
        cout << "Wrong values of the function. WARNING: swaps the strings and finds the patterns"
             << endl;
        string c = pat;
        pat = txt;
        txt = c;
    }

    bool found = 0;
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1; // used in formulae

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < pat.length() - 1; i++)
        h = (h * 256) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < pat.length() ; i++){
        p = (256 * p + pat[i]) % q;
        t = (256 * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= txt.length() - pat.length() ; i++){

        /* Check the hash values of current window of text and pattern.If the hash values match
           then only check for characters on by one */
        if ( p == t )
        {
            // Check for characters one by one
            for (j = 0; j < pat.length() ; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == pat.length() ){
                cout << "Pattern found at index "<< i << endl;
                found = 1;
            }
        }

        // Calculate hash value for next window of text: Remove leading digit, add trailing digit
        if ( i < txt.length() - pat.length())
        {
            t = (256 * (t - txt[i] * h) + txt[i + pat.length() ]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }
    if(found == 0)
        cout << "No pattern for these strings." << endl;

}

void BM(string S1,string S2) {

    if (S2.length() < S1.length()){
        cout << "Wrong values of the function. WARNING: swaps the strings and finds the patterns"
             << endl;
        string c = S1;
        S1 = S2;
        S2 = c;
    }

    int l1 = S1.length();
    int count=0;
    int l2 = S2.length();
    int res = -1;
    int i=0, pos;
    int BMT[256];
    for (i = 0; i < 256; i++)
        BMT[i] = l1;
    for (i = l1 - 1; i >= 0; i--)
        if (BMT[(S1[i])] == l1)
            BMT[(S1[i])] = l1 - i - 1;
    pos = l1 - 1;
    while (pos < l2)
    {

        if (S1[l1 - 1] != S2[pos])
            pos = pos + BMT[S2[pos]];

        else
            for (i = l1 - 1; i >= 0; i--) {
                if (S1[i] != S2[pos - l1 + i + 1]) {
                    if (BMT[(S2[pos - l1 + i + 1])]==0)
                        pos++;
                    else
                        pos += BMT[(S2[pos - l1 + i + 1])] - 1;
                    break;
                } else if (i == 0) {
                    cout << "Pattern found at index " << pos - l1 + 1 << endl;
                    pos++;
                    count++;
                }
            }

    }
    if (count==0)
        cout<<"No pattern for these strings." << endl;
    return;
}

int main() {


    string b = "had you followed Captain Ahab down into his cabin after the squall that took place on the night succeeding that wild ratification of his purpose with his crew, you would have seen him go to a locker in the transom, and bringing out a large wrinkled roll of yellowish sea charts, spread them before him on his screwed-down table. Then seating himself before it, you would have seen him intently study the various lines and shadings which there met his eye; and with slow but steady pencil trace additional courses over spaces that before were blank. At intervals, he would refer to piles of old log-books beside him, wherein were set down the seasons and places in which, on various former voyages of various ships, sperm whales had been captured or seen.\n"
               "\n"
               "While thus employed, the heavy pewter lamp suspended in chains over his head, continually rocked with the motion of the ship, and for ever threw shifting gleams and shadows of lines upon his wrinkled brow, till it almost seemed that while he himself was marking out lines and courses on the wrinkled charts, some invisible pencil was also tracing lines and courses upon the deeply marked chart of his forehead.\n"
               "\n"
               "But it was not this night in particular that, in the solitude of his cabin, Ahab thus pondered over his charts. Almost every night they were brought out; almost every night some pencil marks were effaced, and others were substituted. For with the charts of all four oceans before him, Ahab was threading a maze of currents and eddies, with a view to the more certain accomplishment of that monomaniac thought of his soul.\n"
               "\n"
               "Now, to any one not fully acquainted with the ways of the leviathans, it might seem an absurdly hopeless task thus to seek out one solitary creature in the unhooped oceans of this planet. But not so did it seem to Ahab, who knew the sets of all tides and currents; and thereby calculating the driftings of the sperm whales food; and, also, calling to mind the regular, ascertained seasons for hunting him in particular latitudes; could arrive at reasonable surmises, almost approaching to certainties, concerning the timeliest day to be upon this or that ground in search of his prey.\n"
               "\n"
               "So assured, indeed, is the fact concerning the periodicalness of the sperm whale’s resorting to given waters, that many hunters believe that, could he be closely observed and studied throughout the world; were the logs for one voyage of the entire whale fleet carefully collated, then the migrations of the sperm whale would be found to correspond in invariability to those of the herring-shoals or the flights of swallows. On this hint, attempts have been made to construct elaborate migratory charts of the sperm whale";

    string a;
    for(int i = 0; i < 100000; i++)
        a.push_back(rand() % 2 + 48);

    clock_t start1 = clock();
    naive(a, "110111");
    clock_t end1 = clock();
    double seconds1 = (double) (end1 - start1) / CLOCKS_PER_SEC;
    cout <<"---------------------------------------------";

    clock_t start2 = clock();
    KMP(a, "110111");
    clock_t end2 = clock();
    double seconds2 = (double) (end2 - start2) / CLOCKS_PER_SEC;
    cout <<"---------------------------------------------";

    clock_t start3 = clock();
    Rabin_Karp(a, "110111",101);
    clock_t end3 = clock();
    double seconds3 = (double) (end3 - start3) / CLOCKS_PER_SEC;
    cout <<"---------------------------------------------" << endl;

    clock_t start4 = clock();
    Horspool(a, "110111");
    clock_t end4 = clock();
    double seconds4 = (double) (end4 - start4) / CLOCKS_PER_SEC;
    cout <<"---------------------------------------------" << endl;

    clock_t start41 = clock();
    BM("110111", a);
    clock_t end41 = clock();
    double seconds41 = (double) (end41 - start41) / CLOCKS_PER_SEC;


    cout << seconds1 << " " << seconds2 << " " << seconds3 << " " << seconds4 <<" "<< seconds41 << endl;


    clock_t start5 = clock();
    naive(b, "periodicalness");
    clock_t end5 = clock();
    double seconds5 = (double) (end5 - start5) / CLOCKS_PER_SEC;
    cout <<"---------------------------------------------" << endl;

    clock_t start6 = clock();
    KMP(b, "periodicalness");
    clock_t end6 = clock();
    double seconds6 = (double) (end6 - start6) / CLOCKS_PER_SEC;
    cout <<"---------------------------------------------" << endl;

    clock_t start7 = clock();
    Rabin_Karp(b, "periodicalness",101);
    clock_t end7 = clock();
    double seconds7 = (double) (end7 - start7) / CLOCKS_PER_SEC;
    cout <<"--------------------------------------------- " << endl;

    clock_t start8 = clock();
    Horspool(b, "periodicalness");
    clock_t end8 = clock();
    double seconds8 = (double) (end8 - start8) / CLOCKS_PER_SEC;
    cout <<"--------------------------------------------- !" << endl;

    clock_t start81 = clock();
    BM("periodicalness", b);
    clock_t end81 = clock();
    double seconds81 = (double) (end81 - start81) / CLOCKS_PER_SEC;

    cout << seconds5 << " " << seconds6 << " " << seconds7 << " " << seconds8 << seconds81;

    return 0;
}