/**
 * 2nd Course K-29
 * Lab 3.
 * Task: compose a D-Pyramid in an array-type structure. Create Extract_max, Insert and Increase_Key
 *       functions.
 *
 *@author Vitaliy Datsiuk
 *@version 1.1 05/10/19
 *
 * The high of the Pyramid is: [log n] where log has d as a main and [] means the base of the num
 */

#include <iostream>
#include <limits>

using namespace std;

struct D_Pyramid{
private:
    int d;                               //num of sons
    int *arr;                            //actually the array type representation
    int size;                            //actual size of the pyramid
    int max_size;                        //allocated memory for the array

    void incr_size(int new_size) {

        max_size = new_size;
        int *temp = new int[new_size];

        for (int i = 0; i < size; i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }   //allocates additional memory of *new_size* to an array

    void decr_size(){
        size--;
    }                //decrements the size

    void  swap(int a, int b) {
        if (a < 0 || b < 0 || a >= size || b >= size){
            cout << "Unexpected error. Wrong indexes for an array in function swap(a,b)";
            return;
        }

        int temp;
        temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }       //swaps the values in the indexes

    void heapify(int index){

        int largest = index;
        int temp;
        for (int i = 1; i <= d; i++){
            temp = d * index + i;
            if(temp < size && arr[temp] > arr[largest]){
                largest = temp;                         //find the largest son
                }
            }
        if (largest != index){                       //if largest is no the root
            swap(largest, index);
            heapify(largest);
        }

    }         //updates the properties of the heap to the entered index

    void _Increase_Key(int index){

        if(index <= 0)
            return;

        int father = (index - 1) / d;           //father index

        if(father < 0)
            return;

        if(arr[index] >= arr[father]){
            swap(index, father);
            _Increase_Key(father);
        }
    }   //recursive implementation of increasing the index value

public:
    D_Pyramid(){
        int _d;
        cout << "enter pls the D for the pyramid:" << endl;
        cin >> _d;

        if (_d <= 0){
            cout << "Wrong D for the pyramid. D changed to a default value (D = 2)" <<endl;
            _d = 2;
        }

        d = _d;
        arr = new int[1];
        size = 0;
        max_size = 1;
    }                              //default constructor
    D_Pyramid(int _d){
        d = _d;
        arr = new int[1];
        size = 0;
        max_size = 1;
    }                        //default constructor with entered D

    void add_node(int val) {
        if (size == max_size)
            incr_size(max_size + 20);
        arr[size] = val;
        size++;
    }                  //function that allows You to add a node

    void display() {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }                          //just displays the array

    void buildHeap(){
        for (int i = size - 2; i >=0; i --){
            heapify(i);
        }
    }                         //build the heap

    int Extract_Max(){
        int temp = arr[0];
        swap(0, size - 1);
        decr_size();
        heapify(0);
        return temp;
    }                        //extracts the max value from the Pyramid

    void Increase_Key(int index, int value){

        if(index <= 0 || index >= size){
            cout << "Wrong index" << endl;
            return;
        }

        if(arr[index] >= value){
            cout << "The value in this index is larger" << endl;
            return;
        }

        arr[index] = value;
        _Increase_Key(index);


    }  //checks the errors and calls the private function

    void Insert(int val){
        add_node(numeric_limits<int>::min());
        Increase_Key(size - 1,val);
    }
};

int main() {

    D_Pyramid a;
    a.add_node(10);
    a.add_node(20);
    a.add_node(8);
    a.add_node(7);
    a.add_node(18);
    a.add_node(9);
    a.display();
    a.buildHeap();
    a.display();

    a.Increase_Key(5,22);
    a.display();
    a.Insert(40);
    a.display();



    return 0;
}