//
// Created by kyohei.okawa on 2019/12/06.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <iostream>
#include <sstream>
using namespace std;

template<class K,class V,int MAX_LEVEL>
class SkipNode {
public:
    K _key;
    V _value;
    SkipNode<K, V, MAX_LEVEL>* _forwards[MAX_LEVEL];

    SkipNode() {
        for(int i = 0; i < MAX_LEVEL; i++) {
            _forwards[i] = NULL;
        }
    }

    SkipNode(K key) : _key(key) {
        for(int i = 0; i < MAX_LEVEL; i++) {
            _forwards[i] = NULL;
        }
    }

    SkipNode(K key, V value) : _key(key), _value(value) {
        for(int i = 0; i < MAX_LEVEL; i++) {
            _forwards[i] = NULL;
        }
    }

    ~SkipNode() {

    }
};

template<class K, class V, int MAX_LEVEL=32>
class SkipList {
    typedef SkipNode<K, V, MAX_LEVEL> NodeType;

private:
    K _minKey;
    K _maxKey;
    NodeType* _header;
    NodeType* _tail;
    int _currentMaxLevel;

public:
    SkipList(K minKey, K maxKey):
    _header(NULL),
    _tail(NULL),
    _minKey(minKey),
    _maxKey(maxKey),
    _currentMaxLevel(0){
        _header = new NodeType(minKey);
        _tail = new NodeType(maxKey);
        for(int i = 0; i < MAX_LEVEL; i++) {
            _header->_forwards[i] = _tail;
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

    void Insert(K key, V value) {
        NodeType* updateNode[MAX_LEVEL];
        NodeType* currentNode = _header;
        NodeType* beforeNode = _header;
        for(int i = _currentMaxLevel; i >= 0; i--) {
            currentNode = beforeNode->_forwards[i];
            while(currentNode->_key < key) {
                beforeNode = currentNode;
                currentNode = currentNode->_forwards[i];
            }
            updateNode[i] = beforeNode;
        }

        int randomLevel = GetRondomLevel();
        if(randomLevel > _currentMaxLevel) {
            for(int i = _currentMaxLevel + 1; i <= randomLevel; i++) {
                updateNode[i] = _header;
            }
            _currentMaxLevel = randomLevel;
        }
        currentNode = new NodeType(key,value);
        for(int i = 0; i <= randomLevel; i++) {
            currentNode->_forwards[i] = updateNode[i]->_forwards[i];
            updateNode[i]->_forwards[i] = currentNode;
        }
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
                    sstr << "|BEGIN MINKEY=" << _header->_key;
                } else {
                    sstr << "|key=" << current->_key << ",val=" << current->_value;
                }
                current = current->_forwards[i];
            }
            sstr << "|END MAXKEY=" << _tail->_key;
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
