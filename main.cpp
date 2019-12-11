#include <iostream>
#include <time.h>
#include "SkipList.h"

using namespace std;

int main() {
    SkipList<string, int> skipList(-1,INT_MAX);
//    auto start = clock();
//    skipList.Set("hello", 4444);
//    auto end = clock();
//    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "first insert time = " << time << endl;
//
//    skipList.Set("okawa", 2222);
//    skipList.Set("koike", 4423);
//    skipList.Set("okada", 4456);
//    skipList.Set("lee", 1111);
//    skipList.Set("sakuma", 600);
//    skipList.Set("itokazu", 3413);
//
//    cout << skipList.Print() << endl << endl;
//    cout << "length:" << skipList.GetLength() << endl;
//
//    skipList.Erase("okawa");
//
//    cout << skipList.Print() << endl;
//    cout << "length:" << skipList.GetLength() << endl;

    int loopCount = 1000000;
    auto start = clock();
    for(int i = 0; i < loopCount; i++) {
        skipList.Set(to_string(i), rand() % 10000);
//        cout << skipList.Print() << std::endl;
//        cout << "progress:" << i << std::endl;
    }
    auto end = clock();
    cout << skipList.Print() << std::endl;
    auto time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "many insert time = " << time << endl;
    cout << "length:" << skipList.GetLength() << std::endl;

    start = clock();
    for(int i = 0; i < loopCount; i++) {
        skipList.Find(to_string(i));
    }
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "find time = " << time << endl;

    start = clock();
    for(int i = 0; i < loopCount; i++) {
        skipList.Erase(to_string(i));
    }
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "erase time = " << time << endl;


    return 0;
}
