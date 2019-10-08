/**
 * 2nd Course K-29
 * Lab 4.
 * Task: make 3 algorithms that satisfies the following rules:
 *      1)That satisfies the rule 1 and 2;
 *      2)That satisfies the rule 1 and 3;
 *      3)That satisfies the rule 2 and 3.
 * The rules are:
 *      1)O(n);
 *      2)Algorithm should be stable;
 *      3)No additional memory(in the worst case it should be limited)
 *
 *@author Vitaliy Datsiuk
 *@version 1.0 08/10/19
 */

#include <iostream>

using namespace std;

struct Key_Value{
public:
    int Key;
    bool Val;
};                        //structure that increases comfort of the implementing

void Swap(Key_Value *in, int i1, int i2){

    Key_Value temp = in[i1];
    in[i1] = in[i2];
    in[i2] = temp;
} //swaps two values in the input array and indexes

void display(Key_Value *in, int n){
    for (int i = 0; i < n; i++){
        cout << "Key: " << in[i].Key << " Val: " << in[i].Val << endl;
    }
    cout << endl;
}       //displays the array structure in the appropriate way

int Find_0_num(Key_Value *arr, int n){

    int num = 0;                        //counter

    for(int i = 0; i < n; i++){
        if(arr[i].Val == 0)
            num++;
    }

    return num;
}   //Finds the number of the 0 Values in the array

int partition_quicksort(Key_Value *arr, int start, int finish) {
    Key_Value piv_data = arr[finish];        //data that pivot contain
    int temp = start - 1;                    //index of the place to swap the values
    int j;                                   //iterator

    //partition part
    for (j = start; j !=finish; j++) {
        if (arr[j].Key <= piv_data.Key) {
            temp++;
            //swap(temp, j);
            Swap(arr, temp, j);
        }
    }

    //swapping the pivot
    temp++;
    //swap (temp, j);
    Swap(arr, temp, j);
    return temp;
}

void quicksort(Key_Value *arr,int start, int finish){

    if (finish != 0 && start != finish && start != finish + 1){
        int pivot = partition_quicksort(arr, start, finish);   //finding the place to pivot
        quicksort(arr, start, pivot-1);                   //doing the same to the left part
        quicksort(arr, pivot+1, finish);                  //doing the same to the right part
    }
}

void Algorithm12(Key_Value *arr, int n){

    int length_1 = n - Find_0_num(arr, n);            //length of the array devoted to 1

    Key_Value arr0[n];                               //this array will substitute the input one
    Key_Value arr1[length_1];
    int i0,i1;
    i0 = i1 = 0;

    //seperating 0 and 1 in two different arrays
    for (int i = 0; i < n; i++){
        if (arr[i].Val == 0){
            arr0[i0] = arr[i];
            i0++;
        }
        else{
            arr1[i1] = arr[i];
            i1++;
        }
    }

    //adding the  1 in the wright order
    for (int j = 0; j < length_1; j++){
        arr0[i0] = arr1[j];
        i0++;
    }

    //rewriting the input array
    for(int k = 0; k < n; k++)
        arr[k] = arr0[k];

}  //Algorithm that satisfies the 1 and the 2 rule

void Algorithm13(Key_Value *arr, int n){

    int index = n - 1;                      //ending index
    int i = 0;                              //starting index
    //while all the array would be readed
    while (i != index){
        if(arr[i].Val == 1) {
            Swap(arr, i, index);
            index--;                        //put the 1 in the end
        }
        else{
            i++;                            //increment index in order to check the next element
        }
    }
} //Algorithm that satisfies the 1 and the 3 rule

void Algorithm23(Key_Value *arr, int n){

    Algorithm13(arr, n);                   //at first separates 0 and 1
    int temp = Find_0_num(arr, n);         //number of 0s in the array
    quicksort(arr,0,temp - 1);  //sorts the keys for the 0s
    quicksort(arr, temp, n - 1);     //sorts the leys for the 1s
} //Algorithm that satisfies the 2 and the 3 rule

int main() {

    int n;                                              //the length of the array
    cout << "Enter the length of the array:" << endl;
    cin >> n;
    if(n <= 0 ){
        cout << "Wrong length of the array" << endl;
        return -1;
    }

    Key_Value arr[n];                                   //the input array

    //creating a random array
    for (int i = 0; i < n; i++){
        arr[i].Key = i;                             //distinctive feature
        arr[i].Val = rand() % 2;                    //0 or 1
    }
    cout << endl;

    display(arr, n);

    Algorithm12(arr, n);

    display(arr, n);


    return 0;
}