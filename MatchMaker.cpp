//
//  MatchMaker.cpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//

/*
 ● MUST run as efficiently as possible - we will not state any exact big-O requirements, but try to make your code as efficient as possible - avoid O(N) algorithms where at all possible. If you code things correctly, you should be able to find matches in a fraction of a second even across hundreds of thousands of member profiles!
 ● MUST NOT add any new public member functions or variables
 ● MAY use ANY STL containers you like
 ● MAY have any private member functions or variables you choose to add

 */

#include "MatchMaker.h"
#include <algorithm>
//TODO: implement everything.
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at): m_data(&mdb), m_at(&at){}

MatchMaker::~MatchMaker(){
    //delete m_data;
}

/*
 The IdentifyRankedMatches method is responsible for:
 ● Taking as input an email address for a member, and a matching threshold (indicating how many compatible attribute-value pairs another member must have to be considered a good match)
 ● Using the provided email address to obtain the member’s attribute-value pairs (e.g., “hobby”,”eating”, etc.)
 ● Converting this collection of attribute-value pairs into a collection of unique compatible attribute-value pairs that we want to find in other members (e.g., for “hobby”,”eating” might translate to “hobby”,”cooking” as well as “occupation”,”chef”)
 ● Discovering the collection of members that have each such compatible attribute-value pair (Joe and Mary have “hobby”,”cooking”; Mary and Sue have “occupation”,”chef”)
 ● Identifying the collection of members that have at least the threshold number of compatible attribute-value pairs in common with the member we’re trying to match for
 ● Returning a vector of EmailCount objects (a struct we provide in provided.h), each holding the email address of a matching member that has at least the threshold number of compatible attribute-value pairs, along with the number of such compatible pairs. The EmailCount objects in the returned vector are ordered primarily in descending order of the number of compatible attribute-value pairs, with ties broken by a secondary ordering in ascending alphabetical order by email address (so if two members both have the same number of matching attribute-value pairs, then we’d order their email addresses alphabetically in the output)
 */
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{
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
            compatible = m_at->FindCompatibleAttValPairs(temp);
            for(int i = 0; i < compatible.size(); i++){
                if(m_set.insert(compatible[i].attribute + ',' + compatible[i].value).second){
                    AttValPair a(compatible[i].attribute, compatible[i].value);
                    totalCompatibleValues.push_back(a);
                }
            }
        }
    }
    for(int i = 0; i < totalCompatibleValues.size(); i++){
        matching = m_data->FindMatchingMembers(totalCompatibleValues[i]);
        //std::cerr << "compatible value " << totalCompatibleValues[i].attribute + ',' + totalCompatibleValues[i].value << std::endl;
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
//        std::cerr<< matchingEmailsWithCompatibility.at(uniqueEmails[i]).email <<std::endl;
    }
    std::sort(v.begin(), v.end(), byEmail);
    auto it = v.begin();
    while(it != v.end()){
        if((*it).count < threshold) break;
        it++;
    }
    if(it==v.end()) return v;
    std::vector<EmailCount> vThresh(v.begin(), it);
    return vThresh;
}


