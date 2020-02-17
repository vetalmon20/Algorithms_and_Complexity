//
// Created by vetal on 15/02/2020.
//

#ifndef IDEAL_HASHING_2_1LAB__GROUP_H
#define IDEAL_HASHING_2_1LAB__GROUP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Group {
public:
    string name;
    vector<string> students;

    Group();
    Group(string name, vector<string> in);

    void show_students();
};

class GroupArr{
public:
    int a,b,m;
    vector<Group*> groups;

    GroupArr();
    GroupArr(int size, int a, int b);
};

extern vector<Group*> groups;

#endif //IDEAL_HASHING_2_1LAB__GROUP_H
