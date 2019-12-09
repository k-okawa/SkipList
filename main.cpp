#include <iostream>
#include <time.h>
#include "SkipList.h"

using namespace std;

int main() {
//    std::cout << "Hello, World!" << std::endl;
//    SkipList<int, string> skipList(0,INT_MAX);
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(4993,"hiroshi");
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(2453,"hitomi");
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(1111,"taro");
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(4325,"atsushi");
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(3212,"babibi");
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(4324,"aaa");
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(9374,"hello");
//    cout << skipList.Print() << std::endl;
//    skipList.Insert(4332,"yeah");
//    cout << skipList.Print() << std::endl;


    SkipList<int, string> skipList(0,INT_MAX);

    auto start = clock();
    skipList.Insert(4444,"hello");
    auto end = clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "first insert time = " << time << endl;

    start = clock();
    for(int i = 0; i < 1000000; i++) {
        skipList.Insert(rand()%100000,"a");
        //cout << skipList.Print() << std::endl;
        //cout << "progress:" << i << std::endl;
    }
    end = clock();
    cout << skipList.Print() << std::endl;
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "many insert time = " << time << endl;

    start = clock();
    skipList.Insert(3334, "last");
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "last insert time = " << time << endl;

    return 0;
}
