//
//  PersonProfile.h
//  CS32-Project4
//
//  Created by Amanda Wang on 3/2/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h
#include "provided.h"
#include "RadixTree.h"
#include <string>
#include <vector>
class PersonProfile{
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    inline std::string GetName() const{return m_name;}
    inline std::string GetEmail() const{return m_email;}
    inline int GetNumAttValPairs() const {return static_cast<int>(m_attValPairs.size());}
    void AddAttValPair(const AttValPair& attval);
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    std::string m_name;
    std::string m_email;
    std::vector<AttValPair> m_attValPairs;
    RadixTree<std::string> m_container;
    
};


#endif
