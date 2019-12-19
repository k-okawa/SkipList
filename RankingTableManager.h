//
// Created by kyohei.okawa on 2019/12/19.
//

#ifndef SKIPLIST_RANKINGTABLEMANAGER_H
#define SKIPLIST_RANKINGTABLEMANAGER_H

#include "SkipList.h"
#include <unordered_map>
#include <mutex>

using namespace std;

enum RankType {
    YEARY = 0,
    MONTHLY = 1,
    WEEKLY = 2,
    DAILY = 3
};

class RankingTableManager {
    typedef SkipNode<int, unsigned long, 32> NodeType;
private:
    unordered_map<string,SkipList<int, unsigned long>> _rankTables;

    void CreateTableIfNotExist(string tableName) {
        if(_rankTables.count(tableName) == 0) {
            _rankTables[tableName] = SkipList<int, unsigned long>(0, ULONG_LONG_MAX);
        }
    }
public:
    RankingTableManager() {

    }

    ~RankingTableManager() {

    }

    bool IsExistTable(string tableName) {
        if(_rankTables.count(tableName) == 0) {
            return false;
        }
        return true;
    }

    void RegistScore(string tableName, unsigned long score) {

    }

    unsigned long GetRank(string tableName, int userId) {

    }

    std::vector<std::pair<NodeType*,unsigned long>> GetRange(string tableName, unsigned long first, unsigned long range) {

    }
};

#endif //SKIPLIST_RANKINGTABLEMANAGER_H
