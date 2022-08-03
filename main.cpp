#include <iostream>
#include "SkipList.h"
#include "RankingTableManager.h"
#include "float.h"

using namespace std;

int main() {
    RankingTableManager rankManager;
    rankManager.ResistScore("Hello",1,1);
    rankManager.ResistScore("Hello",1,1);
    rankManager.ResistScore("Hello",2,2);
    rankManager.ResistScore("Hello",3,3);
    rankManager.ResistScore("Hello",4,4);
    rankManager.ResistScore("Hello",5,5);
    rankManager.ResistScore("Hello",6,6);
    rankManager.ResistScore("Hello",7,7);
    rankManager.ResistScore("Hello",8,8);

    cout << rankManager.Print("Hello") << endl;

    unsigned long first = 1;
    unsigned long range = 0;
    std::vector<std::pair<SkipNode<unsigned long, double, 32>*,unsigned long>> rankList = rankManager.GetRange("Hello",first,range);
    for(auto info : rankList) {
        cout << "key=" << info.first->_key << " rank=" << info.second << endl;
    }
    return 0;
}
