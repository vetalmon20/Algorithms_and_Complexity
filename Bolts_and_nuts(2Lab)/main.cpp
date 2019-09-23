/**
 * 2nd Course K-29
 * Lab 2.
 * Task: make an algorithm that determine the right bolt to the right nut
 * (You cannot compare bolt with bolt or nut with nut) for the time O(n*logn)
 *
 *@author Vitaliy Datsiuk
 *@version 1.0 23/09/19
 */

#include <iostream>
#define quantity 50

using namespace std;

void display(int Bolts[], int Nuts[]) {
    for (int i = 0; i < quantity; i++) {
        cout << "Bolt: " << Bolts[i] << ". Nut: " << Nuts[i] << endl;
    }
}

void swap (int *in, int val_a, int val_b){

    if (val_a == val_b || val_a < 0 || val_b < 0 || val_a > quantity - 1 || val_b > quantity - 1){
        return;
    }

    int temp = in[val_a];

    in[val_a] = in[val_b];
    in[val_b] = temp;
}

void shuffle(int *Bolts){
    for (int i = 0; i < 40; i++){
        swap (Bolts,rand() % quantity, rand() % quantity);
    }

}

void determinator(int Bolts[], int Nuts[]){
    
}

int main() {
    int Bolts[quantity], Nuts[quantity];
    for (int i = 0; i < quantity; i++){
        Bolts[i] = Nuts[i] = i + 1;
    }
    //display(Bolts, Nuts);
    shuffle(Bolts);
    shuffle(Nuts);
    display(Bolts, Nuts);

    return 0;
}