//
//  PersonProfile.cpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//
//TODO: i think this is complete.

/*
 
 ● MUST be able to add and retrieve attribute-value pairs in better than O(N) time where N is the number of attribute-value pairs stored in the object. So for example, O(log2 N) would be acceptable. For big-O analysis purposes, you may assume that there's a constant that all attribute lengths are less than.
 ● MUST use your RadixTree class to map attributes to values (for full credit)
 TODO: check; do i have to map an attribute TO a value? or can i just add attribute,value as key and then something irrelevant as value?
 ● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
 ● MAY use the STL list, vector, set, and unordered_set classes
 */
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

