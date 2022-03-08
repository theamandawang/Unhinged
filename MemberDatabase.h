//
//  MemberDatabase.hpp
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h
#include "RadixTree.h"
#include "PersonProfile.h"
#include "provided.h"
#include <string>
class MemberDatabase{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
    
private:
    //maps emails to member profiles
    RadixTree<PersonProfile *> m_keyEmail;
    //maps attVal to emails
    RadixTree<std::vector<std::string>> m_keyAttVal;
    //used to delete things that are allocated.
    std::vector<PersonProfile *> m_people;
};

#endif
