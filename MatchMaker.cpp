//
//  MatchMaker.cpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//


#include "MatchMaker.h"
#include <iostream>
#include <algorithm>
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at): m_data(&mdb), m_at(&at){}

MatchMaker::~MatchMaker(){}
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{
    auto start = std::chrono::steady_clock::now();
    
    const PersonProfile * p = m_data->GetMemberByEmail(email);
    std::vector<EmailCount> v;
    if(p == nullptr) return v;
    //for some reason this doesn't work when it is a private member variable. am very upset.
    std::unordered_set<std::string> m_set;
    std::vector<AttValPair> compatible;
    std::vector<AttValPair> totalCompatibleValues;
    std::vector<std::string> matching;
    std::unordered_map<std::string, EmailCount> m_mapEmailsWithCompatibility;
    for(int i = 0; i < p->GetNumAttValPairs(); i++){
        AttValPair temp("", "");
        if(p->GetAttVal(i, temp)){
            //for each attribute value pair in p, we find compatible values
            compatible = m_at->FindCompatibleAttValPairs(temp);
            for(int i = 0; i < compatible.size(); i++){
                //for each compatible value found, add it into a set
                //if added successfully, add the values into a vector
                if(m_set.insert(compatible[i].attribute + ',' + compatible[i].value).second){
                    AttValPair a(compatible[i].attribute, compatible[i].value);
                    totalCompatibleValues.push_back(a);
                }
            }
        }
    }
    //for each compatible value
    for(int i = 0; i < totalCompatibleValues.size(); i++){
        //find members with the compatible value
        matching = m_data->FindMatchingMembers(totalCompatibleValues[i]);
        //for each member, add their email into a map mapping their email to an attribute
        for(int j = 0; j< matching.size(); j++){
            if(m_mapEmailsWithCompatibility.find(matching[j]) == m_mapEmailsWithCompatibility.end()){
                if(matching[j] != email){
                    EmailCount e(matching[j], 1);
                    std::pair<std::string, EmailCount> myPair(matching[j], e);
                    m_mapEmailsWithCompatibility.insert(myPair);
                }
            }
            else{
                m_mapEmailsWithCompatibility.at(matching[j]).count += 1;
            }
        }
    }
    for(auto key: m_mapEmailsWithCompatibility){
        if(key.first != email && key.second.count >= threshold){ //skip original email
            v.push_back(key.second);
        }
    }
    std::sort(v.begin(), v.end(), byEmail);
    
    /* code you want to measure */
    std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;

    
    return v;
}


