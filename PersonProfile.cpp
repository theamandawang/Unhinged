//
//  PersonProfile.cpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//
#include "PersonProfile.h"
#include "RadixTree.h"
PersonProfile::PersonProfile(std::string name, std::string email): m_name(name), m_email(email){}
PersonProfile::~PersonProfile(){
//    auto it = m_attValPairs.begin();
//    while(it != m_attValPairs.end()){
//        delete *it;
//        it = m_attValPairs.erase(it);
//    }
}


//Add attributes as attribute combined with value; this is because if we used a vector for possible value types and we had N attributes, it would be O(N) time to look through the vector to examine duplicates/get values from it or something.
void PersonProfile::AddAttValPair(const AttValPair& attval){
    if(m_container.search(attval.attribute+ ',' + attval.value) == nullptr){
        m_container.insert(attval.attribute + ',' + attval.value, attval.value);
        //AttValPair *a = new AttValPair(attval.attribute, attval.value);
        AttValPair a(attval.attribute, attval.value);
        m_attValPairs.push_back(a);

    }
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if(attribute_num >= 0 && attribute_num < GetNumAttValPairs()){
        attval = (m_attValPairs[attribute_num]);
        return true;
    }
    return false;
}

