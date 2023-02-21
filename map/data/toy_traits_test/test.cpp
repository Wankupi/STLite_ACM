//
// Created by Libro on 2022/3/16.
//

#include "map.h"
#include <algorithm>
#include <iostream>
using namespace std;

template<class T>
void toy_traits_assignable(T iter, sjtu::my_true_type) {
    cout<<"iterator pointing to pair("<<iter->first<<','<<iter->second<<") is assignable\n";
}

template<class T>
void toy_traits_assignable(T iter, sjtu::my_false_type) {
    cout<<"iterator pointing to pair("<<iter->first<<','<<iter->second<<") is not assignable\n";
}

template<class T>
void toy_traits_func(T iter) {
    typename sjtu::my_type_traits<T>::iterator_assignable iterator_assignable;
    toy_traits_assignable(iter,iterator_assignable);
}


int main() {
    sjtu::map<int,int> a;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    toy_traits_func(++a.begin());
    toy_traits_func(a.cbegin());
    return 0;
}