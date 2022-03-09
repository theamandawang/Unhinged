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
    std::vector<std::string> uniqueEmails;
    std::unordered_map<std::string, EmailCount> matchingEmailsWithCompatibility;
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
            if(matchingEmailsWithCompatibility.find(matching[j]) == matchingEmailsWithCompatibility.end()){
                if(matching[j] != email){
                    EmailCount e(matching[j], 1);
                    std::pair<std::string, EmailCount> myPair(matching[j], e);
                    matchingEmailsWithCompatibility.insert(myPair);
                    uniqueEmails.push_back(matching[j]);
                }
            }
            else{
                matchingEmailsWithCompatibility.at(matching[j]).count += 1;
            }
        }
    }
    for(int i = 0; i < matchingEmailsWithCompatibility.size(); i++){
        v.push_back(matchingEmailsWithCompatibility.at(uniqueEmails[i]));
    }
    std::sort(v.begin(), v.end(), byEmail);
    auto it = v.begin();
    while(it != v.end()){
        if((*it).count < threshold) break;
        it++;
    }
    if(it==v.end()) return v;
    std::vector<EmailCount> vThresh(v.begin(), it);
    
    
    /* code you want to measure */
    std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;

    
    return vThresh;
}


