//
//  MemberDatabase.cpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//

#include "MemberDatabase.h"
#include <sstream>
#include <fstream>
#include <iostream>

MemberDatabase::MemberDatabase(){}
MemberDatabase::~MemberDatabase(){
    std::vector<PersonProfile *>::iterator it = m_people.begin();
    while(it != m_people.end()){
        delete *it;
        it = m_people.erase(it);
    }
}

//O(M) time because we must go through each line of the database
bool MemberDatabase::LoadDatabase(std::string filename){
    std::string line;
    std::ifstream file(filename);
    int attvalPairs = 0;
    std::string name;
    std::string attribute;
    std::string trait;
        
    std::string email;
    while(std::getline(file, line)){
        if(line == "") std::getline(file, line);
        name = line;
        std::getline(file, email);
        if(m_keyEmail.search(email) != nullptr) return false;
        std::string line2;
        std::string temp;
        std::getline(file, temp);
        attvalPairs = std::stoi(temp);
        PersonProfile * p = new PersonProfile(name, email);
            for(int i = 0; i < attvalPairs; i++){
                getline(file, attribute, ',');
                getline(file, trait);
                AttValPair a(attribute, trait);
                p->AddAttValPair(a);
                std::vector<std::string> * retVal = m_keyAttVal.search(attribute+','+trait);
                if(retVal != nullptr){
                    //trait already exists
                    retVal->push_back(email);
                }
                else{
                    std::vector<std::string> v;
                    v.push_back(email);
                    m_keyAttVal.insert(attribute+','+trait, v);
                    
                }
            }
        m_people.push_back(p);
        m_keyEmail.insert(email, p);
    }
    file.close();
    return true;
}

//O(1) time because we use radix tree and the length of attribute +',' + value is roughly constant
std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const{
    std::vector<std::string> * p = m_keyAttVal.search(input.attribute +','+ input.value);
    std::vector<std::string> empty;
    if(p == nullptr) return empty;
    return *p;
}

//O(1) time because we are using a radix tree; depends on length of email which is roughly constant
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
    PersonProfile ** p = m_keyEmail.search(email);
    if(p == nullptr) return nullptr;
    return *p;
}
