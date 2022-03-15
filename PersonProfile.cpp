//
//  PersonProfile.cpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//
#include "PersonProfile.h"
#include "RadixTree.h"
PersonProfile::PersonProfile(std::string name, std::string email): m_name(name), m_email(email){}
PersonProfile::~PersonProfile(){}

//O(1) time because we insert using RadixTree
void PersonProfile::AddAttValPair(const AttValPair& attval){
    if(m_container.search(attval.attribute+ ',' + attval.value) == nullptr){
        m_container.insert(attval.attribute + ',' + attval.value, true);
        AttValPair a(attval.attribute, attval.value);
        m_attValPairs.push_back(a);
    }
}
//O(1) time because we are accessing a value in a vector
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if(attribute_num >= 0 && attribute_num < GetNumAttValPairs()){
        attval = (m_attValPairs[attribute_num]);
        return true;
    }
    return false;
}

