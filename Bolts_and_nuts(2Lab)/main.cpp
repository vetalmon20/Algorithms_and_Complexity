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

struct Border{
    int left;
    int right;
    Border(){
        left = 0;
        right = quantity - 1;
    }
};

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

void shuffle(int *in){
    for (int i = 0; i < 40; i++){
        swap (in,rand() % quantity, rand() % quantity);
    }

}

Border detect(int *Bolts_0, int *Nuts, int val){
    Border out;
    for (int i = 0; i < quantity; i++){
        if(Bolts_0[i] != 0){
            if(Nuts[i] < val)
                out.left = i + 1;
            else {
                out.right = i - 1;
                return out;
            }
        }
    }
    return out;
}

void sorter(int *Bolts_0, int *Nuts, Border in, int val){

    int length = in.right - in.left + 1;            //the length of the temp array
    int Nuts_temp[length];

    Border temp_bord;
    temp_bord.left = 0;
    temp_bord.right = length - 1;

    for (int j = in.left; j < in.right + 1; j++){
        if (val < Nuts[j]){
            Nuts_temp[temp_bord.right] = Nuts[j];
            temp_bord.right--;
        }
        if (val > Nuts[j]){
            Nuts_temp[temp_bord.left] = Nuts[j];
            temp_bord.left++;
        }
    }
    Nuts_temp[temp_bord.left] = val;

    for (int i = 0; i < length; i++){
        Nuts[in.left + i] = Nuts_temp[i];
    }
    Bolts_0[temp_bord.left + in.left] = val;
}

void distributor(int *Bolts, int *Nuts){

    int Bolts_0[quantity];

    for(int j = 0; j < quantity; j++)
        Bolts_0[j] = 0;

    for (int i = 0; i < quantity; i++){
        sorter(Bolts_0, Nuts, detect(Bolts_0, Nuts, Bolts[i]), Bolts[i]);
    }

    for (int k = 0; k < quantity; k++){
        Bolts[k] = Bolts_0[k];
    }

}

int main() {

    int Bolts[quantity], Nuts[quantity];
    for (int i = 0; i < quantity; i++){
        Bolts[i] = Nuts[i] = i * 2 + 2;
    }
    shuffle(Bolts);
    shuffle(Nuts);
    display(Bolts, Nuts);

    cout<<"---"<<endl;
    distributor(Bolts,Nuts);
    display(Bolts,Nuts);

    return 0;
}