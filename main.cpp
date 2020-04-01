#include <iostream>
#include <time.h>
#include "SkipList.h"
#include "RankingTableManager.h"
#include "float.h"

using namespace std;

//int main() {
//    //key: int, score: unsigned long
//    SkipList<int, unsigned  long> skipList(0, ULONG_LONG_MAX);
//    int loopCount = 1000000;
//    auto start = clock();
//    for(int i = 0; i < loopCount; i++){
//        // データをセット
//        skipList.Set(i, rand() % loopCount);
//    }
//    auto end = clock();
//    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "データの追加にかかった時間:" << time << "ms" << endl;
//}

int main() {
    SkipList<unsigned long, double> skipList(DBL_MIN,DBL_MAX);
//    auto start = clock();
//    skipList.Set("hello", 4444);
//    auto end = clock();
//    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "first insert time = " << time << endl;
//

//    skipList.Set(1, 1);
//    skipList.Set(2, 2);
//    skipList.Set(3, 3);
//    skipList.Set(4, 4);
//    skipList.Set(5, 5);
//    skipList.Set(6, 6);
//    skipList.Set(7,7);
//    skipList.Set(8,8);
//
//    cout << skipList.Print() << endl << endl;
//    cout << "length:" << skipList.GetLength() << endl;
//
//    unsigned long first = 1;
//    unsigned long range = 100;
//    auto pairs = skipList.GetRange(first,range);
//    for(auto nodeRank : pairs) {
//        cout << "key=" << nodeRank.first->_key << " rank=" << nodeRank.second << endl;
//    }

    RankingTableManager rankManager;
    rankManager.RegistScore("Hello",1,1);
    rankManager.RegistScore("Hello",1,1);
    rankManager.RegistScore("Hello",2,2);
    rankManager.RegistScore("Hello",3,3);
    rankManager.RegistScore("Hello",4,4);
    rankManager.RegistScore("Hello",5,5);
    rankManager.RegistScore("Hello",6,6);
    rankManager.RegistScore("Hello",7,7);
    rankManager.RegistScore("Hello",8,8);

    cout << rankManager.Print("Hello") << endl;

    unsigned long first = 1;
    unsigned long range = 0;
    std::vector<std::pair<SkipNode<unsigned long, double, 32>*,unsigned long>> rankList = rankManager.GetRange("Hello",first,range);
    for(auto info : rankList) {
        cout << "key=" << info.first->_key << " rank=" << info.second << endl;
    }
//cout << "key=1 " << "rank=" << rankManager.GetRank("Hello",1) << endl;

//    int loopCount = 1000000;
//    auto start = clock();
//    for(int i = 0; i < loopCount; i++) {
//        skipList.Set(to_string(i), rand() % loopCount);
////        cout << skipList.Print() << std::endl;
////        cout << "progress:" << i << std::endl;
//    }
//    auto end = clock();
//    cout << skipList.Print() << std::endl;
//    auto time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "many insert time = " << time << endl;
//    cout << "length:" << skipList.GetLength() << std::endl;
//
//    start = clock();
//    for(int i = 0; i < loopCount; i++) {
//        skipList.Find(to_string(i));
//    }
//    end = clock();
//    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "find time = " << time << endl;
//
//    start = clock();
//    for(int i = 0; i < loopCount; i++) {
//        skipList.GetRankByKey(to_string(i));
////        if(i == 500000)
////            cout << skipList.Check() << endl;
//    }
//    end = clock();
//    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "rank time = " << time << endl;
//
//    //cout << skipList.Print() << endl;

//    RankingTableManager rankManager;
//    int loopCount = 1000000;
//    auto start = clock();
//    for(int i = 0; i < loopCount; i++){
//        rankManager.RegistScore("hello",i, rand() % loopCount);
//    }
//    auto end = clock();
//    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
//    cout << "データの追加にかかった時間:" << time << "ms" << endl;
    //cout << rankManager.Print("hello") << std::endl;

    return 0;
}
