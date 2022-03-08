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

//TODO: does person profile need to be deleted? or anything? bad things are happening.
/*
 ● MUST meet the following big-O requirements:
 ○ When asked to find the email addresses associated with members who have a given attribute-value pair, it must be able to deliver all members in better than O(P+M) time where P is the total number of distinct attribute-value pairs across the entire member population, and M is the number of members that have the searched-for attribute-value pair. So, for example O(log2P+M) would be acceptable.
 ○ When asked to get a member’s PersonProfile by searching for their email address, it must be able to deliver the member’s information in better than O(N) time where N is the total number of members in the member database.
 ● MUST be case-sensitive for all attribute-value pair lookups
 ● MUST be able to accommodate a large number of members (our provided members.txt
 data file has 100k members)
 ● MUST use your RadixTree class to map attribute-value pairs to email addresses
 ● MUST use your RadixTree class to map email addresses to member profiles
 ● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
 ● MUST NOT add any new public member functions or variables
 ● MAY use the STL list and vector classes
 */

MemberDatabase::MemberDatabase(){}
MemberDatabase::~MemberDatabase(){
    std::vector<PersonProfile *>::iterator it = m_people.begin();
    while(it != m_people.end()){
        delete *it;
        it = m_people.erase(it);
    }
}
bool MemberDatabase::LoadDatabase(std::string filename){
    std::string line;
    std::ifstream file(filename);
    int attvalPairs = 0;
    std::string name;
    std::string attribute;
    std::string trait;
    
    //TODO: remove count variable; like this now for efficiency.
    int count = 0;
    std::string email;
    while(std::getline(file, line)){
//        std::cerr << line << std::endl;
//        if(count == 2) break;
        if(line == "") std::getline(file, line);
        name = line;
        
        //TODO: remove
//        std::cerr << line << std::endl;

        std::getline(file, email);
        if(m_keyEmail.search(email) != nullptr) return false;
        
        //TODO: remove
//        std::cerr << email << std::endl;

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
        count ++;
    }
    file.close();
    return true;
}

//TODO: findmatchingmembers must be const
//TODO: for some reason, cannot get this to return non empty vector.
std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const{
    std::vector<std::string> * p = m_keyAttVal.search(input.attribute +','+ input.value);
    std::vector<std::string> empty;
    if(p == nullptr) return empty;
    return *p;
}

//TODO: getmemberbyemail is const
//log n time because using a radix tree
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
    PersonProfile ** p = m_keyEmail.search(email);
    if(p == nullptr) return nullptr;
    return *p;
}
