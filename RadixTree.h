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
        head = new Node("head", false);
        needsDeleted.push_back(head);
    }
    ~RadixTree(){
//        postorder(head);
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
            
            //all of the current string is contained in the key
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
                    //j is set to the last index that currString and key have in common
                    if(currString.at(j) != key.at(j+counter)){
                        j--;
                        break;
                    }
                }
                counter += j;
                
                //all of key is contained in currString
                if(counter == key.size() && j<currString.size()){
                    Node * temp = new Node(key, true);
                    temp->value = value;
                    needsDeleted.push_back(temp);
                    prev->children[ind] = temp;
                    //the currString is set to the latter half of currString (after letters it shares with key)
                    current->str = currString.substr(j);
                    int childInd = currString.at(j) - 0;
                    temp->children[childInd] = current;
                    return;
                }
                
                
                //all of currString is contained in key; this is repetitive
//                else if(j == currString.size() && currString.size() < key.size() && counter < key.size() &&  current->children[key.at(counter) - 0] == nullptr){
//                    int childInd = key.at(counter) - 0;
//                    Node * temp = new Node(key.substr(counter), true);
//                    temp->value = value;
//                    needsDeleted.push_back(temp);
//                    current->children[childInd] = temp;
//                    return;
//                }
                
                
                //splitting must happen
                else if(j < currString.size()){
                    //temp is the latter half of key
                    Node * temp = new Node(key.substr(counter+1), true);
                    temp->value = value;
                    needsDeleted.push_back(temp);
                    
                    //temp2 is the first half of currstring (also the first half of key)
                    Node * temp2 = new Node(currString.substr(0, j+1), false);
                    needsDeleted.push_back(temp2);
                    
                    prev->children[currString.at(0)-0] = temp2;
                    
                    temp2->children[currString.at(j+1)-0] = current;
                    
                    temp2->children[key.at(counter+1)-0] = temp;
                    current->str = currString.substr(j+1);
                    return;
                }
                //they are the same node
                else if((counter) == key.size() && j<currString.size() && !current->leaf){
                    current->value = value;
                    current->leaf = true;
                    return;
                }
                //they are the same node, only updates value
                else if (counter == key.size() && j<currString.size() && current->leaf){
                    current->value = value;
                    return;
                }
            }
            /*otherwise, the key contains all of the current string but has more values to check, i.e. counter < key.size().
             we go back to the top of the loop and examine what is at counter + j , where j = currString.size()
             (the cases above catch behavior for when the for loop ends early).
            */
        }
        
    }
                                            
    ValueType* search(std::string key) const{
        Node * curr = head;
        int counter = 0;

        while(counter < key.size()){
            char c = key.at(counter);
            int ind = c-0;
            //checks each character of key to see if it matches the characters in current
            if(curr->children[ind] != nullptr){
                curr = curr->children[ind];
                std::string currString = curr->str;
                int j = 0;
                //return nullptr if the current string is longer than the key, or if for
                //for some reason the current string is empty
                if((key.size()-counter) < currString.size() || currString.size() == 0){
                    return nullptr;
                }
                for(j = 0; j<currString.size(); j++){
                    //using j+counter in case substring takes a lot of memory/time
                    if(currString.at(j) != key.at(j+counter)){
                        return nullptr;
                    }
                }
                //j is currString.size()
                counter+=j;

            }
            else return nullptr;
            
            //if counter is the same as the size of the key, that means that a concatenation of node str's will yield
            //a string equal to key
            if(counter == (key.size()) && curr->leaf) return &curr->value;
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
    void postorder(Node* curr){
        if(curr==nullptr) return;
        for(int i = 0; i < 128; i++){
            if(curr->children[i] != nullptr){
                postorder(curr->children[i]);
            }
        }
        if(curr!=nullptr){
            delete curr;
            curr = nullptr;
        }
    }
    void print(std::string ogName, Node * curr) {
            for (int i = 0; i < 128; i++) {
                if (curr->children[i] != nullptr) {
                    Node* child = curr->children[i];
                    std::string childName;
                    childName = (child->str);
                    std::cerr << "------------------" << std::endl;
                    std::cerr << "parent: "  << ogName  << "\tchild: "  << childName  << std::endl;
                    if (child->leaf)
                        std::cerr << "full word, value: " << child->str << std::endl;
                    std::cerr << std::endl;
                    print(childName, curr->children[i]);
                }
            }
        }
    Node * head;
    std::vector<Node *> needsDeleted;

};

#endif

