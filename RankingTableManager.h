//
// Created by kyohei.okawa on 2019/12/19.
//

#ifndef SKIPLIST_RANKINGTABLEMANAGER_H
#define SKIPLIST_RANKINGTABLEMANAGER_H

#include "SkipList.h"
#include <unordered_map>
#include <mutex>

using namespace std;

class RankingTableManager {
    typedef SkipNode<string, unsigned long, 32> NodeType;
private:
    unordered_map<string,SkipList<string, unsigned long>*> _rankTables;
    std::mutex _mtx;

    void CreateTableIfNotExist(string tableName) {
        if(_rankTables.count(tableName) == 0) {
            std::lock_guard<std::mutex> lock(_mtx);
            _rankTables[tableName] = new SkipList<string, unsigned long>(0, ULONG_LONG_MAX);
        }
    }
public:
    RankingTableManager() {

    }

    ~RankingTableManager() {
        std::lock_guard<std::mutex> lock(_mtx);
        for(auto table : _rankTables) {
            delete table.second;
        }
        _rankTables.clear();
    }

    bool IsExistTable(string tableName) {
        std::lock_guard<std::mutex> lock(_mtx);
        if(_rankTables.count(tableName) == 0) {
            return false;
        }
        return true;
    }

    bool RemoveTable(string tableName) {
        std::lock_guard<std::mutex> lock(_mtx);

        auto itr = _rankTables.find(tableName);
        if(itr == _rankTables.end()) {
            return false;
        }

        delete itr->second;
        _rankTables.erase(tableName);
        return true;
    }

    void RegistScore(string tableName,string key, unsigned long score) {
        CreateTableIfNotExist(tableName);
        _rankTables[tableName]->mtx.lock();
        _rankTables[tableName]->Set(key, score);
        _rankTables[tableName]->mtx.unlock();
    }

    unsigned long GetRank(string tableName, string key) {
        if(!IsExistTable(tableName)) {
            return 0;
        }
        _rankTables[tableName]->mtx.lock();
        unsigned long rank = _rankTables[tableName]->GetRankByKey(key);
        _rankTables[tableName]->mtx.unlock();
        return rank;
    }

    std::vector<std::pair<NodeType*,unsigned long>> GetRange(string tableName, unsigned long first, unsigned long range) {
        std::vector<std::pair<NodeType*,unsigned long>> ret;
        if(!IsExistTable(tableName)) {
            return ret;
        }
        _rankTables[tableName]->mtx.lock();
        ret = _rankTables[tableName]->GetRange(first,range);
        _rankTables[tableName]->mtx.unlock();
        return ret;
    }

    string Print(string tableName) {
        if(!IsExistTable(tableName)) {
            return "";
        }

        _rankTables[tableName]->mtx.lock();
        string ret = _rankTables[tableName]->Print();
        _rankTables[tableName]->mtx.unlock();
        return ret;
    }
};

#endif //SKIPLIST_RANKINGTABLEMANAGER_H
