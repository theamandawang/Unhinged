//USING MAP BECAUSE I CANNOT HANDLE THIS RN
#ifndef RadixTree_h
#define RadixTree_h
#include <string>
#include <vector>
#include <map>
#include "provided.h"
#include <iostream>
/*
 
 ● MUST be a class template, implemented fully in RadixTree.h.
 ● MUST hold a number of nodes that is proportional to the number of unique key-value
 pairs inserted in the Radix Tree, NOT a number of nodes that is proportional to the
 number of keys times the average key length.
 ● MUST have a big-O for insertion of O(K) where K is the maximum key length of a new
 item being inserted into the Radix Tree, and for searches, O(K) where K is the maximum
 key length of the items in the Radix Tree.
 ● MUST be case-sensitive for all searches
 ● MUST be able to accommodate any number of key-value pairs
 ● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
 (in your final submission)
 ● MUST NOT add any new public member functions or variables
 ● MAY avoid dealing with an empty key string
 ● MAY use the STL set, list and vector classes
 ● MAY have any private member functions or variables you choose to add

 */




//TODO: MUST REPLACE WITH ACTUAL RADIX TREE INSTEAD OF MAP
template<typename ValueType>
class RadixTree{
public:
    RadixTree():m_size(0){}
    ~RadixTree(){}
    void insert(std::string key, const ValueType& value){
        m_map[key] = value;
    }
    ValueType* search(std::string key) const{
        //typename std::map<std::string, ValueType>::const_iterator it = m_map.find(key);
        auto it = m_map.find(key);
        if(it == m_map.end()) return nullptr;
        return const_cast<ValueType*>(&(it->second));
    }
    std::map<std::string, ValueType> m_map;
private:
    int m_size;
//    struct Node{
//        std::string key;
//        ValueType& value;
//        vector<Node*> children;
//    }
};

#endif
