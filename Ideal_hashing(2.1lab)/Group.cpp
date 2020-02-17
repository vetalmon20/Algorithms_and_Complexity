//
// Created by vetal on 15/02/2020.
//

#include "Group.h"

Group::Group() : name(" "), students( ){

}

Group::Group(string name, vector<string> in) {
    this->name = name;
    students = in;
    groups.push_back(this);
}

void Group::show_students() {

    for(size_t i = 0; i < students.size(); i++){
        cout << students[i] << " ";
    }
    cout << endl;
}

GroupArr::GroupArr(){
    a = 0;
    b = 0;
    m = 0;
}

GroupArr::GroupArr(int size, int a, int b){

    this->a = a;
    this->b = b;
    this->m = size * size;

    groups.resize(size*size);
    groups.shrink_to_fit();

}