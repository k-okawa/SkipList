#include <iostream>
#include <time.h>
#include "SkipList.h"

using namespace std;

int main() {
    SkipList<string, int> skipList(0,INT_MAX);

    auto start = clock();
    //skipList.Insert("hello",4444);
    auto end = clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "first insert time = " << time << endl;

    start = clock();
    for(int i = 0; i < 10; i++) {
        skipList.Insert(to_string(i),rand()%100);
        //cout << skipList.Print() << std::endl;
        //cout << "progress:" << i << std::endl;
    }
    end = clock();
    cout << skipList.Print() << std::endl;
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "many insert time = " << time << endl;
    cout << "length:" << skipList.GetLength() << std::endl;

    start = clock();
    skipList.Insert("last",3334);
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "last insert time = " << time << endl;

    return 0;
}
