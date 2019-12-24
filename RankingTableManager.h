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

    bool RemoveTable(string tableName) {
        if(!IsExistTable(tableName)) {
            return false;
        }
        _rankTables.erase(tableName);
        return true;
    }

    void RegistScore(string tableName,int userId, unsigned long score) {
        CreateTableIfNotExist(tableName);
        _rankTables[tableName].Set(userId, score);
    }

    unsigned long GetRank(string tableName, int userId) {
        if(!IsExistTable(tableName)) {
            return 0;
        }
        return _rankTables[tableName].GetRankByKey(userId);
    }

    std::vector<std::pair<NodeType*,unsigned long>> GetRange(string tableName, unsigned long first, unsigned long range) {
        std::vector<std::pair<NodeType*,unsigned long>> ret;
        if(!IsExistTable(tableName)) {
            return ret;
        }
        return _rankTables[tableName].GetRange(first,range);
    }
};

#endif //SKIPLIST_RANKINGTABLEMANAGER_H
