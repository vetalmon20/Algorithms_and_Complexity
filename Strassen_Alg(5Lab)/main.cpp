/**
 * 2nd Course K-29
 * Lab 5.
 * Task: perform Strassen algorithm
 *
 *@author Vitaliy Datsiuk
 *@version 1.0 19/10/19
 */

#include <iostream>

using namespace std;

int** create_arr(int n){
    int ** arr;
    arr = new int* [n];
    for(int i = 0; i < n; i++)
        arr[i] = new int[n];
    return arr;
}                           //allocating memory for the array

void print_arr(int** arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout <<"---------------------------" << endl;
}                  //printing the array

void generate_arr(int** arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j ++){
            arr[i][j] = rand() % 10 - 5;
        }
    }
}               //generating the random matrix

//divides the array on arrays with length n/2
void part_arr(int** arr, int** out, int i, int j, int n){
    //n is the length of the input array
    int real_j = j;                     //used to restore the real value of the j
    for (int i1 = 0; i1 < n/2; i1++){
        for(int j1 = 0; j1 < n/2; j1++){
            out[i1][j1] = arr[i][j];
            j++;
        }
        j = real_j;
        i++;
    }
}

//makes a new matrices by gluing together the 4 blocks of those
void build_arr(int** arr1, int** arr2, int** arr3, int** arr4, int** arr, int n){

    int arr_i = 0;
    int arr_j = 0;
    int real_arr_j = arr_j;
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            arr[arr_i][arr_j] = arr1[i][j];
            arr_j++;
        }
        arr_j = real_arr_j;
        arr_i++;
    }

    arr_i = 0;
    arr_j = n/2;
    real_arr_j = arr_j;
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            arr[arr_i][arr_j] = arr2[i][j];
            arr_j++;
        }
        arr_j = real_arr_j;
        arr_i++;
    }

    arr_i = n/2;
    arr_j = 0;
    real_arr_j = arr_j;
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            arr[arr_i][arr_j] = arr3[i][j];
            arr_j++;
        }
        arr_j = real_arr_j;
        arr_i++;
    }

    arr_i = n/2;
    arr_j = n/2;
    real_arr_j = arr_j;
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            arr[arr_i][arr_j] = arr4[i][j];
            arr_j++;
        }
        arr_j = real_arr_j;
        arr_i++;
    }

}

//gets the sum or the subtr of 2 matrices
//0 - sum; 1 - subtraction
int** sum_substr(bool sign, int** arr1, int** arr2, int n){

    int** temp;
    temp = create_arr(n);
    if(sign == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = arr1[i][j] + arr2[i][j];
            }
        }
    }
        else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp[i][j] = arr1[i][j] - arr2[i][j];
                }
        }
    }
    return temp;
}

//multiplying 2 matrices and saving the result in the arr
void simple_multiply(int** arr1, int** arr2, int** arr, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            arr[i][j] = 0;
            for (int k = 0; k < n; k++){
                arr[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
}

int** Strassens_multiply(int** arr1, int** arr2, int n){

    //basic case
    if (n == 2){
        int ** arr;
        arr = create_arr(2);
        int p1, p2, p3, p4, p5, p6, p7, a, b, c, d, e, f, g, h;
        a = arr1[0][0];
        b = arr1[0][1];
        c = arr1[1][0];
        d = arr1[1][1];

        e = arr2[0][0];
        f = arr2[0][1];
        g = arr2[1][0];
        h = arr2[1][1];

        p1 = (a + d) *(e + h);
        p2 = (c + d) * e;
        p3 = a * (f - h);
        p4 = d * (g - e);
        p5 = (a + b) * h;
        p6 = (c - a) * (e + f);
        p7 = (b - d) * (g + h);

        arr[0][0] = p1 + p4 - p5 + p7;
        arr[0][1] = p3 + p5;
        arr[1][0] = p2 + p4;
        arr[1][1] = p1 - p2 + p3 + p6;

        return arr;
    }

    /*it scares me more than you, really*/
    int **p1, **p2, **p3, **p4, **p5, **p6, **p7, **a, **b, **c, **d, **e, **f, **g, **h, **arr;
    //allocating the memory for all the arrays. Many memory)
    p1 = create_arr(n/2);
    p2 = create_arr(n/2);
    p3 = create_arr(n/2);
    p4 = create_arr(n/2);
    p5 = create_arr(n/2);
    p6 = create_arr(n/2);
    p7 = create_arr(n/2);
    a = create_arr(n/2);
    b = create_arr(n/2);
    c = create_arr(n/2);
    d = create_arr(n/2);
    e = create_arr(n/2);
    f = create_arr(n/2);
    g = create_arr(n/2);
    h = create_arr(n/2);

    arr = create_arr(n);

    //creating the subarrays by splitting the input array on the 4 parts
    part_arr(arr1, a, 0, 0, n);
    part_arr(arr1, b, 0, n/2, n);
    part_arr(arr1, c, n/2, 0, n);
    part_arr(arr1, d, n/2, n/2, n);
    part_arr(arr2, e, 0, 0, n);
    part_arr(arr2, f, 0, n/2, n);
    part_arr(arr2, g, n/2, 0, n);
    part_arr(arr2, h, n/2, n/2, n);

    p1 = Strassens_multiply(sum_substr(0,a,d,n/2), sum_substr(0,e,h,n/2), n/2);
    p2 = Strassens_multiply(sum_substr(0, c, d, n/2), e, n/2);
    p3 = Strassens_multiply(a,sum_substr(1, f, h, n/2), n/2);
    p4 = Strassens_multiply(d, sum_substr(1, g, e, n/2), n/2);
    p5 = Strassens_multiply(sum_substr(0, a, b, n/2), h, n/2);
    p6 = Strassens_multiply(sum_substr(1, c, a, n/2), sum_substr(0, e, f, n/2), n/2);
    p7 = Strassens_multiply(sum_substr(1, b, d, n/2), sum_substr(0, g, h, n/2), n/2);

    build_arr(sum_substr(0,sum_substr(0,p4,p1,n/2),sum_substr(1,p7,p5,n/2),n/2),
                    sum_substr(0,p3,p5,n/2),
                    sum_substr(0,p2,p4,n/2),
                    sum_substr(0,sum_substr(0,p6,p3,n/2),sum_substr(1,p1,p2,n/2),n/2),arr,n);
    return arr;


}

int main() {

    int n = 4;                                      //the length of the matrix
    int **arr1, **arr2, **arr;

    arr1 = create_arr(n);
    generate_arr(arr1, n);

    arr2 = create_arr(n);
    generate_arr(arr2, n);

    arr = create_arr(n);                            //output matrix

    print_arr(arr1, n);
    print_arr(arr2, n);
    arr = Strassens_multiply(arr1, arr2, n);
    print_arr(arr,n);


    return 0;
}