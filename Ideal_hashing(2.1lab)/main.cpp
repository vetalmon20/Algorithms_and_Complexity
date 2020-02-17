#include <iostream>
#include <string>
#include <vector>
#include "Group.h"

using namespace std;

vector<Group*> groups;


vector<string> group1_st = {"Oleg", "Igor", "Natasha", "Vanya", "Sasha"};
vector<string> group2_st = {"Ingha", "Ksyusha", "Ivan", "Max", "Danil"};
vector<string> group3_st = {"Vasya", "Olya", "Vetal", "Yarik", "Leva"};
vector<string> group4_st = {"Vadim", "Stas", "Kira", "Lyosha", "Ostap"};
vector<string> group5_st = {"Vlad", "Anton", "Katya", "Nastya", "Borya"};
vector<string> group6_st = {"Taras", "Vika", "Lisa", "Vitaliya", "Tanya"};
vector<string> group7_st = {"Sabina", "Tolya", "Tamara", "Misha", "Natasha"};

Group group1("group1", group1_st);
Group group2("group2", group2_st);
Group group3("group3", group3_st);
Group group4("group4", group4_st);
Group group5("group5", group5_st);
Group group6("group6", group6_st);
Group group7("group7", group7_st);

const int a = 3;
const int b = 42;
const int p = 101;


long long int strhash(string in){
    long long int hash = 0;
    const int P = 53;
    long long int pow = 1;
    for(size_t i = 0; i < in.size(); i++){
        hash = hash + (in[i] - 'a' + 1) * pow;
        pow = pow * P;
    }
    return (abs(hash)) % 99999999;
}

void first_hash(vector<Group*> in[]){

    long long int str_h;
    int index;

    for(size_t i = 0; i < groups.size(); i++){
        str_h = strhash(groups[i]->name);
        index = ((a * str_h + b) % p) % groups.size();
        in[index].push_back(groups[i]);
        //cout << index << " ";
        //cout << str_h << " ";
    }
}

void create_grouparr(GroupArr *in, int size, vector<Group*> table_row){
    int a = rand() % 10;
    int b = rand() % 100;

    bool check_arr[size];

    for(size_t i = 0; i < size; i++){
        check_arr[i] = 0;
    }

    int hash;

    for(size_t i = 0; i < table_row.size(); i++){
        hash = ((a * strhash(table_row[i]->name) + b) % p) % size;
        if(check_arr[hash] == 0)
            check_arr[hash] = 1;
        else {
            create_grouparr(in, size, table_row);
            return;
        }
    }

    for(size_t i = 0; i < table_row.size(); i++) {
        in->a = a;
        in->b = b;
        hash = ((a * strhash(table_row[i]->name) + b) % p) % size;
        in->groups[hash] = table_row[i];
    }
}

void create_table(vector<Group*> in[], GroupArr *table[]){

    for(size_t i = 0; i < groups.size(); i++){
        if(in[i].size() != 0){

            table[i] = new GroupArr(in[i].size(), a, b);
            create_grouparr(table[i], table[i]->m, in[i]);

        }
        else {
            table[i] = new GroupArr();
        }
    }
}

void find_group(string in, GroupArr *table[]){
    long long int in_strhash = strhash(in);
    int first_index = ((a*in_strhash + b) % p) % groups.size();

    if(table[first_index]->m == 0){
        cout << "There is no such a group" << endl;
        return;
    }

    int position = ((table[first_index]->a * in_strhash + table[first_index]->b) % p) % table[first_index]->m;

    if(table[first_index]->groups[position] == NULL || table[first_index]->groups[position]->name != in) {
        cout << "There is no such a group" << endl;
        return;
    }

    table[first_index]->groups[position]->show_students();
}

int main() {

    GroupArr aaa(5,1,2);
    //aaa.groups[3] = &group1;

    vector<Group*> top_table[groups.size()];
    first_hash(top_table);

    GroupArr *table[groups.size()];

    create_table(top_table, table);

    find_group("group", table);
    find_group("group2", table);
    find_group("group3", table);

    return 0;
}





