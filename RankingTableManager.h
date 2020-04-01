//
// Created by kyohei.okawa on 2019/12/19.
//

#ifndef SKIPLIST_RANKINGTABLEMANAGER_H
#define SKIPLIST_RANKINGTABLEMANAGER_H

#include "SkipList.h"
#include <unordered_map>
#include <mutex>
#include "float.h"

using namespace std;

class RankingTableManager {
    typedef SkipNode<unsigned long, double, 32> NodeType;
private:
    unordered_map<string,SkipList<unsigned long, double>*> _rankTables;
    std::mutex _mtx;

    void CreateTableIfNotExist(string tableName) {
        std::lock_guard<std::mutex> lock(_mtx);
        if(_rankTables.count(tableName) == 0) {
            _rankTables[tableName] = new SkipList<unsigned long, double>(DBL_MIN, DBL_MAX);
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

    bool RemoveAll() {
        std::lock_guard<std::mutex> lock(_mtx);
        for(auto table : _rankTables) {
            delete table.second;
        }
        _rankTables.clear();
    }

    void RegistScore(string tableName, unsigned long key, double score) {
        CreateTableIfNotExist(tableName);
        _rankTables[tableName]->mtx.lock();
        _rankTables[tableName]->Set(key, score);
        _rankTables[tableName]->mtx.unlock();
    }

    unsigned long GetRank(string tableName, unsigned long key) {
        if(!IsExistTable(tableName)) {
            return 0;
        }
        _rankTables[tableName]->mtx.lock();
        unsigned long rank = _rankTables[tableName]->GetRankByKey(key);
        _rankTables[tableName]->mtx.unlock();
        return rank;
    }

    std::vector<std::pair<NodeType*,unsigned long>> GetRange(string tableName, unsigned long first, unsigned long range) {
        std::vector<std::pair<NodeType *, unsigned long>> ret;
        if (!IsExistTable(tableName)) {
            return ret;
        }
        _rankTables[tableName]->mtx.lock();
        ret = _rankTables[tableName]->GetRange(first, range);
        _rankTables[tableName]->mtx.unlock();
        return ret;
    }

    unsigned long GetTableLength(string tableName) {
        if(!IsExistTable(tableName)) {
            return 0;
        }

        return _rankTables[tableName]->GetLength();
    }

    double GetScore(string tableName, unsigned long key) {
        if(!IsExistTable(tableName)) {
            return 0;
        }

        NodeType* node = _rankTables[tableName]->Find(key);
        if(node == nullptr) {
            return 0;
        }

        return _rankTables[tableName]->Find(key)->_value;
    }

    bool RemoveNode(string tableName, unsigned long key) {
        if(!IsExistTable(tableName)) {
            return false;
        }

        NodeType* node = _rankTables[tableName]->Find(key);
        if(node == nullptr) {
            return false;
        }

        _rankTables[tableName]->Erase(key);
        return true;
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
