#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct array{
    int* A=new int[10];
    int length;
    array(){
        length=10;
    }
};

void fill_file(FILE* input){
    for(int i=0;i<100;i++)
        fprintf(input,"%i%c",rand() % 1000,' ');
    rewind(input);
}


//void read_arr(FILE* input,vector<int> A){
int read_arr(FILE* input,array in){
    int temp;
    for(int i=0;i<10;i++) {
        if (feof(input)) {
            return i-1;
            }
        fscanf(input,"%i",&temp);
        //A.push_back(temp);
        in.A[i]=temp;
    }
    return 10;
}

//void print_arr(vector<int> in,int length){
void print_arr(array in){
    for(int i=0;i<in.length;i++){
        cout<<in.A[i]<<" ";
    }
    cout<<endl;
}

void print_vec(vector<int> in){
    for (vector<int>::const_iterator i = in.begin(); i != in.end(); ++i)
        cout<<*i<<' ';
}

void quicksort(int* A,int length){


}

int main() {
    FILE *fina=fopen("inA.txt","r+");
    FILE *finb=fopen("inB.txt","r+");
    FILE *fouta=fopen("outA.txt","w+");
    FILE *foutb=fopen("outB.txt","w+");

    //fill_file(fina);
    fill_file(finb);

    //vector<int> arr(10);
    array arr;

    arr.length=read_arr(fina,arr);
    print_arr(arr);
    arr.length=read_arr(fina,arr);
    print_arr(arr);

    return 0;
}