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
#define quantity 50                 //number of the nuts and bolts

using namespace std;

//structure which contain the left and the right index(used in sorting the part of the array
//starting from left index and ending by right index)
struct Border{
    int left;
    int right;
    Border(){
        left = 0;
        right = quantity - 1;
    }
};

//function that prints the bolt and the appropriate nut
void display(int Bolts[], int Nuts[]) {
    for (int i = 0; i < quantity; i++) {
        cout << "Bolt: " << Bolts[i] << ". Nut: " << Nuts[i] << endl;
    }
}

//function that swaps two values in the input array
void swap (int *in, int val_a, int val_b){

    if (val_a == val_b || val_a < 0 || val_b < 0 || val_a > quantity - 1 || val_b > quantity - 1){
        return;
    }

    int temp = in[val_a];

    in[val_a] = in[val_b];
    in[val_b] = temp;
}

//function that randomly swaps the values in the array (the aim of this function in my program is to
//make maximally random array to sort)
void shuffle(int *in){
    for (int i = 0; i < 40; i++){
        swap (in,rand() % quantity, rand() % quantity);
    }

}

//this function detects the borders(left and right border) of the main array , that should be sorted
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

//this fucntion sorts the part of array that determines by Border. Sorting is implemented like:
//we take the first value from the border array and compare it with the input val. If it is bigger
//we write it in the end of the array and decrement the right border, otherwise if it is smaller
// we write it on the start of the array and increment the left border. The last part is to put the
//input value on the needed place(which is basically empty)
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

//this function takes all the bolts and sort the nuts in correspondence to the bolt: either it is
//bigger or smaller. Than it takes the next bolt and do the same, firtsly comparing it with the
//already sorted nuts to determine the part of the array to sort
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
        Bolts[i] = Nuts[i] = i * 2 + 2;         //You can fill the array whatever you like
    }
    shuffle(Bolts);
    shuffle(Nuts);

    display(Bolts, Nuts);

    cout<<"---"<<endl;
    distributor(Bolts,Nuts);                    //main function
    display(Bolts,Nuts);

    return 0;
}