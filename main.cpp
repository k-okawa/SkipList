#include <iostream>
#include <time.h>
#include "SkipList.h"

using namespace std;

int main() {
    SkipList<string, int> skipList(0,INT_MAX);
//    auto start = clock();
//    skipList.Insert("hello",4444);
//    auto end = clock();
//    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "first insert time = " << time << endl;

//    skipList.Insert("okawa",2222);
//    skipList.Insert("koike",4423);
//    skipList.Insert("okada", 4456);
//    skipList.Insert("lee",1111);
//    skipList.Insert("sakuma",600);
//    skipList.Insert("itokazu", 3413);
//
//    cout << skipList.Print() << endl << endl;
//    cout << "length:" << skipList.GetLength() << endl;
//
//    skipList.Erase("okawa");
//
//    cout << skipList.Print() << endl;
//    cout << "length:" << skipList.GetLength() << endl;

    auto start = clock();
    for(int i = 0; i < 1000000; i++) {
        skipList.Insert(to_string(i),rand()%10000);
//        cout << skipList.Print() << std::endl;
//        cout << "progress:" << i << std::endl;
    }
    auto end = clock();
    cout << skipList.Print() << std::endl;
    auto time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "many insert time = " << time << endl;
    cout << "length:" << skipList.GetLength() << std::endl;

    start = clock();
    skipList.Erase("500000");
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "erase time = " << time << endl;

    return 0;
}
