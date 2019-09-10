#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#define deflen 10
int files_num=0;

using namespace std;

FILE *fouta=fopen("outA.txt","w+");
FILE *foutb=fopen("outB.txt","w+");
FILE *blocks[20];

//struct fo the array with length
struct array{
    int* A=new int[deflen];
    int length;
    array(){
        length=10;
    }
};

FILE* create_default_file(const char* in){
    string name="source";
    FILE *test=fopen(in,"w+");
}

//filling the file with random integers
void fill_file(FILE* input){
    for(int i=0;i<100;i++)
        fprintf(input,"%i%c",rand() % 1000,' ');
    rewind(input);
}

//reading an array from the file
int read_arr(FILE* input,array in){
    int temp;
    for(int i=0;i<deflen;i++) {
        if (feof(input)) {
            return i-1;
            }
        fscanf(input,"%i",&temp);
        //A.push_back(temp);
        in.A[i]=temp;
    }
    return 10;
}

//printing an array in file and on the screen
void print_arr(array in,FILE* out){
    for(int i=0;i<in.length;i++){
        cout<<in.A[i]<<" ";
        fprintf(out,"%d%c",in.A[i],' ');
    }
    fprintf(out,"%c%c",'/',' ');
    cout<<endl;
}

//concatenating the rest of the array from starting position
void conc_arr(array in,FILE* out,int start_pos){
    for(start_pos=0;start_pos<in.length;start_pos++){
        //cout<<in.A[start_pos]<<" ";
        fprintf(out,"%d%c",in.A[start_pos],' ');
    }
    fprintf(out,"%c%c",'/',' ');
    cout<<endl;
}

//merging an array in sorted one
void merge(array in,int left,int middle,int right){
    int len1=middle-left+1;
    int len2=right-middle;
    //creating 2 temp subarrays
    int A[len1];
    int B[len2];
    //copy data to temp subarrays
    for(int i=0;i<len1;i++){
        A[i]=in.A[left+i];
    }
    for(int j=0;j<len2;j++){
        B[j]=in.A[middle+1+j];
    }
    int i=0;
    int j=0;
    int k=left;
    while(i<len1 && j<len2){
        if(A[i]<=B[j]){
            in.A[k]=A[i];
            i++;
        }else{
            in.A[k]=B[j];
            j++;
        }
        k++;
    }
    //copy the rest of the subarrays to our array
    while(i<len1){
        in.A[k]=A[i];
        i++;
        k++;
    }
    while(j<len2){
        in.A[k]=B[j];
        j++;
        k++;
    }



}

//recursive divide the array for the merge
void mergesort(array in,int left,int right){
    if(left<right) {
        int middle = left+(right-left)/2;
        mergesort(in, left, middle);
        mergesort(in, middle + 1, right);
        merge(in,left,middle,right);
    }
}

void make_sorted_blocks(FILE* in){
    array temp;
    while(!feof(in)){
       temp.length=read_arr(in,temp);
       print_arr(temp,fouta);
    }
}

int main() {
    string test;
    int aaa=1232;
    test=to_string(aaa);
    cout<<test;
    //create_default_file(test.c_str());


    FILE *fina=fopen("inA.txt","r+");
    FILE *finb=fopen("inB.txt","r+");
//filling files with the random integers
    fill_file(fina);
    fill_file(finb);
//creating the temp arr
    array arr;

    arr.length=read_arr(fina,arr);
    print_arr(arr,fouta);
    arr.length=read_arr(fina,arr);
    print_arr(arr,foutb);

    mergesort(arr,0,arr.length);
    print_arr(arr,foutb);

    return 0;
}