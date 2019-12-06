#include <iostream>
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
    for(int i = 0; i < 1000; i++) {
        skipList.Insert(rand()%1000,"a");
        cout << skipList.Print() << std::endl;
    }
    return 0;
}
