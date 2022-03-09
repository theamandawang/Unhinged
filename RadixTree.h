//USING MAP BECAUSE I CANNOT HANDLE THIS RN
#ifndef RadixTree_h
#define RadixTree_h
#include <string>
#include <vector>
#include <map>
#include "provided.h"



//TODO: MUST REPLACE WITH ACTUAL RADIX TREE INSTEAD OF MAP
template<typename ValueType>
class RadixTree{
public:
    RadixTree(){}
    ~RadixTree(){}
    void insert(std::string key, const ValueType& value){
        m_map[key] = value;
    }
    ValueType* search(std::string key) const{
        auto it = m_map.find(key);
        if(it == m_map.end()) return nullptr;
        return const_cast<ValueType*>(&(it->second));
    }
    std::map<std::string, ValueType> m_map;
private:
//    struct Node{
//        std::string key;
//        ValueType& value;
//        vector<Node*> children;
//    }
};

#endif
