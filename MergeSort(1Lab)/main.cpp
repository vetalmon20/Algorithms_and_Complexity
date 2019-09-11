#include <iostream>
#include <stdio.h>
#include <string>
#define numfiles 10                     //Number files for dividing on blocks
#define rand_num 2000                    //Number of random created integers in main source file(inA)
int deflen=rand_num/numfiles;           //Number of integers in every file
//int deflen=200;
int files_num=0;                        //Counter for num of files

using namespace std;

FILE *blocks[numfiles];                                 //Array for auxillary created files
FILE *result=fopen("result.txt","w");    //Out file

//struct fo the array with length
struct array{
    int* A=new int[deflen];
    int length;
    array(){
        length=deflen;
    }
};

//creating source files to merge
FILE* create_default_file(){
    string name="source_";
    int curr_num=files_num;
    string num=to_string(curr_num);
    string txt=".txt";
    num.append(txt);
    name.append(num);
    FILE *test=fopen(name.c_str(),"w+");
    files_num++;
    return test;
}

//func that delete all the source files
void delete_files(){
    for(int i=files_num-1;i>=0;i--){
        string name="source_";
        string num=to_string(--files_num);
        name.append(num);
        name.append(".txt");
        fclose(blocks[i]);
        remove(name.c_str());
    }
}

//filling the file with random integers
void fill_file(FILE* input){
    for(int i=0;i<rand_num;i++)
        fprintf(input,"%i%c",rand() % 1000,' ');
    rewind(input);
}

//reading an array from the file
int read_arr(FILE* input,array in){
    int temp;
    for(int i=0;i<deflen;i++) {
        if (feof(input)) {
            return i;
            }
        fscanf(input,"%i",&temp);
        //A.push_back(temp);
        in.A[i]=temp;
    }
    return deflen;
}

//printing an array in file and on the screen
void print_arr(array in,FILE* out){
    for(int i=0;i<in.length;i++){
        //cout<<in.A[i]<<" ";
        fprintf(out,"%d%c",in.A[i],' ');
    }
    fprintf(out,"%c%c",' ','/');
    //cout<<endl;
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

//checking if file is empty(ends in '/')
bool is_file_empty(FILE* fin){
    char a;
    long int pos=ftell(fin);//current position
    //fscanf(fin,"%c",&a);
    a=getc(fin);
    while(a==' ')
        a=getc(fin);
    //cout<<" 1st:"<<a;
    fseek(fin,pos,SEEK_SET);//return the pos
    if(a=='/') return 1;
    else return 0;
}


int main() {
    FILE *fina=fopen("inA.txt","w+");
//filling files with the random integers
    fill_file(fina);
//creating the temp arr
    array arr;
//creating source files,that include sorted blocks length of "deflen"
    for(int i=0;i<numfiles;i++){
        blocks[i]=create_default_file();
        arr.length=read_arr(fina,arr);
        mergesort(arr,0,arr.length);
        print_arr(arr,blocks[i]);
//making cursor on the start to operate with the block of data
        rewind(blocks[i]);
    }
//actually MERGING *numfiles* IN ONE
    //fprintf(blocks[0],"%i",22);
    int smallest,smallest_pos,not_empty_pos,temp,k;
    not_empty_pos=0;
    int s=0;
    while(s<rand_num){
        while(is_file_empty(blocks[not_empty_pos])) {
            not_empty_pos++;                            //finding the next NOT EMPTY file
        }
        if(not_empty_pos>19){                           //Unexpected behavior
            cout<<"Unexpected error"<<endl;
            return -1;
        }
        long int pos=ftell(blocks[not_empty_pos]);
        fscanf(blocks[not_empty_pos],"%i",&smallest);   //making a new first element the smallest
        fseek(blocks[not_empty_pos],pos,SEEK_SET);//return the pos in order not to miss the unused integer if the file

        k=not_empty_pos;
        while(k<numfiles) {                             //finding the smallest one
            if(is_file_empty(blocks[k])){
                k++;

            }
            else {
                pos = ftell(blocks[k]);

                fscanf(blocks[k], "%i", &temp);
                if (temp <= smallest) {
                    smallest = temp;
                    smallest_pos = k;
                }

                fseek(blocks[k], pos, SEEK_SET);
                k++;
            }
        }
        fscanf(blocks[smallest_pos],"%i",&temp);//just the easy way to step a cursor on one int right
        fprintf(result,"%i%c",smallest,' ');
    s++;
    }
    delete_files();

    fclose(fina);
    fclose(result);
    return 0;
}