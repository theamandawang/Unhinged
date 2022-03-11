//USING MAP BECAUSE I CANNOT HANDLE THIS RN
#ifndef RadixTree_h
#define RadixTree_h
#include <string>
#include <vector>
#include <iostream>
#include "provided.h"

template<typename ValueType>
class RadixTree{
public:
    RadixTree(){
        head = new Node("head!", false);
        needsDeleted.push_back(head);
    }
    ~RadixTree(){
//        std::cout << needsDeleted.size() << std::endl;
        auto it = needsDeleted.begin();
        while(it != needsDeleted.end()){
            delete *it;
            it = needsDeleted.erase(it);
        }
    }
    void insert(std::string key, const ValueType& value){
        Node * current = head;
        int counter = 0;
        while(counter < key.size()){
            char c = key.at(counter);
            int ind = c-0;
//            std::cout << c << std::endl;
//            std::cout << key <<  " : key" << std::endl;
            if(current->children[ind] == nullptr){
                current->children[ind] = new Node(key.substr(counter), true);
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
                    if(key.size() == (counter+j)) break;
//                    std::cout << "key at j " << key.at(j) << std::endl;
                    if(currString.at(j) != key.at(j+counter)){
                        j--;
                        break;
                    }
                }
                counter += j;
                
                //all of key is contained in currString
                if(counter == key.size() && j!=currString.size()){
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
                else if(j == currString.size() && currString.size() < key.size() && counter < key.size() &&  current->children[key.at(counter) - 0] == nullptr){
                    int childInd = key.at(counter) - 0;
                    Node * temp = new Node(key.substr(counter), true);
                    temp->value = value;
                    needsDeleted.push_back(temp);
                    current->children[childInd] = temp;
                    return;
                }
                
                
                
                else if(j < currString.size()){
                    Node * temp = new Node(key.substr(counter+1), true);
                    temp->value = value;
                    needsDeleted.push_back(temp);
                    
                    Node * temp2 = new Node(currString.substr(0, j+1), false);
                    needsDeleted.push_back(temp2);
                    
                    prev->children[currString.at(0)-0] = temp2;
                    
                    temp2->children[currString.at(j+1)-0] = current;
                    
                    temp2->children[key.at(counter+1)-0] = temp;
                    current->str = currString.substr(j+1);
                    return;
                }
                //they are the same node
                else if((counter) == key.size() && !current->leaf){
                    current->value = value;
                    current->leaf = true;
                    return;
                }
                //this means that they split off without one ending completely!
            }
        }
        
    }
                                            
    ValueType* search(std::string key) const{
        Node * curr = head;
        int counter = 0;

        while(counter < key.size()){
//            std::cout << key << " key before checking nullptr" << std::endl;
//            std::cout << "children index to examine " << (key.at(0) - 0) << std::endl;
            char c = key.at(counter);
            int ind = c-0;
            if(curr->children[ind] != nullptr){
                curr = curr->children[ind];
                std::string currString = curr->str;
                int j;
                if((key.size()-counter) < currString.size()){
                    return nullptr;
                }
                for(j = 0; j<currString.size(); j++){
                    if(currString.at(j) != key.at(j+counter)){
//                        std::cout << "key char: " << key.at(j+counter) << std::endl;
                        return nullptr;
                    }
                }
                counter+=j;

            }
            else return nullptr;
            if(counter == (key.size()) && curr->leaf) return &curr->value;
        }
        return nullptr;
    }
//    void dump() {
//        print("", head);
//    }
    
    
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
        
        
        void print(std::string output, Node * p) {
                for (int i = 0; i < 128; i++) {
                    if (p->children[i] != nullptr) {
                        Node* child = p->children[i];
                        std::string newOutput = output;
                        newOutput += (i + 'a');
                        newOutput += child->str;
                        std::cerr << "============================" << std::endl;
                        std::cerr << "Parent: " << """ << output << """ << std::endl;
                        std::cerr << "Child: " << """ << newOutput << """ << std::endl;
                        if (child->leaf)
                            std::cerr << "This is a complete word and its value corresponds to: " << child->str << std::endl;
                        std::cerr << std::endl;

                        print(newOutput, p->children[i]);
                    }
                }
            }
    };
    Node * head;
    std::vector<Node *> needsDeleted;

};

#endif
