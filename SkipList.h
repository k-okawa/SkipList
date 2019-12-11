//
// Created by kyohei.okawa on 2019/12/06.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

template<class K,class V,int MAX_LEVEL>
class SkipNode {
public:
    K _key;
    V _value;
    SkipNode<K, V, MAX_LEVEL>* _forwards[MAX_LEVEL];
    SkipNode<K, V, MAX_LEVEL>* _backwards[MAX_LEVEL];
    int _forwardSpans[MAX_LEVEL];

    SkipNode() {
        for(int i = 0; i < MAX_LEVEL; i++) {
            _forwards[i] = NULL;
            _backwards[i] = NULL;
            _forwardSpans[i] = 0;
        }
    }

    SkipNode(V value) : _value(value) {
        for(int i = 0; i < MAX_LEVEL; i++) {
            _forwards[i] = NULL;
            _backwards[i] = NULL;
            _forwardSpans[i] = 0;
        }
    }

    SkipNode(K key, V value) : _key(key), _value(value) {
        for(int i = 0; i < MAX_LEVEL; i++) {
            _forwards[i] = NULL;
            _backwards[i] = NULL;
            _forwardSpans[i] = 0;
        }
    }

    ~SkipNode() {

    }
};

template<class K, class V, int MAX_LEVEL=32>
class SkipList {
    typedef SkipNode<K, V, MAX_LEVEL> NodeType;

private:
    V _minValue;
    V _maxValue;
    NodeType* _header;
    NodeType* _tail;
    int _currentMaxLevel;
    int _length;
    std::unordered_map<K,NodeType*> _nodeMap;

public:
    SkipList(V minValue, V maxValue):
            _header(NULL),
            _tail(NULL),
            _minValue(minValue),
            _maxValue(maxValue),
            _currentMaxLevel(0),
            _length(0) {
        _header = new NodeType(minValue);
        _tail = new NodeType(maxValue);
        for (int i = 0; i < MAX_LEVEL; i++) {
            _header->_forwards[i] = _tail;
            _header->_forwardSpans[i] = 1;
            _tail->_backwards[i] = _header;
        }
    }

    ~SkipList() {
        NodeType* currentNode = _tail;
        while(currentNode != _tail) {
            NodeType* tmp = currentNode;
            currentNode = currentNode->_forwards[0];
            delete tmp;
        }
        delete _header;
        delete _tail;
    }

    void Set(K key, V value) {
        _length++;
        NodeType* updateNode[MAX_LEVEL];
        NodeType* currentNode = _header;
        NodeType* beforeNode = _header;
        for(int i = _currentMaxLevel; i >= 0; i--) {
            currentNode = beforeNode->_forwards[i];
            while(currentNode->_value < value) {
                beforeNode = currentNode;
                currentNode = currentNode->_forwards[i];
            }
            updateNode[i] = beforeNode;
            updateNode[i]->_forwardSpans[i]++;
        }

        int randomLevel = GetRondomLevel();
        if(randomLevel > _currentMaxLevel) {
            for(int i = _currentMaxLevel + 1; i <= randomLevel; i++) {
                updateNode[i] = _header;
                _header->_forwardSpans[i] = _length + 1;
            }
            _currentMaxLevel = randomLevel;
        }
        auto it = _nodeMap.find(key);
        if(it != _nodeMap.end()) {
            // すでに登録されているキーの場合一度削除
            Erase(key);
        }

        currentNode = new NodeType(key,value);
        for(int i = 0; i <= randomLevel; i++) {
            auto befUpdateNodeForward = updateNode[i]->_forwards[i];
            currentNode->_forwards[i] = updateNode[i]->_forwards[i];
            updateNode[i]->_forwards[i] = currentNode;
            currentNode->_backwards[i] = updateNode[i];
            currentNode->_forwards[i]->_backwards[i] = currentNode;

            int count = 0;
            if(i > 0) {
                auto tmp = currentNode;
                while(tmp != befUpdateNodeForward) {
                    tmp = tmp->_forwards[0];
                    count++;
                }
                currentNode->_forwardSpans[i] = count;
                int span = updateNode[i]->_forwardSpans[i];
                updateNode[i]->_forwardSpans[i] = span - count;
            } else {
                currentNode->_forwardSpans[i] = 1;
                updateNode[i]->_forwardSpans[i]--;
            }
        }
        _nodeMap[key] = currentNode;
    }

    bool Erase(K key) {
        auto target = Find(key);
        if(target == nullptr) {
            return false;
        }

        NodeType* currentNode = _header->_forwards[_currentMaxLevel];
        for(int i = _currentMaxLevel; i >= 0; i--) {
            //currentNode = currentNode->_backwards[i]->_forwards[i];
            while(currentNode->_value < target->_value) {
                currentNode = currentNode->_forwards[i];
            }
            if(currentNode == target) {
                currentNode->_backwards[i]->_forwards[i] = currentNode->_forwards[i];
                currentNode->_backwards[i]->_forwardSpans[i] = currentNode->_backwards[i]->_forwardSpans[i] + currentNode->_forwardSpans[i] - 1;
                currentNode->_forwards[i]->_backwards[i] = currentNode->_backwards[i];
            } else {
                currentNode->_backwards[i]->_forwardSpans[i]--;
                currentNode = currentNode->_backwards[i];
            }
        }

        _length--;
        _nodeMap.erase(key);
        delete target;
        return true;
    }

    NodeType* Find(K key) {
        auto it = _nodeMap.find(key);
        if(it != _nodeMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    int GetLength() {
        return _length;
    }

    bool IsEmpty() {
        return _header->_forwards[0] == _tail;
    }

    std::string Print() {
        stringstream sstr;
        for (int i = 0; i < MAX_LEVEL; i++) {
            NodeType *current = _header;
            while (current != _tail) {
                if(current == _header) {
                    sstr << "|BEGIN MINVALUE=" << _header->_value << " span=" << _header->_forwardSpans[i];
                } else {
                    sstr << "|key=" << current->_key << " value=" << current->_value << ",span=" << current->_forwardSpans[i];
                }
                current = current->_forwards[i];
            }
            sstr << "|END MAXVALUE=" << _tail->_value;
            sstr << "|" << std::endl;
        }

        return sstr.str();
    }

private:
    double UniformRandom() {
        return rand() / double(RAND_MAX);
    }

    int GetRondomLevel() {
        int level = 0;
        double p = 0.25;
        while(UniformRandom() < p && level < MAX_LEVEL - 1) {
            level++;
        }
        return level;
    }
};

#endif //SKIPLIST_SKIPLIST_H
