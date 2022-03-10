//USING MAP BECAUSE I CANNOT HANDLE THIS RN
#ifndef RadixTree_h
#define RadixTree_h
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "provided.h"



//TODO: MUST REPLACE WITH ACTUAL RADIX TREE INSTEAD OF MAP
template<typename ValueType>
class RadixTree{
public:
    RadixTree(){
        head = new Node("head!", false);
        needsDeleted.push_back(head);
    }
    ~RadixTree(){
        auto it = needsDeleted.begin();
        while(it != needsDeleted.end()){
            delete *it;
            it = needsDeleted.erase(it);
        }
    }
    void insert(std::string key, const ValueType& value){
        Node * current = head;
        int ogSize = key.size();
        for(int i = 0; i < ogSize; i++){
            //need to traverse what is in my tree so far
            char c = key.at(0);
            int ind = c-0;
//            std::cout << c << std::endl;
//            std::cout << key <<  " : key" << std::endl;
            if(current->children[ind] == nullptr){
                current->children[ind] = new Node(key.substr(i), true);
                current->children[ind]->value = value;
                needsDeleted.push_back(current->children[ind]);
                return;
            }
            else{
                //follow the string down!
                Node * prev = current;
                current = current->children[ind];
                std::string currString = current->str;
                int j;
                for(j = 0; j<currString.size(); j++){
                    if(key.size() == (j)) break;
//                    std::cout << "key at j " << key.at(j) << std::endl;

                    if(currString.at(j) != key.at(j)){
                        j--;
                        break;
                    }
                }
                //all of key is contained in currString
                if(j == key.size() && j!=currString.size()){
                    Node * temp = new Node(key, true);
                    temp->value = value;
                    needsDeleted.push_back(temp);
                    prev->children[ind] = temp;
                    current->str = currString.substr(j);
                    int childInd = currString.at(j) - 0;
//                    std::cout << childInd << " " << current->str << std::endl;
                    temp->children[childInd] = current;
                    return;
                }
                //all of currString is contained in key
                
                if(j == currString.size() && currString.size() < key.size() && current->children[key.at(j) - 0] == nullptr){
                    int childInd = key.at(j) - 0;
                    Node * temp = new Node(key.substr(currString.size()), true);
                    temp->value = value;
                    needsDeleted.push_back(temp);
                    current->children[childInd] = temp;
                    return;
                }
                if(j < currString.size() && current->children[key.at(j)-0] == nullptr){
//                    std::cout << "key: " << key << std::endl;
                    Node * temp = new Node(key.substr(j+1), true);
                    temp->value = value;
                    needsDeleted.push_back(temp);
                    
                    Node * temp2 = new Node(currString.substr(0,j+1), false);
                    needsDeleted.push_back(temp2);
                    
                    prev->children[currString.at(0)-0] = temp2;
                    
                    temp2->children[currString.at(j+1)-0] = current;
                    
                    temp2->children[key.at(j+1)-0] = temp;
                    current->str = currString.substr(j+1);
                    return;
                }
                //they are the same node
                if(j == key.size() && j==currString.size() && !current->leaf){
                    current->value = value;
                    current->leaf = true;
                    return;
                }
                
                else{
                    key = key.substr(j);
                    i+=j;
                }
                //this means that they split off without one ending completely!
            }
        }
        
    }
                                            
    ValueType* search(std::string key) const{
        Node * curr = head;
        int ogSize = key.size();
        for(int i = 0; i < ogSize; i++){
//            std::cout << key << " key before checking nullptr" << std::endl;
//            std::cout << "children index to examine " << (key.at(0) - 0) << std::endl;
            if(curr->children[key.at(0)-0] != nullptr){
                curr = curr->children[key.at(0)-0];
                std::string currString = curr->str;
                int j;
                if(key.size() < currString.size()){
                    return nullptr;
                }
                for(j = 0; j<currString.size(); j++){
                    if(currString.at(j) != key.at(j)){
                        return nullptr;
                    }
                }
                key = key.substr(j);
//                std::cout << key << std::endl;

            }
            if(key == "" && curr->leaf) return &curr->value;
        }

        return nullptr;
    }
private:
    
    struct Node {
        public:
        Node(std::string s, bool l){
            str = s;
            leaf = l;
        }
        std::string str;
        ValueType value;
        bool leaf;
        Node * children[128]={nullptr};
    };
    Node * head;
    std::vector<Node *> needsDeleted;

};

#endif
